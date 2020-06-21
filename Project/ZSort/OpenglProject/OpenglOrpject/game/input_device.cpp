#include "input_device.h"
#include <Windows.h>


bool* CInputDevice::GetInputState() {
	BYTE tempKeyTbl[KEYBOARD_NUM];
	bool retList[KEYBOARD_NUM] = { false };
	GetKeyboardState(tempKeyTbl);
	for (int i = 0; i < KEYBOARD_NUM; i++) {
		retList[i] = tempKeyTbl[i] & IS_INPUT;
	}
	return retList;
}