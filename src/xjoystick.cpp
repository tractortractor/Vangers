/*==========================================================================
 *
 * Functions:
 * XJoystickInit()
 * XJoystickCleanup()
 * XJoystickInput(void);
 *
 ***************************************************************************/

#define KDWIN
#define __ROUND__
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "iscreen/iscreen_options.h" // tractortractor's added
#include "../lib/xtool/xglobal.h"
#include "xjoystick.h"

// tractortractor's added begin
extern int RecorderMode;

extern Uint8 *controlsKeyboardState;
extern Uint8 *controlsControllerState;
// tractortractor's added end

SDL_GameController *ctrl = NULL;
SDL_Joystick *joy = NULL;

int JoystickMode = JOYSTICK_None;
int JoystickStickSwitchButton = VK_BUTTON_2;
int CurrentStickSwitchCode = 0;
unsigned int next_joystick_input = 0;

int JoystickAvailable = 0;
char* XJoystickLastErrorString = 0;
int XJoystickLastErrorCode = 0;
static int XJoystickErrHUsed = 1;
#define XJOYSTICK_ABORT(str,code) { if(XJoystickErrHUsed) ErrH.Abort(str,XERR_USER,code); else{ XJoystickLastErrorString = (char *)str; XJoystickLastErrorCode = code; }}

// Global State of Joystick
XJOYSTATE  XJoystickState;

// tractortractor's added begin
int XJoystickTractionSensitivity = 1;
int XJoystickRudderSensitivity = 1;
// tractortractor's added end

// tractortractor's comment: Old function. Don't use.
int JoystickWhatsPressedNow()
{
//	std::cout<<"JoystickWhatsPressedNow "<<std::endl; // tractortractor's commented
//	if(!JoystickAvailable) // tractortractor's commented
	if(JoystickAvailableCheck()) // tractortractor's added
		return 0;
	if(SDL_GetTicks() > next_joystick_input){
//		XJoystickInput(); // tractortractor's commented
		next_joystick_input = SDL_GetTicks() + 20;
		}
	if(CurrentStickSwitchCode)
		return CurrentStickSwitchCode;
	for(int i = 0;i < 32;i++)
		if(XJoystickState.rgbButtons[i])
			return VK_BUTTON_1 + i;
	return 0;
}

// tractortractor's comment: Old function. Don't use.
int isJoystickButtonPressed(int vk_code)
{
	std::cout<<"isJoystickButtonPressed "<<vk_code<<std::endl;
//	if(!JoystickAvailable) // tractortractor's commented
	if(JoystickAvailableCheck()) // tractortractor's added
		return 0;
	if(SDL_GetTicks() > next_joystick_input){
//		XJoystickInput(); // tractortractor's commented
		next_joystick_input = SDL_GetTicks() + 20;
		}
	if(vk_code & VK_BUTTON)
		return XJoystickState.rgbButtons[vk_code - VK_BUTTON_1] ? 1 : 0;
	if(vk_code & VK_STICK_SWITCH)
		return vk_code == CurrentStickSwitchCode ? 1 : 0;
	return 0;
}

//===========================================================================
// inputPrepareDevice
//
// Performs device preparation by setting the device's parameters (ie
// deadzone).
//
// Parameters:
//
// Returns:
//
//===========================================================================
static bool inputPrepareDevice(void)
{
    return true;
} //** end inputPrepareDevice()


//===========================================================================
// XJoystickInit
//
// Creates and initializes joysticks.
//
// Parameters:
//
// Returns:
//
//===========================================================================
bool XJoystickInit() {
	int i;
	
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
	SDL_JoystickEventState(SDL_ENABLE);
	SDL_GameControllerEventState(SDL_ENABLE);
	
	if(!SDL_WasInit(SDL_INIT_JOYSTICK) && SDL_InitSubSystem(SDL_INIT_JOYSTICK)) {
		std::cout<<"Unable to initialize the joystick subsystem"<<std::endl;
		return false;
	}
	
	for(i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			printf("Index \'%i\' is a compatible controller, named \'%s\'\n", i, SDL_GameControllerNameForIndex(i));
			ctrl = SDL_GameControllerOpen(i);
			joy = SDL_GameControllerGetJoystick(ctrl);
			break;
		} else {
			printf("Index \'%s\' is not a compatible controller.\n", SDL_JoystickNameForIndex(i));
		}
	}
	if (ctrl) {
		JoystickAvailable = 1;
		return true;
	}
	for(i = 0; i < SDL_NumJoysticks(); ++i) {
		joy = SDL_JoystickOpen(i);
		if (joy) {
			printf("Index \'%i\' is a compatible joystick, named \'%s\'\n", i, SDL_JoystickNameForIndex(i));
			break;
		}
	}
	if (joy) {
// tractortractor's added begin
		XJoystickState.lX = 0.0;
		XJoystickState.lY = 0.0;
		XJoystickState.rgdwPOVNum = SDL_JoystickNumHats(joy);
		if(XJoystickState.rgdwPOVNum)
			XJoystickState.rgdwPOV = new unsigned char[XJoystickState.rgdwPOVNum];
			memset(XJoystickState.rgdwPOV, 0, XJoystickState.rgdwPOVNum);
		XJoystickState.previous_lX = 0.0;
		XJoystickState.previous_lY = 0.0;
// tractortractor's added end
		JoystickAvailable = 1;
		return true;
	} else {
		return false;
	}
}

SDL_GameController *get_gamecontroller() {
	return ctrl;
}

SDL_Joystick *get_joystick() {
	return joy;
}

bool XJoystickInit_old(int ErrHUsed)
{
    JoystickAvailable = 0;
    XJoystickErrHUsed = ErrHUsed;

    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	//SDL_JoystickEventState(SDL_ENABLE);
    //SDL_JoystickEventState(SDL_IGNORE); // we will poll ourselves

    int nJoysticks = SDL_NumJoysticks();

    // FIXME: pick first
    if (nJoysticks < 1)
	return false;

	std::cout<<"Found "<<nJoysticks<<" joysticks"<<std::endl;
    joy = SDL_JoystickOpen(0);
    if (!joy)
		return false;

	std::cout<<"Init joystick: "<<SDL_JoystickNameForIndex(0)<<std::endl;
    // set joystick parameters (deadzone, etc)
    if(!inputPrepareDevice())
    {
        XJOYSTICK_ABORT("Device preparation failed\nXJoystick - Force Feedback", -1);
        return false;
    }

    // if we get here, we succeeded
    return true;
/* */
} //*** end XJoystickInit()


//===========================================================================
// XJoystickCleanup
//
// Cleans up joystick structures
//
// Parameters: none
//
// Returns: nothing
//
//===========================================================================
void XJoystickCleanup(void)
{
    //if (SDL_JoystickOpened(0) && joystick)
	//SDL_JoystickClose(joystick);
    JoystickAvailable = 0;
	delete[] XJoystickState.rgdwPOV; // tractortractor's added
	XJoystickState.rgdwPOV = NULL; // tractortractor's added
} //*** end XJoystickCleanup()

//===========================================================================
// XJoystickInput
//
// Processes data from the input device.  Uses GetDeviceState().
//
// Returns: 1 if joysticks state was updated, 0 otherwise.
//
//===========================================================================
/* // tractortractor's commented begin
int XJoystickInput()
{
//	std::cout<<"XJoystickInput"<<std::endl; // tractortractor's commented
	if(!JoystickAvailable)
		return 0;

	SDL_JoystickUpdate(); // update all open joysticks

// tractortractor's moved to "lib/xtool/xtcore.cpp" file to xtCallXKey function
//	for (int i = 0; i < SDL_JoystickNumButtons(joy) && i < 32; i++)
//	    XJoystickState.rgbButtons[i] = SDL_JoystickGetButton(joy, i);

	for (int i = 0; i < SDL_JoystickNumAxes(joy) && i < 2; i++)
	{
	    if (i == 0)
		XJoystickState.lX = SDL_JoystickGetAxis(joy, i);
	    else if (i == 1)
		XJoystickState.lY = SDL_JoystickGetAxis(joy, i);
	}

	CurrentStickSwitchCode = 0;
	if(JoystickStickSwitchButton){ // tractortractor's added
		int joy_switch_button = JoystickStickSwitchButton - VK_BUTTON_1; // tractortractor's added
//		if(JoystickStickSwitchButton && XJoystickState.rgbButtons[JoystickStickSwitchButton - VK_BUTTON_1]) // tractortractor's commented
		if(joy_switch_button < 32 && XJoystickState.rgbButtons[joy_switch_button]) // tractortractor's added
		{
			int dx = XJoystickState.lX;
			if(abs(dx) < RANGE_MAX/16)
				dx = 0;
			int dy = XJoystickState.lY;
			if(abs(dy) < RANGE_MAX/16)
				dy = 0;

			if(dy < 0){
				if(dx < 0)
					CurrentStickSwitchCode = VK_STICK_SWITCH_7;
				else
					if(dx > 0)
						CurrentStickSwitchCode = VK_STICK_SWITCH_9;
					else
						CurrentStickSwitchCode = VK_STICK_SWITCH_8;
				}
			else
				if(dy > 0){
					if(dx < 0)
						CurrentStickSwitchCode = VK_STICK_SWITCH_1;
					else
						if(dx > 0)
							CurrentStickSwitchCode = VK_STICK_SWITCH_3;
						else
							CurrentStickSwitchCode = VK_STICK_SWITCH_2;
					}
				else
					if(dx < 0)
						CurrentStickSwitchCode = VK_STICK_SWITCH_4;
					else
						if(dx > 0)
							CurrentStickSwitchCode = VK_STICK_SWITCH_6;
						else
							CurrentStickSwitchCode = VK_STICK_SWITCH_5;
			}
		} // tractortractor's added
	return 1;

} //*** end XJoystickInput()
*/ // tractortractor's commented end


bool XJoystickHandleAxisMotion_helper_gamepadStateCompare(int val1, int val2)
{
	if(val1 == 0 || val2 == 0)
		return val1 == val2;
	return (val1 < 0) == (val2 < 0);
}

// tractortractor's added begin
int XJoystickHandleAxisMotion(SDL_Event* p) // returns rec_flag
{
	if(!JoystickAvailableCheck())
		return 0;

//	std::cout << iGetOptionValue(iJOYSTICK_RUDDER_AXIS_INVERTED) << std::endl; // test
//	std::cout << iGetOptionValue(iJOYSTICK_TRACTION_AXIS_INVERTED) << std::endl; // test
	if (p->jaxis.axis == iGetControlCode(iKEY_RUDDER_AXIS,0))
		XJoystickState.lX = iGetOptionValue(iJOYSTICK_RUDDER_AXIS_INVERTED) ? -p->jaxis.value-1 : p->jaxis.value;
	if (p->jaxis.axis == iGetControlCode(iKEY_TRACTION_AXIS,0))
		XJoystickState.lY = iGetOptionValue(iJOYSTICK_TRACTION_AXIS_INVERTED) ? -p->jaxis.value-1 : p->jaxis.value;
//	std::cout << XJoystickState.lX << std::endl; // test
//	std::cout << XJoystickState.lY << std::endl; // test

	CurrentStickSwitchCode = 0;

	if(JoystickStickSwitchButtonPressed())
	{
		int dx = XJoystickState.lX;
		if(abs(dx) < -SDL_JOYSTICK_AXIS_MIN/16)
			dx = 0;
		int dy = XJoystickState.lY;
		if(abs(dy) < -SDL_JOYSTICK_AXIS_MIN/16)
			dy = 0;

		if(dy < 0){
			if(dx < 0)
				CurrentStickSwitchCode = VK_STICK_SWITCH_7;
			else
				if(dx > 0)
					CurrentStickSwitchCode = VK_STICK_SWITCH_9;
				else
					CurrentStickSwitchCode = VK_STICK_SWITCH_8;
		}
		else
			if(dy > 0){
				if(dx < 0)
					CurrentStickSwitchCode = VK_STICK_SWITCH_1;
				else
					if(dx > 0)
						CurrentStickSwitchCode = VK_STICK_SWITCH_3;
					else
						CurrentStickSwitchCode = VK_STICK_SWITCH_2;
			}
			else
				if(dx < 0)
					CurrentStickSwitchCode = VK_STICK_SWITCH_4;
				else
					if(dx > 0)
						CurrentStickSwitchCode = VK_STICK_SWITCH_6;
					else
						CurrentStickSwitchCode = VK_STICK_SWITCH_5;
	}

	// getting rid of useless action recording while playing with gamepad option
	if(JoystickMode == JOYSTICK_GamePad){
		int ret = 0;
		if(!XJoystickHandleAxisMotion_helper_gamepadStateCompare(XJoystickState.previous_lX, XJoystickState.lX)){
			ret = 1;
			XJoystickState.previous_lX = XJoystickState.lX;
		}
		if(!XJoystickHandleAxisMotion_helper_gamepadStateCompare(XJoystickState.previous_lY, XJoystickState.lY)){
			ret = 1;
			XJoystickState.previous_lY = XJoystickState.lY;
		}
		return ret;
	}
	return 1;
}

void XJoystickGetAxisPressed(int &axis_num, int &axis_inverted)
{
	axis_num = -1;
	axis_inverted = 0;
	if(!JoystickAvailableCheck())
		return;

	int numAxis = SDL_JoystickNumAxes(joy);

	if(numAxis != -1){
		for (int i = 0; i < numAxis; i++)
		{
			int axis_value = SDL_JoystickGetAxis(joy, i);
			if(abs(axis_value) >= -SDL_JOYSTICK_AXIS_MIN/16 * 15)
			{
				axis_num = i;
				if(axis_value > 0)
					axis_inverted = 1;
				return;
			}
		}
	}
}

int JoystickStickSwitchButtonPressed()
{
	if(JoystickStickSwitchButton)
	{
		if(JoystickStickSwitchButton & VK_BUTTON){
			int joy_switch_button = JoystickStickSwitchButton - VK_BUTTON_1;
			if(joy_switch_button < 32)
				return XJoystickState.rgbButtons[joy_switch_button];
		}
		else if (JoystickStickSwitchButton & SDLK_GAMECONTROLLER_BUTTON_MASK) {
			int controllerButtonNum = JoystickStickSwitchButton ^ SDLK_GAMECONTROLLER_BUTTON_MASK;
			if(controllerButtonNum < SDL_CONTROLLER_BUTTON_MAX)
				return controlsControllerState[controllerButtonNum];
		}
		else if (JoystickStickSwitchButton & SDLK_JOYSTICK_HAT_MASK) {
			int joyHatIndex = (JoystickStickSwitchButton ^ SDLK_JOYSTICK_HAT_MASK) / 10;
			int joyHatValue = (JoystickStickSwitchButton ^ SDLK_JOYSTICK_HAT_MASK) % 10;
			if(joyHatIndex < XJoystickState.rgdwPOVNum)
				return (XJoystickState.rgdwPOV[joyHatIndex] & joyHatValue);
		}
		else if (JoystickStickSwitchButton & VK_STICK_SWITCH) {
			return 0;
		}
		else if (JoystickStickSwitchButton & SDLK_SCANCODE_MASK) {
			return controlsKeyboardState[SDL_GetScancodeFromKey(JoystickStickSwitchButton)];
		}
		else {
			if(JoystickStickSwitchButton < SDL_NUM_SCANCODES)
				return controlsKeyboardState[JoystickStickSwitchButton];
		}
	}
	return 0;
}

int JoystickStickSwitchButtonCheck(int key)
{
	if(JoystickStickSwitchButton)
	{
		if(JoystickStickSwitchButton & VK_BUTTON){
			int joy_switch_button = JoystickStickSwitchButton - VK_BUTTON_1;
			if(joy_switch_button < 32)
				return JoystickStickSwitchButton == key;
//				return XJoystickState.rgbButtons[joy_switch_button];
		}
		else if (JoystickStickSwitchButton & SDLK_GAMECONTROLLER_BUTTON_MASK) {
			int controllerButtonNum = JoystickStickSwitchButton ^ SDLK_GAMECONTROLLER_BUTTON_MASK;
			if(controllerButtonNum < SDL_CONTROLLER_BUTTON_MAX)
				return JoystickStickSwitchButton == key;
//				return controlsControllerState[controllerButtonNum];
		}
		else if (JoystickStickSwitchButton & SDLK_JOYSTICK_HAT_MASK) {
			int joyHatIndex = (JoystickStickSwitchButton ^ SDLK_JOYSTICK_HAT_MASK) / 10;
			int JoystickStickSwitchButtonValue = (JoystickStickSwitchButton ^ SDLK_JOYSTICK_HAT_MASK) % 10;
			int keyValue = (key ^ SDLK_JOYSTICK_HAT_MASK) % 10;
			if(joyHatIndex < XJoystickState.rgdwPOVNum)
				return JoystickStickSwitchButtonValue & keyValue;
//				return (XJoystickState.rgdwPOV[joyHatIndex] & joyHatValue);
		}
		else if (JoystickStickSwitchButton & VK_STICK_SWITCH) {
			return 0;
		}
		else if (JoystickStickSwitchButton & SDLK_SCANCODE_MASK) {
			return JoystickStickSwitchButton == key;
//			return controlsKeyboardState[SDL_GetScancodeFromKey(JoystickStickSwitchButton)];
		}
		else {
			if(JoystickStickSwitchButton < SDL_NUM_SCANCODES)
				return JoystickStickSwitchButton == key;
		}
	}
	return 0;
}

void XJoystickSetTractionAxisSensitivity(int value)
{
	if (value < 1)
		XJoystickTractionSensitivity = 1;
	else if (value > 255)
		XJoystickTractionSensitivity = 255;
	else
		XJoystickTractionSensitivity = value;
}

void XJoystickSetRudderAxisSensitivity(int value)
{
	if (value < 0)
		XJoystickRudderSensitivity = 0;
	else if (value > 255)
		XJoystickRudderSensitivity = 255;
	else
		XJoystickRudderSensitivity = value;
}

int JoystickAvailableCheck(void)
{
	if(JoystickAvailable || RecorderMode == XRC_PLAY_MODE)
		return 1;
}
// tractortractor's added end
