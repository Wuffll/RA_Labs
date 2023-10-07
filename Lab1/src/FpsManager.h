#pragma once

#include "Timer.h"

class FpsManager
{
public:

	FpsManager();
	FpsManager(const unsigned int& fpsLimit);

	void SetFpsLimit(const unsigned int& fpsLimit);
	unsigned int GetFpsLimit() const;

	unsigned int GetCurrentFps() const;

	void Begin();
	bool TimeToGo();

private:

	unsigned int mFpsLimit = 0;
	unsigned int mCurrentFps = 0;
	double mWaitTime;
	Timer mTimer{};

};