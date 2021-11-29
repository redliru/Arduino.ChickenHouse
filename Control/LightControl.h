// LightControl.h

#ifndef _LightControl_h
#define _LightControl_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "SimpleEventTimer.h"
#include "RelayModule4.h"
#include "PhotoSensor.h"

class LightControl : public SimpleEventTimer
{
private:
	RelayModule4 _module;
	PhotoSensor** _sensor;
	void CheckSensors();

	bool _manual[3] = {false, false, false};

protected:
	void StartAction();
	void StopAction();
	void Loop();

public:
	LightControl(TimeSpan start, TimeSpan stop) : SimpleEventTimer(start, stop) {};

	String Name() {
		return "LightTimer";
	};

	uint32_t Delay();
	void Begin();
	void ManualRelay(RelayModule4Enum relay, bool enable);
};
#endif

