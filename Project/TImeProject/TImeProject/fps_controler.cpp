#include "fps_controler.h"
#include <windows.h>

CFpsController::CFpsController()
{
}

CFpsController::CFpsController(int _fps)
{
	SetFPS(_fps);
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

void CFpsController::SetFPS(int _fps)
{
	if (_fps > 0) {
		m_fps = _fps;
	}
	else {
		m_fps = DEFAULT_FPS;
	}
	m_interval = 1.0f / m_fps;

}

bool CFpsController::TimeOver()const
{
	return m_timeCounter > m_interval;
}

float CFpsController::GetDeltaTime() const
{
	return m_deltaTime;
}

void CFpsController::ResetOverTime()
{
	m_deltaTime = m_timeCounter - m_preResetTime;
	m_timeCounter -= m_interval;
	m_preResetTime = m_timeCounter;

}
