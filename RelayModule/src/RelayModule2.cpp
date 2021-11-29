// 
// 
// 

#include "RelayModule2.h"

void RelayModule2::Load(RelayPin * relayPin, RelayModule2Enum in)
{
	RelayModule::Load(relayPin, in);
}

void RelayModule2::Load(const uint8_t in1, const uint8_t in2)
{
	_relay[Relay2IN1] = new RelayPin(in1);
	_relay[Relay2IN2] = new RelayPin(in2);

	for (short i = 0; i < Relay2All; i++)
	{
		ActiveRelay(_relay[i]);
	}
}

void RelayModule2::Action(RelayModule2Enum in, bool enable)
{
	RelayModule::Action(in, enable);
}

bool RelayModule2::IsActive(RelayModule2Enum in)
{
	return RelayModule::IsActive(in);
}

void RelayModule2::EnableRelay(RelayModule2Enum in)
{
	RelayModule::EnableRelay(in);
}

void RelayModule2::DisableRelay(RelayModule2Enum in)
{
	RelayModule::DisableRelay(in);
}
