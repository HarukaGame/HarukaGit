#pragma once
#ifndef __DEVICE_INPUT_H__
#define __DEVICE_INPUT_H__

#include "input_common.h"

class CDeviceInput {
public:
	static bool CreateInstance();
	static void SafeDestory();
	static unsigned char GetStateBit();
	static float* GetAxisValue();

	static void DeviceInputUpdat();
	static void DeviceInputRelease();

	static void SetMouseWheel(float delta);
private:
	static CDeviceInput* s_instance;
	static const unsigned char m_commandList[COMMAND_BUTTON_NUM];
	//static const unsigned char m_axisList[AXIS_NUM];
	unsigned int m_inputBit;
	float m_axisValueList[COMMAND_AXIS_NUM] = { 0 };
	float m_preMouseX = 0;
	float m_preMouseY = 0;
};

#endif // !__DEVICE_INPUT_H__
