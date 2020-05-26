#include "fps_controler.h"
#include <windows.h>

CFpsController::CFpsController()
{
}

CFpsController::CFpsController(int _fps)
{
	m_fps = _fps;
	m_interval = 1.0f / _fps;
	TimerReset();
}

void CFpsController::TimerReset()
{
	m_timeCounter = 0;
	LARGE_INTEGER freqInteger;
	QueryPerformanceFrequency(&freqInteger);
	freq = freqInteger.QuadPart;

	LARGE_INTEGER startInteger;
	QueryPerformanceCounter(&startInteger);
	m_preTime = startInteger.QuadPart;

}

void CFpsController::TimeUpdate() {
	LARGE_INTEGER endInteger;
	QueryPerformanceCounter(&endInteger);
	float time = (float)(endInteger.QuadPart - m_preTime) / freq;
	m_timeCounter += time;
	m_preTime = endInteger.QuadPart;
}

bool CFpsController::TimeOver()
{
	TimeUpdate();
	bool isOver = m_timeCounter > m_interval;
	if (isOver == true) {
		ResetOverTime();
	}
	return  isOver;
}

void CFpsController::ResetOverTime()
{
	m_timeCounter -= m_interval;
}
