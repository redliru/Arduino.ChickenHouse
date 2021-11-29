/*
Name:		RelayModule.cpp
Created:	08.01.2018 12:15:18
Author:	redliru
Editor:	Садырин Сергей
*/

#include "RelayModule4.h"

void RelayModule4::Load(const uint8_t in1, const uint8_t in2, const uint8_t in3, const uint8_t in4)
{
	_relay[Relay4IN1] = new RelayPin(in1);
	_relay[Relay4IN2] = new RelayPin(in2);
	_relay[Relay4IN3] = new RelayPin(in3);
	_relay[Relay4IN4] = new RelayPin(in4);

	for (short i = 0; i < Relay4All; i++)
	{
		ActiveRelay(_relay[i]);
	}
}

void RelayModule4::Load(RelayPin * relayPin, RelayModule4Enum in)
{
	RelayModule::Load(relayPin, in);
}

void RelayModule4::Action(RelayModule4Enum in, bool enable)
{
	RelayModule::Action(in, enable);
}

bool RelayModule4::IsActive(RelayModule4Enum in)
{
	return RelayModule::IsActive(in);
}

void RelayModule4::EnableRelay(RelayModule4Enum in)
{
	RelayModule::EnableRelay(in);
}

void RelayModule4::DisableRelay(RelayModule4Enum in)
{
	RelayModule::DisableRelay(in);
}
