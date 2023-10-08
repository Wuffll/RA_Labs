#include "TimeControl.h"

TimeControl::TimeControl()
{
}

void TimeControl::Start()
{
	mStarted = true;
	mStart = mClock.now();
}

double TimeControl::End()
{
	if (!mStarted)
		return 0.0;

	mEnd = mClock.now();

	return DurationInSeconds();
}

void TimeControl::Stop()
{
	mStarted = false;
}

const bool& TimeControl::IsStarted() const
{
	return mStarted;
}

double TimeControl::DurationInSeconds()
{
	if (!mStarted)
		return 0.0;

	return ((std::chrono::duration<float>)(mEnd - mStart)).count();
}
