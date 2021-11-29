/*
Name:		RelayModule4.h
Created:	08.01.2018 12:15:18
Author:	redliru
Editor:	Садырин Сергей
*/

#ifndef _RelayModule4_h
#define _RelayModule4_h

//#include <inttypes.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "RelayModule.h"

enum RelayModule4Enum { Relay4IN1 = 0, Relay4IN2 = 1, Relay4IN3 = 2, Relay4IN4 = 3, Relay4All };

class RelayModule4 : public RelayModule
{
public:
	RelayModule4() : RelayModule(4) {};

	void Load(RelayPin* relayPin, RelayModule4Enum in);
	void Load(const uint8_t in1, const uint8_t in2, const uint8_t in3, const uint8_t in4);

	void Action(RelayModule4Enum in, bool enable);
	bool IsActive(RelayModule4Enum in);
	void EnableRelay(RelayModule4Enum in);
	void DisableRelay(RelayModule4Enum in);
};
#endif

