#ifndef __CONTROLS_H // tractortractor's added
#define __CONTROLS_H // tractortractor's added

#define iKEY_OBJECT_SIZE	2

// tractortractor's moved from "src/iscreen/controls.cpp" begin
struct iKeyControls
{
	int* keyCodes;
	int* defaultCodes;
	int* flags;

	void init(void);
	void reset(void);

	void setFlag(int id,int fl){ flags[id] |= fl; }
	void dropFlag(int id,int fl){ flags[id] &= ~fl; }
	void clearFlag(int id){ flags[id] = 0; }

	void addCode(int id,int key,int num = 0);
	void removeCode(int id,int num = 0);
	void addDefaultCode(int id,int key,int num = 0);

	int getCode(int id,int num);

	int GetID(int key);
	int CheckID(int id,int key);

	iKeyControls(void);
};
// tractortractor's moved from "src/iscreen/controls.cpp" end

enum iControlID {
	iKEY_TURN_WHEELS_LEFT	= 1,
	iKEY_TURN_WHEELS_RIGHT, 	// 2
	iKEY_MOVE_FORWARD,		// 3
	iKEY_MOVE_BACKWARD,		// 4
	iKEY_TURN_OVER_LEFT,		// 5
	iKEY_TURN_OVER_RIGHT,		// 6
	iKEY_DEVICE_ON, 		// 7
	iKEY_DEVICE_OFF,		// 8
	iKEY_ACTIVATE_KID,		// 9
	iKEY_ACCELERATION,		// 10
	iKEY_VERTICAL_THRUST,		// 11
	iKEY_INVENTORY, 		// 12
	iKEY_OPEN,			// 13
	iKEY_FIRE_WEAPON1,		// 14
	iKEY_FIRE_WEAPON2,		// 15
	iKEY_FIRE_WEAPON3,		// 16
	iKEY_FIRE_WEAPON4,		// 17
	iKEY_FIRE_ALL_WEAPONS,		// 18
	iKEY_CHANGE_TARGET,		// 19

	iKEY_FULLSCREEN,		// 20
	iKEY_REDUCE_VIEW,		// 21
	iKEY_ENLARGE_VIEW,		// 22
	iKEY_ROTATION,			// 23
	iKEY_AUTO_ZOOM, 		// 24
	iKEY_AUTO_TILT, 		// 25
	iKEY_ZOOM_IN,			// 26
	iKEY_ZOOM_OUT,			// 27
	iKEY_ZOOM_STANDART,		// 28

	iKEY_HANDBRAKE, 		// 29

	iKEY_USE_GLUEK, 		// 30
	iKEY_JOYSTICK_SWITCH,		// 31
	iKEY_SKIP_TEXT, 		// 32

	iKEY_USE_VECTOR,		// 33
	iKEY_FRAG_INFO, 		// 34
	iKEY_CHAT,			// 35

	iKEY_EXIT,			// 36

// tractortractor's added begin
	iKEY_TRACTION_AXIS, // 37
	iKEY_RUDDER_AXIS, // 38
// tractortractor's added end

	iKEY_MAX_ID
};

int iGetKeyID(int key);
int iKeyPressed(int id);
int iCheckKeyID(int id,int key);

void iInitControls(void);
void iResetControls(void);
void iInitControlObjects(void);

void iSetControlCode(int id,int key,int num = 0);
void iResetControlCode(int id,int num = 0);
int iGetControlCode(int id,int num = 0);

char* iGetJoystickButtonName(int vkey);
char* iGetMouseButtonName(int vkey);

#endif /* __CONTROLS_H */ // tractortractor's added