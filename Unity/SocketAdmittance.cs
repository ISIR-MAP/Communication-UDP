using System;
using System.Collections;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using UnityEngine;


public class SocketAdmittance: ScriptObject {

	private Vector3 position = new Vector3(0f, 0f, 0f);
	private Vector3 orientation = new Vector3(0f, 0f, 0f);
	private Vector3 vitesse = new Vector3(0f, 0f, 0f);
	private Vector3 vitesseAngulaire = new Vector3(0f, 0f, 0f);
	private Vector3 force = new Vector3(0f, 0f, 0f);
	private Vector3 moment = new Vector3(0f, 0f, 0f);

	private Socket socket;
	private UdpClient client;

	public string IP = "127.0.0.1";
	public int portSend = 8080;
	public int portRecv = 8081;

	IPEndPoint ipRecvPoint = null;
	IPEndPoint ipSendPoint = null;

	// Use this for initialization
	public SocketAdmittance () {

		// Open Socket (talker) and starting UdpClient (listener)
		this.socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
		this.client = new UdpClient(portRecv);
		this.ipSendPoint = new IPEndPoint(IPAddress.Parse(IP), portSend);
		this.ipRecvPoint = new IPEndPoint(IPAddress.Parse(IP), portRecv);

		SocketAdmittance inst = this;
		this.client.BeginReceive(new AsyncCallback(ReceiveCallback), inst);
		/*while (position == new Vector3(0f, 0f, 0f)) { }*/		// Wait until first contact is made with interface
		print("INIT:: Link to Haptic Interface Established");
	}

	private static void ReceiveCallback (IAsyncResult ar) {
		SocketAdmittance inst = (SocketAdmittance)(ar.AsyncState);
		UdpClient u = (UdpClient)inst.client;
		IPEndPoint e = (IPEndPoint)inst.ipRecvPoint;

		Byte[] data = u.EndReceive(ar, ref e);
		inst.force = new Vector3((float) BitConverter.ToDouble(data, 8),
									(float) BitConverter.ToDouble(data, 16),
									-1*((float) BitConverter.ToDouble(data, 0)));

		inst.moment = new Vector3((float) BitConverter.ToDouble(data, 32),
									   (float) BitConverter.ToDouble(data, 40),
									   (float) BitConverter.ToDouble(data, 24));

		// Formatting data to send
		byte[] dataX = BitConverter.GetBytes((double) -1*inst.position.z);
		byte[] dataY = BitConverter.GetBytes((double) inst.position.x);
		byte[] dataZ = BitConverter.GetBytes((double) inst.position.y);
		//Debug.Log("Send: " + inst.force.x + ", " + inst.force.y + ", " + inst.force.z);

		byte[] dataToSend = new byte[24];
		for (int i=0; i<dataX.Length; i++) {
			dataToSend[i] = dataX[i];
			dataToSend[i+8] = dataY[i];
			dataToSend[i+16] = dataZ[i];
		}

		// Send force through socket
		try {
			inst.socket.SendTo(dataToSend, inst.ipSendPoint);
		} catch (Exception exception) {
			print("Exception caught: " + exception.Message);
		}

		inst.client.BeginReceive(new AsyncCallback(ReceiveCallback), inst);
	}

	public Vector3 GetPosition() {
		return this.position;
	}

	public void SetPosition(Vector3 p) {
		this.position = p;
	}

	public Vector3 GetOrientation() {
		return this.orientation;
	}

	public Vector3 GetSpeed() {
		return this.vitesse;
	}

	public Vector3 GetAngularSpeed() {
		return this.vitesseAngulaire;
	}

	public void SetForce(Vector3 f) {
		 this.force = f;
	}

	public Vector3 GetForce() {
		 return this.force;
	}

	public KeyValuePair<Vector3, Vector3> GetPositionAndOrientation() {
		return new KeyValuePair<Vector3, Vector3>(this.position, this.orientation);
	}

	~SocketAdmittance() {

	}
}
