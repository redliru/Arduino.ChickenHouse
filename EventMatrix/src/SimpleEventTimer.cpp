// 
// Простой таймер с указанием начала и окончания работы (события включены)
// 

#include "SimpleEventTimer.h"

SimpleEventTimer::SimpleEventTimer(TimeSpan start, TimeSpan stop)
{
	_start = start;
	_stop = stop;
}

void SimpleEventTimer::Enable()
{
	_enable = true;
}

void SimpleEventTimer::Disable()
{
	_enable = false;
}

bool SimpleEventTimer::IsWork()
{
	return _enable;
}

void SimpleEventTimer::Start()
{
	Enable();
	StartAction();
}

void SimpleEventTimer::Stop()
{
	Disable();
	StopAction();
}

bool SimpleEventTimer::Work(TimeSpan *time)
{
	if (_start.totalseconds() <= time->totalseconds() && time->totalseconds() <= _stop.totalseconds())
	{
		return true;
	}
	return false;
}
