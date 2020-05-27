#pragma once
#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "input_common.h"

class CComand {
public:
	static bool GetCommand(unsigned int _command);
	static float GetAxis(unsigned int _command);
private:
};

#endif // !__COMMAND_H__
