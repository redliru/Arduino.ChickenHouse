// RelayModule2.h

#ifndef _RELAYMODULE2_h
#define _RELAYMODULE2_h

//#include <inttypes.h>

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "RelayModule.h"

enum RelayModule2Enum { Relay2IN1 = 0, Relay2IN2 = 1, Relay2All };

class RelayModule2 : public RelayModule
{
 protected:

 public:
	 RelayModule2() : RelayModule(2) {};

	 void Load(RelayPin* relayPin, RelayModule2Enum in);
	 void Load(const uint8_t in1, const uint8_t in2);

	 void Action(RelayModule2Enum in, bool enable);
	 bool IsActive(RelayModule2Enum in);
	 void EnableRelay(RelayModule2Enum in);
	 void DisableRelay(RelayModule2Enum in);
};
#endif

