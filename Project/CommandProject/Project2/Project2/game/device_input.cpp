#include "device_input.h"
#include <windows.h>

#define KEY_ACTIVE	0x0080
#define KEY_NUM		(256)

CDeviceInput* CDeviceInput::s_instance;

bool IsState(BYTE* list, unsigned char state) {
	return list[state] & KEY_ACTIVE;
}


bool CDeviceInput::CreateInstance()
{
	if (s_instance == nullptr) {
		s_instance = new CDeviceInput();
	}
	if (s_instance == nullptr) {
		return false;
	}
	return true;
}

void CDeviceInput::SafeDestory()
{
	if (s_instance != nullptr) {
		delete s_instance;
	}
}

unsigned char CDeviceInput::GetStateBit() {
	return s_instance->m_inputBit;
}

float* CDeviceInput::GetAxisValue() {
	return s_instance->m_axisValueList;
}

void CDeviceInput::DeviceInputUpdat()
{
	unsigned char temp = 0;
	BYTE tempKeyList[KEY_NUM];
	GetKeyboardState(tempKeyList);
	if (IsState(tempKeyList, VK_MBUTTON)) {
		temp |= INPUT_MOUSE_MBUTTON;
	}
	if (IsState(tempKeyList, VK_RBUTTON)) {
		temp |= INPUT_MOUSE_RBUTTON;
	}
	if (IsState(tempKeyList, VK_LBUTTON)) {
		temp |= INPUT_MOUSE_LBUTTON;
	}
	if (IsState(tempKeyList, VK_MENU)) {
		temp |= INPUT_KEY_ALT;
	}
	if (IsState(tempKeyList, VK_CONTROL)) {
		temp |= INPUT_KEY_CTRL;
	}
	s_instance->m_inputBit = temp;


	//mouse
	POINT pos;
	GetCursorPos(&pos);
	float posX = (float)pos.x;
	float posY = (float)pos.y;

	s_instance->m_axisValueList[COMMAND_HORIZONTAL] = posX - s_instance->m_preMouseX;
	s_instance->m_axisValueList[COMMAND_VERTICAL] = posY - s_instance->m_preMouseY;

	s_instance->m_preMouseX = posX;
	s_instance->m_preMouseY = posY;

}

void CDeviceInput::DeviceInputRelease()
{
	s_instance->m_axisValueList[COMMAND_WHEEL] = 0;
}

void CDeviceInput::SetMouseWheel(float delta)
{
	if (s_instance == nullptr) {
		return;
	}
	s_instance->m_axisValueList[COMMAND_WHEEL] = delta;
}

//const unsigned char CDeviceInput::m_commandList[COMMAND_BUTTON_NUM] = {
//	/*CAMERA_ROTATE	 */		INPUT_KEY_ALT | INPUT_MOUSE_LBUTTON,
//	/*CAMERA_MOVE,	 */		INPUT_KEY_ALT | INPUT_MOUSE_MBUTTON,
//	/*CAMERA_ZOOM,	 */		INPUT_KEY_ALT | INPUT_MOUSE_RBUTTON,
//	/*LIGHT_ROTATE,  */		INPUT_KEY_CTRL | INPUT_MOUSE_LBUTTON
//};

//const unsigned char CDeviceInput::m_axisList[COMMAND_AXIS_NUM] = {
//	/*HORIZONTAL,	  */	INPUT_MOUSE_HORIZONTAL,
//	/*VERTICAL,		  */	INPUT_MOUSE_VERTICAL,
//	/*WHEEL,		  */	INPUT_MOUSE_WHEEL
//}