// EventElement.h

#ifndef _EventElement_h
#define _EventElement_h

//#include <inttypes.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Matrix.h"

class EventElement : virtual public MatrixElement
{
private:
	void Start() {};
	void Stop() {};

protected:
	const bool _isEvent = true;
	virtual void Loop() = 0;

public:
	bool IsEvent() { return true; }
};
#endif

