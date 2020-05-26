#pragma once

#ifndef __fps_controller_h__
#define __fps_controller_h__


class CFpsController {
public:
	CFpsController(int _fps);


	void TimerReset();
	bool TimeOver();
private:
	CFpsController();


	void TimeUpdate();
	void ResetOverTime();

	int m_fps = 60;
	float m_interval = 0;
	float m_timeCounter = 0;
	__int64 freq = 0;
	__int64 m_preTime = 0;
};

#endif // !__fps_controller_h__
