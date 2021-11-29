/*
 Name:		RelayModule.h
 Created:	08.01.2018 12:15:18
 Author:	redliru
 Editor:	Садырин Сергей
*/

#ifndef _RelayModule_h
#define _RelayModule_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif

class RelayPin
{
private:
	bool _enable = false;

	bool _active = false;

public:
	const uint8_t _address = 13;
	RelayPin(const uint8_t& in);
	bool IsEnable();
	void Enable();
	bool Status();
	void SetLevel(bool active);
	void High();
	void Low();
};

class RelayModule
{
private:
	void LoadRelay(RelayPin* relayPin, uint8_t in);

protected:
	RelayModule(uint8_t relayCount);
	uint8_t _length = 0;
	uint8_t _index = 0;
	RelayPin** _relay;

	void ActiveRelay(RelayPin* relay);

	void Load(RelayPin* relayPin, uint8_t in);
	void Action(uint8_t in, bool enable);
	bool IsActive(uint8_t in);
	void EnableRelay(uint8_t in);
	void DisableRelay(uint8_t in);

public:
	void LoadPin(uint8_t port);
};
#endif

