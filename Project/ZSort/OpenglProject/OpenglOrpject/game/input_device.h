#pragma once
#ifndef __INPUT_DEVICE_H__
#define __INPUT_DEVICE_H__

#define KEYBOARD_NUM (256)
#define IS_INPUT (0x80)

class CInputDevice {
public:
	static bool* GetInputState();
};


#endif // !__INPUT_DEVICE_H__
