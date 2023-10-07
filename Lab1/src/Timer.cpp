#include "Timer.h"

Timer::Timer()
{
}

void Timer::Start()
{
	mStarted = true;
	mStart = mClock.now();
}

double Timer::End()
{
	if (!mStarted)
		return 0.0;

	mEnd = mClock.now();

	return DurationInSeconds();
}

void Timer::Stop()
{
	mStarted = false;
}

const bool& Timer::IsStarted() const
{
	return mStarted;
}

double Timer::DurationInSeconds()
{
	if (!mStarted)
		return 0.0;

	return ((std::chrono::duration<float>)(mEnd - mStart)).count();
}
