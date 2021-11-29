// SimpleEventTimer.h

#ifndef _SimpleEventTimer_h
#define _SimpleEventTimer_h

//#include <inttypes.h>

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Matrix.h"
#include "RTClib.h"

class SimpleEventTimer : virtual public MatrixElement
{
private:
	TimeSpan _start;
	TimeSpan _stop;
	bool _enable = false;
	void Enable();
	void Disable();

	bool IsTimer() { return true; }
	bool IsEvent() { return true; }

	bool Work(TimeSpan* time);

protected:
	SimpleEventTimer(TimeSpan start, TimeSpan stop);
	virtual void StartAction() = 0;
	virtual void StopAction() = 0;

public:
	bool IsWork();
	void Start();
	void Stop();
};
#endif

