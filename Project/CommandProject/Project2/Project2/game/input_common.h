#pragma once
#ifndef __INPUT_COMMON_H__
#define __INPUT_COMMON_H__

#define INPUT_MOUSE_MBUTTON		0x0001
#define INPUT_MOUSE_RBUTTON		0x0002
#define INPUT_MOUSE_LBUTTON		0x0004
#define INPUT_KEY_ALT			0x0008
#define INPUT_KEY_CTRL			0x0010

#define INPUT_MOUSE_HORIZONTAL	0x0100
#define INPUT_MOUSE_VERTICAL	0x0200
#define INPUT_MOUSE_WHEEL		0x0400

//enum InputState {
//	INPUT_MOUSE_MBUTTON,
//	INPUT_MOUSE_RBUTTON,
//	INPUT_MOUSE_LBUTTON,
//	INPUT_KEY_ALT	   ,
//	INPUT_KEY_CTRL	   ,
//	INPUT_STATE_NUM
//};
//
//enum InputAxis {
//	INPUT_MOUSE_HORIZONTAL,
//	INPUT_MOUSE_VERTICAL,
//	INPUT_MOUSE_WHEEL,
//	INPUT_AXIS_NUM
//};

enum CommandButton {
	COMMAND_CAMERA_ROTATE,
	COMMAND_CAMERA_MOVE,
	COMMAND_CAMERA_ZOOM,
	COMMAND_LIGHT_ROTATE,
	COMMAND_BUTTON_NUM
};

enum CommandAxis {
	COMMAND_HORIZONTAL,
	COMMAND_VERTICAL,
	COMMAND_WHEEL,
	COMMAND_AXIS_NUM
};

const unsigned char commandList[COMMAND_BUTTON_NUM] = {
	/*CAMERA_ROTATE	 */		INPUT_KEY_ALT | INPUT_MOUSE_LBUTTON,
	/*CAMERA_MOVE,	 */		INPUT_KEY_ALT | INPUT_MOUSE_MBUTTON,
	/*CAMERA_ZOOM,	 */		INPUT_KEY_ALT | INPUT_MOUSE_RBUTTON,
	/*LIGHT_ROTATE,  */		INPUT_KEY_CTRL | INPUT_MOUSE_LBUTTON
};

#endif // !__INPUT_COMMON_H__