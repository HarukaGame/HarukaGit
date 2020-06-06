#pragma once

#ifndef __fps_controller_h__
#define __fps_controller_h__
#define DEFAULT_FPS (60)



class CFpsController {
public:
	CFpsController(int _fps);

	void TimeUpdate();
	void SetFPS(int _fps);
	void TimerReset();
	bool TimeOver()const;
	void ResetOverTime();

	float GetDeltaTime()const;
private:
	CFpsController();
	int m_fps = DEFAULT_FPS;
	float m_interval = 0;
	float m_timeCounter = 0;
	float m_deltaTime = 0;
	__int64 freq = 0;
	__int64 m_preTime = 0;
	float m_preResetTime = 0;
};

#endif // !__fps_controller_h__
