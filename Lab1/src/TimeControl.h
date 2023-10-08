#pragma once

#include <chrono>

#define Clock std::chrono::steady_clock
#define TimePoint std::chrono::time_point<Clock>

class TimeControl
{
public:

	TimeControl();

	void Start();
	double End();

	void Stop();

	const bool& IsStarted() const;

	double DurationInSeconds();

private:

	Clock mClock{};
	TimePoint mStart;
	TimePoint mEnd;
	bool mStarted = false;

};