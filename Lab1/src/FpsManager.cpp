#include "FpsManager.h"

FpsManager::FpsManager()
{
}

FpsManager::FpsManager(const unsigned int& fpsLimit)
	:
	mFpsLimit(fpsLimit),
	mWaitTime(1.0 / fpsLimit)
{
}

void FpsManager::SetFpsLimit(const unsigned int& fpsLimit)
{
	mFpsLimit = fpsLimit;
	mWaitTime = 1.0 / fpsLimit;
}

unsigned int FpsManager::GetFpsLimit() const
{
	return mFpsLimit;
}

unsigned int FpsManager::GetCurrentFps() const
{
	return mCurrentFps;
}

void FpsManager::Begin()
{
	mTimer.Start();
}

bool FpsManager::TimeToGo()
{
	if(mTimer.End() < mWaitTime)
		return false;
	
	mCurrentFps = 1.0 / mTimer.DurationInSeconds();

	return true;
}
