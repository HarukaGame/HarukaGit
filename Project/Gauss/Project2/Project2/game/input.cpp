#include "input.h"
#include <Windows.h>
#include <windowsx.h>
#include <assert.h>
#include <string>

#if DEBUG_MODE
#include <iostream>
#endif

static Input* s_instance;	//
const int m_keyNum = 256;
POINT m_windowMousePos;
BYTE m_keyTbl[m_keyNum] = {};
BYTE m_preKeyTbl[m_keyNum] = {};
const int isinput = 0x80;
HWND m_hwnd;


Input::Input(){}

Input* Input::CreateInstance() {
	if (s_instance == nullptr) {
		s_instance = new Input();
	}

	if (s_instance != NULL) {
		return s_instance;
	}
	else {
		return NULL;
	}
}

void Input::SetWnd(HWND _hwnd)
{
	m_hwnd = _hwnd;
}


void Input::DestroyInstance() {
	delete s_instance;
}


void Input::StackInput() {
	BYTE tempKeyTbl[m_keyNum];
	GetKeyboardState(tempKeyTbl);
	for (int keyIndex = 0; keyIndex < m_keyNum; keyIndex++) {
		m_keyTbl[keyIndex] = m_keyTbl[keyIndex] | tempKeyTbl[keyIndex];
	}
}

void Input::ReleaseInput() {
	memcpy(m_preKeyTbl, m_keyTbl, sizeof(m_preKeyTbl));
	GetKeyboardState(m_keyTbl);
}

bool Input::GetKey(const int key) {
	return m_keyTbl[key] & isinput;
}

bool Input::GetKeyDown(const int key) {
	return (m_keyTbl[key] & isinput) && !(m_preKeyTbl[key] & isinput);
}

bool Input::GetKeyUp(const int key) {
	return !(m_keyTbl[key] & isinput) && (m_preKeyTbl[key] & isinput);
}

POINT Input::GetMousePosition() {
	POINT pos;
	GetCursorPos(&pos);
	ScreenToClient(m_hwnd, &pos);
	return pos;
}

float Input::GetMouseWheel() {
	return 0;
}

#if DEBUG_MODE
void Input::ShowInputState(BYTE key) {
	printf("%d\n", m_keyTbl[key]);
}

#endif