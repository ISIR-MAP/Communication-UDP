/*
 * VirtuoseAPI.h - Virtuose Application Programming Interface
 *
 * Copyright (C) 2011, HAPTION S.A.
 * Author: Pascal Louveau
 * Last modification: 30/09/2011
 * Version number: 3.80
 */

#if !defined(_VirtuoseAPI_h)
#define _VirtuoseAPI_h

#ifndef __cplusplus
#define inline extern
#endif

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
 
#include <stdio.h> 

  /* Hide VirtContext for client applications */
#if !defined(_VirtuosePrivate_h)
  typedef void *VirtContext;
#endif	/* _VirtuosePrivate_h */

  typedef enum
  {
    /* Default command type: no movement possible */
    COMMAND_TYPE_NONE = 0,
    /* Simple joint control */
    COMMAND_TYPE_JOINT,
    /* Simple cartesian control */
    COMMAND_TYPE_CARTESIAN,
    /* Force/position control */
    COMMAND_TYPE_IMPEDANCE,
    /* Position/force control */
    COMMAND_TYPE_ADMITTANCE,
    /* Position/force control with virtual kinematics */
    COMMAND_TYPE_VIRTMECH,
	/* articular position control */
	COMMAND_TYPE_ARTICULAR,
	/* articular force control */
	COMMAND_TYPE_ARTICULAR_IMPEDANCE,
  }
  VirtCommandType;


  typedef enum
  {
    /* Default command type: no movement possible */
    GRIPPER_COMMAND_TYPE_NONE = 0,
    /* Position/position control */
    GRIPPER_COMMAND_TYPE_POSITION,
    /* Force/position control */
    GRIPPER_COMMAND_TYPE_IMPEDANCE,
  }
  VirtGripperCommandType;

  
  typedef enum
  {
    /* Indexing is allowed on translations and rotations */
    INDEXING_ALL = 0,
    /* Indexing is allowed on translations only */
    INDEXING_TRANS = 1,
    /* No indexing allowed, even without deadman  */
    INDEXING_NONE = 2,
    /* Indexing is allowed on translations and rotations, no force while indexing */
    INDEXING_ALL_FORCE_FEEDBACK_INHIBITION = 3,
    /* Indexing is allowed on translations only, no force while indexing */
    INDEXING_TRANS_FORCE_FEEDBACK_INHIBITION = 4,
    /* Indexing is allowed on rotations only, no force while indexing */
    INDEXING_ROT_FORCE_FEEDBACK_INHIBITION = 6,
    /* Indexing is allowed on rotations only */
    INDEXING_ROT = 7,
  }
  VirtIndexingType;
 
 
  typedef enum 
  { 
    VM_TYPE_CartMotion = 0, 
    VM_TYPE_Spline, 
    VM_TYPE_Rx, 
    VM_TYPE_Tx,
    VM_TYPE_TxRx, 
    VM_TYPE_TxTyTz, 
    VM_TYPE_RxRyRz,
    VM_TYPE_TxTy,
    VM_TYPE_Crank,
  } 
  VirtVmType; 
 
 
  typedef void (*VirtPeriodicFunction)(VirtContext, void *);

#define DEBUG_SERVO	0x0001
#define DEBUG_LOOP	0x0002

  typedef enum 
  {
    APIVERSION,
    ATTACHVO,
    ATTACHQSVO,
    ATTACHVOAVATAR,
    CLOSE,
    DETACHVO,
    DETACHVOAVATAR,
    DISPLAYHARDWARESTATUS,
    GETCATCHFRAME,
    GETBASEFRAME,
    GETBUTTON,
    GETCOMMANDTYPE,
    GETDEADMAN,
    GETEMERGENCYSTOP,
    GETERROR,
    GETERRORCODE,
    GETERRORMESSAGE,
    GETFORCE,
    GETFORCEFACTOR,
    GETINDEXINGMODE,
    GETLIMITTORQUE,
    GETOBSERVATIONFRAME,
    GETPOSITION,
    GETPOWERON,
    GETSPEED,
    GETSPEEDFACTOR,
    GETTIMELASTUPDATE,
    GETTIMEOUTVALUE,
    OPEN,
    SETCATCHFRAME,  
    SETBASEFRAME,
    SETCOMMANDTYPE,
    SETDEBUGFLAGS,
    SETFORCE,
    SETFORCEFACTOR,
    SETINDEXINGMODE,
    SETLIMITTORQUE,
    SETOBSERVATIONFRAME, 
    SETOBSERVATIONFRAMESPEED,
    SETOUTPUTFILE,
    SETPERIODICFUNCTION,
    SETPOSITION,
    SETPOWERON,
    SETSPEED,
    SETSPEEDFACTOR,
    SETTEXTURE,
    SETTEXTUREFORCE,
    SETTIMEOUTVALUE,
    SETTIMESTEP,
    STARTLOOP,
    STOPLOOP,
    WAITFORSYNCH, 
    TRAJRECORDSTART, 
    TRAJRECORDSTOP, 
    TRAJSAMPLES, 
    TRAJTIMESTEP, 
    VMSETTYPE, 
    VMPARAMETERTYPE, 
    VMACTIVATE, 
    VMDEACTIVATE, 
    VMSETMAXBOUNDS, 
    VMSETMINBOUNDS, 
    VMSETBASEFRAME, 
    STARTTRAJSAMPLING, 
    SATURATETORQUE, 
    PHYSICALPOSITION, 
    AVATARPOSITION, 
    VMSETTRANSPARENTMODE, 
    VMSETCARTESIANPOSITION, 
    VMSETBASEFRAMETOCURRENTFRAME, 
    RGBTOGRAYSCALE, 
    VMGETBASEFRAME, 
    WAITBUTTON, 
    GETTIMESTEP, 
    VMSETROBOTMODE, 
    VMSAVESPLINE, 
    VMLOADSPLINE, 
    VMDELETESPLINE, 
    VMUPPERBOUND, 
    DISABLECONTROLCONNEXION, 
    BOUNDS, 
    ALARM, 
    SETTACTEL,
    ACTIVESPEEDCONTROL,
    DESACTIVESPEEDCONTROL,
    SHIFTPOSITION,
    FRICTION,
	MOUSE,
	DEBUGFILE,
	CENTERSPEEDCONTROL,
	DEPLTOMATRIX,
	MATRIXTODEPL,
	AXEROTATION,
	GETADC,
	GETTRACKBALL,
	GETTRACKBALLBUTTON,
	SETABSOLUTEPOSITION,
	BEEPONLIMIT,
	ENABLEFORCEFEEDBACK,
	PHYSICALSPEED,
	FORCESHIFTBUTTON,
	ADDPHYSICALFORCE,
	BREAKDOWN,
	SETARTICULARPOSITIONOFADDITIONALAXE,
	GETARTICULARPOSITIONOFADDITIONALAXE,
	SETARTICULARSPEEDOFADDITIONALAXE,
	GETARTICULARSPEEDOFADDITIONALAXE,
	SETARTICULARFORCEOFADDITIONALAXE,
	SETARTICULARPOSITION,
	GETARTICULARPOSITION,
	SETARTICULARSPEED,
	GETARTICULARSPEED,
	SETARTICULARFORCE,
	ACTIVEROTATIONSPEEDCONTROL,
	DESACTIVEROTATIONSPEEDCONTROL,
	CONTROLERVERSION,
	ISINSPEEDCONTROL,
	FORCEINSPEEDCONTROL,
	TORQUEINSPEEDCONTROL,
	SETGRIPPERCOMMANDTYPE,
	OUTPUTSSETTING,
	DEVICEID,

  } virtDLLFunction;

  extern int virtCallDLL(virtDLLFunction, ...);
  extern int virtLoadDLL(char *path);



#if !defined(VIRTUOSEAPI_DLLEXPORTS)

  inline int virtActiveRotationSpeedControl(VirtContext VC, float angle, float speedFactor) { return virtCallDLL(ACTIVEROTATIONSPEEDCONTROL,VC, &angle, &speedFactor); }
  inline int virtActiveSpeedControl(VirtContext VC, float radius, float speedFactor) { return virtCallDLL(ACTIVESPEEDCONTROL,VC, &radius, &speedFactor); }
  inline int virtAddForce(VirtContext VC, float *force) { return virtCallDLL(ADDPHYSICALFORCE,VC,force); }
  inline int virtAPIVersion(int *major, int *minor) { return virtCallDLL(APIVERSION, major, minor); }
  inline int virtAttachQSVO(VirtContext VC, float *Ks, float *Bs) { return virtCallDLL(ATTACHQSVO,VC,Ks,Bs); }
  inline int virtAttachVO(VirtContext VC, float mass, float *mxmymz) { return virtCallDLL(ATTACHVO,VC,&mass,mxmymz); }
  inline int virtAttachVOAvatar(VirtContext VC, float mass, float *mxmymz) { return virtCallDLL(ATTACHVOAVATAR,VC,&mass,mxmymz); }
  inline int virtClose(VirtContext VC) { return virtCallDLL(CLOSE,VC); }
  inline int virtConvertDeplToHomogeneMatrix(VirtContext VC, float* d, float* m) { return virtCallDLL(DEPLTOMATRIX,VC,d,m); } 
  inline int virtConvertHomogeneMatrixToDepl(VirtContext VC, float* d, float* m) { return virtCallDLL(MATRIXTODEPL,VC,d,m); } 
  inline int virtConvertRGBToGrayscale (VirtContext VC, float *rgb, float *gray) { return virtCallDLL(RGBTOGRAYSCALE,VC,rgb,gray); } 
  inline int virtDeactiveRotationSpeedControl(VirtContext VC) { return virtCallDLL(DESACTIVEROTATIONSPEEDCONTROL,VC); }
  inline int virtDeactiveSpeedControl(VirtContext VC) { return virtCallDLL(DESACTIVESPEEDCONTROL,VC); }
  inline int virtDetachVO(VirtContext VC) { return virtCallDLL(DETACHVO,VC); }
  inline int virtDetachVOAvatar(VirtContext VC) { return virtCallDLL(DETACHVOAVATAR,VC); }
  inline int virtDisableControlConnexion(VirtContext VC, int disable) { return virtCallDLL(DISABLECONTROLCONNEXION,VC, &disable); } 
  inline int virtDisplayHardwareStatus(VirtContext VC, FILE *fichier) { return virtCallDLL(DISPLAYHARDWARESTATUS,VC,fichier); }
  inline int virtEnableForceFeedback(VirtContext VC, int enable) { return virtCallDLL(ENABLEFORCEFEEDBACK,VC, &enable); }
  inline int virtForceShiftButton(VirtContext VC, int forceShiftButton) { return virtCallDLL(FORCESHIFTBUTTON,VC, &forceShiftButton); }
  inline int virtGetADC (VirtContext VC, int line, float* adc) { return virtCallDLL(GETADC,VC,&line,adc); } 
  inline int virtGetAlarm(VirtContext VC, unsigned int *alarm) { return virtCallDLL(ALARM, VC, alarm); } 
  inline int virtGetArticularPosition(VirtContext VC, float *pos) { return virtCallDLL(GETARTICULARPOSITION,VC,pos); } 
  inline int virtGetArticularPositionOfAdditionalAxe(VirtContext VC, float *pos) { return virtCallDLL(GETARTICULARPOSITIONOFADDITIONALAXE,VC,pos); } 
  inline int virtGetArticularSpeed(VirtContext VC, float *speed) { return virtCallDLL(GETARTICULARSPEED,VC,speed); } 
  inline int virtGetArticularSpeedOfAdditionalAxe(VirtContext VC, float *speed) { return virtCallDLL(GETARTICULARSPEEDOFADDITIONALAXE,VC,speed); } 
  inline int virtGetAvatarPosition (VirtContext VC, float *pos) { return virtCallDLL(AVATARPOSITION,VC,pos); } 
  inline int virtGetAxisOfRotation(VirtContext VC, float* axe) { return virtCallDLL(AXEROTATION,VC,axe); } 
  inline int virtGetBaseFrame(VirtContext VC, float *base) { return virtCallDLL(GETBASEFRAME,VC,base); }
  inline int virtGetButton(VirtContext VC, int button_number, int *state) { return virtCallDLL(GETBUTTON,VC,&button_number,state); }
  inline int virtGetCatchFrame(VirtContext VC, float *frame) { return virtCallDLL(GETCATCHFRAME,VC,frame); }
  inline int virtGetCenterSphere(VirtContext VC, float* pos) { return virtCallDLL(CENTERSPEEDCONTROL,VC,pos); } 
  inline int virtGetCommandType(VirtContext VC, VirtCommandType *type) { return virtCallDLL(GETCOMMANDTYPE,VC,type); }
  inline int virtGetControlerVersion(VirtContext VC, int *major, int *minor) { return virtCallDLL(CONTROLERVERSION,VC,major,minor); }
  inline int virtGetDeadMan(VirtContext VC, int *dead_man) { return virtCallDLL(GETDEADMAN,VC,dead_man); }
  inline int virtGetDeviceID(VirtContext VC, int *device_type, int *serial_number) { return virtCallDLL(DEVICEID, VC, device_type, serial_number); }
  inline int virtGetEmergencyStop(VirtContext VC, int *emergency_stop) { return virtCallDLL(GETEMERGENCYSTOP,VC,emergency_stop); }
  inline int virtGetError(VirtContext VC,int *error) { return virtCallDLL(GETERROR,VC,error); }
  inline int virtGetErrorCode(VirtContext VC) { return virtCallDLL(GETERRORCODE,VC); }
  inline char *virtGetErrorMessage(int code) { return (char *)virtCallDLL(GETERRORMESSAGE,&code); }
  inline int virtGetFailure(VirtContext VC, unsigned int *error) { return virtCallDLL(BREAKDOWN, VC, error); } 
  inline int virtGetForce(VirtContext VC, float *force) { return virtCallDLL(GETFORCE,VC,force); }
  inline int virtGetForceFactor(VirtContext VC, float *force_factor) { return virtCallDLL(GETFORCEFACTOR, VC, force_factor); }
  inline int virtGetIndexingMode(VirtContext VC, VirtIndexingType *indexing_mode) { return  virtCallDLL(GETINDEXINGMODE,VC,indexing_mode); }
  inline int virtGetMouseState(VirtContext VC, int* actif, int* clic_gauche, int* clic_droit) { return virtCallDLL(MOUSE,VC,actif,clic_gauche,clic_droit); }
  inline int virtGetObservationFrame(VirtContext VC, float *obs) { return virtCallDLL(GETOBSERVATIONFRAME,VC,obs); }
  inline int virtGetPhysicalPosition (VirtContext VC, float *pos) { return virtCallDLL(PHYSICALPOSITION,VC,pos); } 
  inline int virtGetPhysicalSpeed(VirtContext VC, float *speed) { return virtCallDLL(PHYSICALSPEED, VC, speed); }
  inline int virtGetPosition(VirtContext VC, float *pos) { return virtCallDLL(GETPOSITION,VC,pos); }
  inline int virtGetPowerOn(VirtContext VC, int *power) { return virtCallDLL(GETPOWERON,VC,power); }
  inline int virtGetSpeed(VirtContext VC, float *speed) { return virtCallDLL(GETSPEED, VC, speed); }
  inline int virtGetSpeedFactor(VirtContext VC, float *speed_factor) { return virtCallDLL(GETSPEEDFACTOR, VC, speed_factor); }
  inline int virtGetTimeLastUpdate (VirtContext VC, unsigned int *time) { return virtCallDLL(GETTIMELASTUPDATE,VC,time); }
  inline int virtGetTimeoutValue(VirtContext VC,float *time_value) { return virtCallDLL(GETTIMEOUTVALUE,VC,time_value); }
  inline int virtGetTimeStep(VirtContext VC, float* step) { return virtCallDLL(GETTIMESTEP,VC,step); } 
  inline int virtGetTrackball(VirtContext VC, int* x_move, int* y_move) { return virtCallDLL(GETTRACKBALL,VC,x_move,y_move); } 
  inline int virtGetTrackballButton(VirtContext VC, int* actif, int* btn_gauche, int* btn_milieu, int* btn_droit) { return virtCallDLL(GETTRACKBALLBUTTON,VC,actif,btn_gauche,btn_milieu,btn_droit); } 
  inline int virtIsInBounds(VirtContext VC, unsigned int *bounds) { return virtCallDLL(BOUNDS, VC, bounds); } 
  inline int virtIsInShiftPosition(VirtContext VC, int* decalage) { return virtCallDLL(SHIFTPOSITION,VC,decalage); }
  inline int virtIsInSpeedControl(VirtContext VC, int *translation, int *rotation) { return virtCallDLL(ISINSPEEDCONTROL,VC,translation,rotation); }
  inline VirtContext virtOpen(const char *nom) { return (VirtContext)virtCallDLL(OPEN,nom); }
  inline int virtOutputsSetting(VirtContext VC, unsigned int outputs) { return virtCallDLL(OUTPUTSSETTING,VC,&outputs); }
  inline int virtSaturateTorque (VirtContext VC, float forceThreshold, float momentThreshold) { return virtCallDLL(SATURATETORQUE,VC,&forceThreshold,&momentThreshold); } 
  inline int virtSetArticularForce(VirtContext VC, float *force) { return virtCallDLL(SETARTICULARFORCE,VC,force); }
  inline int virtSetArticularForceOfAdditionalAxe(VirtContext VC, float *effort) { return virtCallDLL(SETARTICULARFORCEOFADDITIONALAXE,VC,effort); }
  inline int virtSetArticularPosition(VirtContext VC, float *pos) { return virtCallDLL(SETARTICULARPOSITION,VC,pos); }
  inline int virtSetArticularPositionOfAdditionalAxe(VirtContext VC, float *pos) { return virtCallDLL(SETARTICULARPOSITIONOFADDITIONALAXE,VC,pos); }
  inline int virtSetArticularSpeed(VirtContext VC, float *speed) { return virtCallDLL(SETARTICULARSPEED,VC,speed); }
  inline int virtSetArticularSpeedOfAdditionalAxe(VirtContext VC, float *speed) { return virtCallDLL(SETARTICULARSPEEDOFADDITIONALAXE,VC,speed); }
  inline int virtSetBaseFrame(VirtContext VC, float *base) { return virtCallDLL(SETBASEFRAME,VC,base); }
  inline int virtSetCatchFrame(VirtContext VC, float *frame) { return virtCallDLL(SETCATCHFRAME,VC,frame); }
  inline int virtSetCommandType(VirtContext VC, VirtCommandType type) { return virtCallDLL(SETCOMMANDTYPE,VC,&type); }
  inline int virtSetDebugFlags(VirtContext VC, unsigned short flag) { return virtCallDLL(SETDEBUGFLAGS,VC,&flag); }
  inline int virtSetForce(VirtContext VC, float *force) { return virtCallDLL(SETFORCE,VC,force); }
  inline int virtSetForceFactor(VirtContext VC, float force_factor) { return virtCallDLL(SETFORCEFACTOR, VC, &force_factor); }
  inline int virtSetForceInSpeedControl(VirtContext VC, float force) { return virtCallDLL(FORCEINSPEEDCONTROL,VC, &force); }
  inline int virtSetGripperCommandType(VirtContext VC, VirtGripperCommandType type) { return virtCallDLL(SETGRIPPERCOMMANDTYPE,VC,&type); }
  inline int virtSetIndexingMode(VirtContext VC, VirtIndexingType indexing_mode) { return  virtCallDLL(SETINDEXINGMODE,VC,&indexing_mode); }
  inline int virtSetObservationFrame(VirtContext VC, float *obs) { return virtCallDLL(SETOBSERVATIONFRAME,VC,obs); }
  inline int virtSetObservationFrameSpeed(VirtContext VC, float *speed) { return virtCallDLL(SETOBSERVATIONFRAMESPEED,VC,speed); } 
  inline int virtSetOutputFile(VirtContext VC, char *name) { return virtCallDLL(SETOUTPUTFILE, VC, name); }
  inline int virtSetPeriodicFunction(VirtContext VC, void (*fn)(VirtContext, void *), float *period, void *arg) { return virtCallDLL(SETPERIODICFUNCTION,VC,fn,period,arg); }
  inline int virtSetPosition(VirtContext VC, float *pos) { return virtCallDLL(SETPOSITION,VC,pos); }
  inline int virtSetPowerOn(VirtContext VC, int power) { return virtCallDLL(SETPOWERON,VC,&power); }
  inline int virtSetSpeed(VirtContext VC, float *speed) { return virtCallDLL(SETSPEED, VC, speed); }
  inline int virtSetSpeedFactor(VirtContext VC, float speed_factor) { return virtCallDLL(SETSPEEDFACTOR, VC, &speed_factor); }
  inline int virtSetTexture(VirtContext VC, float *position,float *intensite, int reinit) { return virtCallDLL(SETTEXTURE, VC, position,intensite, &reinit); } 
  inline int virtSetTextureForce(VirtContext VC, float *texture_force) { return virtCallDLL(SETTEXTUREFORCE, VC, texture_force); }
  inline int virtSetTimeoutValue(VirtContext VC,float time_value) { return virtCallDLL(SETTIMEOUTVALUE,VC,&time_value); }
  inline int virtSetTimeStep(VirtContext VC, float step) { return virtCallDLL(SETTIMESTEP, VC, &step); }
  inline int virtSetTorqueInSpeedControl(VirtContext VC, float torque) { return virtCallDLL(TORQUEINSPEEDCONTROL,VC, &torque); }
  inline int virtStartLoop (VirtContext VC) { return virtCallDLL(STARTLOOP,VC); }
  inline int virtStopLoop (VirtContext VC) { return virtCallDLL(STOPLOOP,VC); }
  inline int virtTrajRecordStart (VirtContext VC) { return virtCallDLL(TRAJRECORDSTART, VC); } 
  inline int virtTrajRecordStop (VirtContext VC) { return virtCallDLL(TRAJRECORDSTOP, VC); } 
  inline int virtTrajSetSamplingTimeStep (VirtContext VC, float timeStep, unsigned int *recordTime) { return virtCallDLL(TRAJTIMESTEP, VC, &timeStep, recordTime); } 
  inline int virtVmActivate (VirtContext VC) { return virtCallDLL(VMACTIVATE, VC); } 
  inline int virtVmDeactivate (VirtContext VC) { return virtCallDLL(VMDEACTIVATE, VC); } 
  inline int virtVmDeleteSpline(VirtContext VC, char *file_name)  { return virtCallDLL(VMDELETESPLINE,VC,file_name); } 
  inline int virtVmGetBaseFrame (VirtContext VC, float *base) { return virtCallDLL(VMGETBASEFRAME,VC,base); } 
  inline int virtVmGetTrajSamples (VirtContext VC, float* samples) { return virtCallDLL(TRAJSAMPLES, VC, samples); } 
  inline int virtVmLoadSpline(VirtContext VC, char *file_name)  { return virtCallDLL(VMLOADSPLINE,VC,file_name); } 
  inline int virtVmSaveCurrentSpline(VirtContext VC, char *file_name)  { return virtCallDLL(VMSAVESPLINE,VC,file_name); } 
  inline int virtVmSetBaseFrame (VirtContext VC, float *base) { return virtCallDLL(VMSETBASEFRAME,VC,base); } 
  inline int virtVmSetBaseFrameToCurrentFrame (VirtContext VC) { return virtCallDLL(VMSETBASEFRAMETOCURRENTFRAME,VC); } 
  inline int virtVmSetDefaultToCartesianPosition (VirtContext VC) { return virtCallDLL(VMSETCARTESIANPOSITION,VC); } 
  inline int virtVmSetDefaultToTransparentMode (VirtContext VC) { return virtCallDLL(VMSETTRANSPARENTMODE,VC); } 
  inline int virtVmSetRobotMode(VirtContext VC, int OnOff) { return virtCallDLL(VMSETROBOTMODE,VC,&OnOff); }
  inline int virtVmSetType (VirtContext VC, VirtVmType type) { return virtCallDLL(VMSETTYPE, VC, &type); }
  inline int virtVmStartTrajSampling (VirtContext VC, unsigned int nbSamples) { return virtCallDLL(STARTTRAJSAMPLING, VC, &nbSamples); }
  inline int virtVmWaitUpperBound(VirtContext VC) { return virtCallDLL(VMUPPERBOUND,VC); }
  inline int virtWaitPressButton(VirtContext VC, int button_number) { return virtCallDLL(WAITBUTTON,VC,&button_number); }


#endif /* VIRTUOSEAPI_DLLEXPORTS */

#define VIRT_E_NO_ERROR					0
#define VIRT_E_OUT_OF_MEMORY			1
#define VIRT_E_COMMUNICATION_FAILURE	2
#define VIRT_E_INVALID_CONTEXT			3
#define VIRT_E_FILE_NOT_FOUND			4
#define VIRT_E_WRONG_FORMAT				5
#define VIRT_E_TIME_OUT					6
#define VIRT_E_NOT_IMPLEMENTED			7
#define VIRT_E_VARIABLE_NOT_AVAILABLE	8
#define VIRT_E_INCORRECT_VALUE			9
#define VIRT_E_SYNTAX_ERROR				10
#define VIRT_E_HARDWARE_ERROR			11
#define VIRT_E_POSITION_DISCONTINUITY	12
#define VIRT_E_VIRTUOSE_DLL_NOT_FOUND	13
#define VIRT_E_PERIODIC_FUNCTION		14
#define VIRT_E_PERFORMANCE_COUNTER		15
#define VIRT_E_MAJOR_MINOR_VERSION		16
#define VIRT_E_WRONG_MODE				17
#define VIRT_E_MODE_NOT_SUPPORTED		18 
#define VIRT_E_CALL_TIME				19 
#define VIRT_E_INCOMPATIBLE_VERSION		20 
#define VIRT_E_INCORRECT_VM_TYPE		21 
 
 
#define VIRT_BOUND_LEFT_AXE_1			0x0001 
#define VIRT_BOUND_RIGHT_AXE_1			0x0002 
#define VIRT_BOUND_SUP_AXE_2			0x0004 
#define VIRT_BOUND_INF_AXE_2			0x0008 
#define VIRT_BOUND_SUP_AXE_3			0x0010 
#define VIRT_BOUND_INF_AXE_3			0x0020 
#define VIRT_BOUND_RIGHT_AXE_4			0x0040 
#define VIRT_BOUND_LEFT_AXE_4			0x0080 
#define VIRT_BOUND_SUP_AXE_5			0x0100 
#define VIRT_BOUND_INF_AXE_5			0x0200 
#define VIRT_BOUND_LEFT_AXE_6			0x0400 
#define VIRT_BOUND_RIGHT_AXE_6			0x0800 
#define VIRT_BOUND_INF_AXE_2_3			0x1000 
#define VIRT_BOUND_SUP_AXE_2_3			0x2000 
 
 
#define	VIRT_ALARM_OVERHEAT				0x00004000 
#define VIRT_ALARM_SATURATE				0x00008000
#define VIRT_ALARM_CALLBACK_OVERRUN		0x00020000 
#define VIRT_ALARM_ERROR_POSITION		0x00040000 
#define VIRT_ALARM_LOW_BATTERY			0x00100000
 

#define VIRT_BREAKDOWN_MOTOR_1			0x0001
#define VIRT_BREAKDOWN_MOTOR_2			0x0002
#define VIRT_BREAKDOWN_MOTOR_3			0x0004
#define VIRT_BREAKDOWN_MOTOR_4			0x0008
#define VIRT_BREAKDOWN_MOTOR_5			0x0010
#define VIRT_BREAKDOWN_MOTOR_6			0x0020
#define VIRT_BREAKDOWN_MOTOR_7			0x0040
#define VIRT_BREAKDOWN_MOTOR_8			0x0080


#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* _VirtuoseAPI_h */
