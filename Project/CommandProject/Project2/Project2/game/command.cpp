#include "command.h"
#include "device_input.h"

bool CComand::GetCommand(unsigned int _command) {
	unsigned int bit = CDeviceInput::GetStateBit();

	return (bit & commandList[_command]) == commandList[_command];
}

float CComand::GetAxis(unsigned int _command) {
	float* temp = CDeviceInput::GetAxisValue();
	return temp[_command];
}