using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;﻿
using UnityEditor;

/*	Script computing the forces and gains relating to the coupling of
	a haptic interface
 * 		- Gets haptic interface information through "SocketImpedance.cs"
 * 			by creating an instance of the class
 * 		- Requires "Handle" GameObject which has no collision
 * 			to behave correctly
 * 		- Requires "Proxy" GameObject which has collisions and a
 * 			rigidbody to simulate a realistic behavior
 */

public class CouplingImpedance : MonoBehaviour {

	struct Point {
		public float distance;
		public Vector3 position;
		public int index;

		public Point(float d, Vector3 p, int i) {
			this.distance = d;
			this.position = p;
			this.index = i;
		}
	}

	SocketImpedance socket;
	Rigidbody rb;
	GameObject proxy;
	GameObject handle;
	HandleManager handleScript;
	public GameObject[] grabableObjs;

	GameObject Root;
	Vector3[] bezierPoints;

	Vector3 force;
	Vector3 deltaPos;

	bool objGrabbed;
	Vector3 prevPos;

	int sizeFactor = 3;		// 3 for Virtuose 3d
	float threshold = 0.1f;
	public bool enableHapticFeedback;
	public bool enableHapticPath;
	public bool enableVisualPath;
	public bool recordData;

	int counter;
	float error;

	float k = 80; // Virtuose = 80
	float b = 0;
	float m = 0;
	float kG = 5f; // Gain proportionnel guidage en chemin
	float bG = 0; // Gain dérivé guidage en chemin

	// Use this for initialization
	void Start() {
		this.socket = ScriptableObject.CreateInstance<SocketImpedance>();
		this.force = Vector3.zero;	// force vector to be sent to haptic interface

		// Getting proxy Rigidbody and its parameters
		this.rb = GetComponent<Rigidbody>();
		this.m = this.rb.mass;

		// Computing dampening (stability)
		this.b = 2f*(float)Math.Pow(this.k*this.m, 0.5f);
		this.bG = 0f*(float)Math.Pow(this.kG*this.m, 0.5f);
		print("INIT:: Coefficients: k = " + this.k + ", b = " + this.b);

		// Getting Handle GameObject and its script
		proxy = GameObject.Find("Proxy");
		handle = GameObject.Find("Handle");
		handleScript = this.handle.GetComponent<HandleManager>();

		// Getting bezier Points
		this.Root = GameObject.Find("Reference Path");
		this.bezierPoints = this.Root.GetComponent<BezierVisualizer>().GetPoints(enableVisualPath);
		objGrabbed = false;

		// Initialize position of handle and proxy to avoid huge forces
		// at the start of the game
		this.rb.position = this.sizeFactor*(socket.GetPosition());
		prevPos = this.rb.position;
		handle.transform.position = this.sizeFactor*(socket.GetPosition());
		print("INIT:: Haptics Done");
	}

	// Gets called every physics frame
	void FixedUpdate() {
		// Retreive positions and velocity of handle and proxy
		Vector3 posHandle = this.sizeFactor*(socket.GetPosition());
		Vector3 velHandle = this.sizeFactor*(socket.GetSpeed());
		Vector3 posProxy  = this.rb.position;
		Vector3 velProxy  = this.rb.velocity;

		// Copy the position of the haptic interface to the proxy
		handle.transform.position = posHandle;

		// Compute force applied to proxy and haptic interface (spring-dampener equations)
		this.deltaPos = posHandle-posProxy;
		this.force = this.k*deltaPos - this.b*(velProxy-velHandle);

		// Applying forces to proxy
		this.rb.AddForce(force);

		Vector3 guidanceForce = applyGuidance(posProxy, velProxy, velHandle);
		grabObjects(posProxy);

		if (enableHapticFeedback) {
			if (this.handleScript.GetStatus()) {		// Applies a force if handle is colliding with an object
				this.socket.SetForce(-1*force/2 + guidanceForce);
			} else {
				this.socket.SetForce(guidanceForce);
			}
		} else {
			this.socket.SetForce(new Vector3(0f, 0f, 0f));
		}

		if (objGrabbed && (prevPos-posProxy).magnitude>0.05f) {
			DrawLine(Color.red, prevPos, posProxy);
			prevPos = posProxy;
		}

		/*if ((grabableObjs[0].transform.position-new Vector3(-0.493f, 1.101f, -0.244f)).magnitude<0.04 && objGrabbed) {
			essai++;
			grabableObjs[0].transform.position = new Vector3(0.656f, 1.117f, -0.019f);
			foreach (GameObject obj in grabableObjs) {
				if (GetComponent<FixedJoint>()!=null) {
					Destroy(GetComponent<FixedJoint>());
					obj.GetComponent<Rigidbody>().mass = 1f;
				}
			}
			objGrabbed = false;

			print(essai);
			if (this.essai==7) {
				block++;
				essai = 0;
				if (this.path == 0) {
					GameObject.Find("path2").SetActive(true);
					GameObject.Find("Sphere (3)").transform.position = new Vector3(0.51f, 0.2415f, 0.3821f);
				} else {
					GameObject.Find("path2").SetActive(false);
					GameObject.Find("Sphere (3)").transform.position = new Vector3(0.51f, 0.2415f, 0.251f);
				}
				// change scene
			}
		}*/
	}

	private Vector3 applyGuidance(Vector3 posProxy, Vector3 velProxy, Vector3 velHandle) {
		Vector3 f = new Vector3(0f, 0f, 0f);
		if (enableHapticPath) {
			Point closestPoint = getNearestPointOnBezier(posProxy);
			//print(closestPoint.distance);
			//if (GetComponent<FixedJoint>()!=null) {
			if (GetComponent<FixedJoint>()==null) {
				if (closestPoint.distance>this.threshold) {
					f = this.kG*(closestPoint.position - posProxy) - this.bG*(velProxy-velHandle);
					Vector3 fOffset = f.normalized*this.threshold;
					f -= fOffset;
					//print("Yes force" + f);
				} else {
					//print("No  force" + f);
				}
			}
		}

		return f;
	}

	void DrawLine(Color color, Vector3 prev, Vector3 curr) {
		GameObject myLine = new GameObject();
		myLine.transform.position = prev;
		myLine.AddComponent<LineRenderer>();
		LineRenderer lr = myLine.GetComponent<LineRenderer>();
		lr.material = new Material(Shader.Find("Particles/Alpha Blended Premultiply"));
		lr.SetColors(color, color);
		lr.SetWidth(0.0025f, 0.0025f);
		lr.positionCount = 2;
		lr.SetPosition(0, prev);
		lr.SetPosition(1, curr);
	}

	private void grabObjects(Vector3 posProxy) {
		// Applies a FixedJoint to the proxy linking it to the grabbed object
		if (Input.GetKeyDown(KeyCode.Space)) {
			print("Space key pressed");
			foreach (GameObject obj in grabableObjs) {
				if ((obj.transform.position-posProxy).magnitude<0.25 &&
					GetComponent<FixedJoint>()==null) {
					FixedJoint joint = obj.AddComponent<FixedJoint>();
			 		joint.connectedBody = proxy.GetComponent<Rigidbody>();
					obj.GetComponent<Rigidbody>().mass = 0.0000001f;
					objGrabbed = true;
				}
			}
        }

		if (Input.GetKeyUp(KeyCode.Space)) {
			print("Space key released");
			foreach (GameObject obj in grabableObjs) {
				if (GetComponent<FixedJoint>()!=null) {
					Destroy(GetComponent<FixedJoint>());
					obj.GetComponent<Rigidbody>().mass = 1f;
				}
			}
			objGrabbed = false;
    	}
	}

	private Point getNearestPointOnBezier(Vector3 posProxy) {
		float min = 100;
		int index = -1;
		Vector3 p = new Vector3(0f, 0f, 0f);
		for (int i=0; i<this.bezierPoints.Length; i++) {
			if (Vector3.Distance(this.bezierPoints[i], posProxy)<min) {
				min = Vector3.Distance(this.bezierPoints[i], posProxy);
				p = this.bezierPoints[i];
				index = i;
			}
		}
		return new Point(min, p, index);
	}

	public Vector3 GetPosition() {
		return this.rb.position;
	}

	public Vector3 GetDeltaPosition() {
		return deltaPos;
	}

	public Vector3 GetForce() {
		return force;
	}

	void OnDestroy() {

	}
}
