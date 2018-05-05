#ifndef _XJOYSTICK_H
#define _XJOYSTICK_H

#include <SDL_joystick.h> // tractortractor's added

//---------------------------------------------------------------------------

struct XJOYSTATE {
    long    lX;                     /* x-axis position              */
    long    lY;                     /* y-axis position              */
//    long    lZ;                     /* z-axis position              */
//    long    lRx;                    /* x-axis rotation              */
//    long    lRy;                    /* y-axis rotation              */
//    long    lRz;                    /* z-axis rotation              */
//    long    rglSlider[2];           /* extra axes positions         */
//    unsigned int   rgdwPOV[4];             /* POV directions               */
	int              rgdwPOVNum; // tractortractor's added
	unsigned char   *rgdwPOV = NULL; // tractortractor's added
    unsigned char    rgbButtons[32];         /* 32 buttons                   */
// tractortractor's added begin
	long previous_lX;
	long previous_lY;
// tractortractor's added end
};
   
extern XJOYSTATE  XJoystickState;

// tractortractor's added begin
extern int XJoystickTractionSensitivity;
extern int XJoystickRudderSensitivity;
// tractortractor's added end

// prototypes
bool XJoystickInit();
void XJoystickCleanup();
int XJoystickInput();  // updates XJoystickState if !0
// tractortractor's added begin
bool XJoystickHandleAxisMotion_helper_gamepadStateCompare(int val1, int val2);
int XJoystickHandleAxisMotion(SDL_Event* p);
void XJoystickGetAxisPressed(int &axis_num, int &axis_inverted);
int JoystickStickSwitchButtonPressed();
int JoystickStickSwitchButtonCheck(int key);
void XJoystickSetTractionAxisSensitivity(int value);
void XJoystickSetRudderAxisSensitivity(int value);
int JoystickAvailableCheck(void);
// tractortractor's added end

// tractortractor's added begin
#define JOYSTICK_MAX_USED_AXES 2
#define JOYSTICK_TRACTION_AXIS 0
#define JOYSTICK_RUDDER_AXIS 1
// tractortractor's added end

// constants used for scaling the input device
#define DEADZONE        2500            // 25% of the axis range
#define RANGE_MAX       256            // maximum positive axis value
#define RANGE_MIN       -256           // minimum negative axis value
#define FF_CHILD        5000            // "Child"          gain == 50%
#define FF_ADULT        7500            // "Adult"          gain == 75%
#define FF_BODYBUILDER  10000           // "Bodybuilder"    gain == 100%

// "effect flags" - these are internal identifiers and in no way map to DirectInput
#define EF_BOUNCE   0x00000001l
#define EF_EXPLODE  0x00000002l
#define EF_FIRE     0x00000004l

// tractortractor's added begin
#ifndef SDL_JOYSTICK_AXIS_MAX
#define SDL_JOYSTICK_AXIS_MAX   32767
#endif
#ifndef SDL_JOYSTICK_AXIS_MIN
#define SDL_JOYSTICK_AXIS_MIN   -32768
#endif
// tractortractor's added end

#define VK_BUTTON		0x100
#define VK_STICK_SWITCH	  0x200
enum {
	VK_BUTTON_1 = VK_BUTTON + 1,
	VK_BUTTON_2,
	VK_BUTTON_3,
	VK_BUTTON_4,
	VK_BUTTON_5,
	VK_BUTTON_6,
	VK_BUTTON_7,
	VK_BUTTON_8,
	VK_BUTTON_9,
	VK_BUTTON_10,
	VK_BUTTON_11,
	VK_BUTTON_12,
	VK_BUTTON_13,
	VK_BUTTON_14,
	VK_BUTTON_15,
	VK_BUTTON_16,
	VK_BUTTON_17,
	VK_BUTTON_18,
	VK_BUTTON_19,
	VK_BUTTON_20,
	VK_BUTTON_21,
	VK_BUTTON_22,
	VK_BUTTON_23,
	VK_BUTTON_24,
	VK_BUTTON_25,
	VK_BUTTON_26,
	VK_BUTTON_27,
	VK_BUTTON_28,
	VK_BUTTON_29,
	VK_BUTTON_30,
	VK_BUTTON_31,
	VK_BUTTON_32,

	VK_STICK_SWITCH_1 = VK_STICK_SWITCH + 1,
	VK_STICK_SWITCH_2,
	VK_STICK_SWITCH_3,
	VK_STICK_SWITCH_4,
	VK_STICK_SWITCH_5,
	VK_STICK_SWITCH_6,
	VK_STICK_SWITCH_7,
	VK_STICK_SWITCH_8,
	VK_STICK_SWITCH_9
};

enum {
	JOYSTICK_None,
	JOYSTICK_GamePad,
	JOYSTICK_Joystick,
	JOYSTICK_SteeringWheel
};

extern int JoystickAvailable;
extern int JoystickMode;
extern int JoystickStickSwitchButton;

int JoystickWhatsPressedNow();
int isJoystickButtonPressed(int vk_code);


SDL_GameController *get_gamecontroller();
SDL_Joystick *get_joystick();
//---------------------------------------------------------------------------

#endif //_XJOYSTICK_H
