/*
 Name:		RelayModule.cpp
 Created:	08.01.2018 12:15:18
 Author:	redliru
 Editor:	Садырин Сергей
*/

#include "RelayModule.h"

RelayPin::RelayPin(const uint8_t& in) : _address(in)
{
}

bool RelayPin::IsEnable()
{
	return _enable;
}

void RelayPin::Enable()
{
	_enable = true;
	pinMode(_address, OUTPUT);
}

bool RelayPin::Status()
{
	if (!_enable) return false;

	return _active;
}

void RelayPin::SetLevel(bool active)
{
	if (_enable)
	{
		_active = active;
		digitalWrite(_address, active ? LOW : HIGH);
	}
}

void RelayPin::High()
{
	SetLevel(true);
}

void RelayPin::Low()
{
	SetLevel(false);
}

void RelayModule::LoadRelay(RelayPin * relayPin, uint8_t in)
{
	if (in < _length)
	{
		_relay[in] = relayPin;
		ActiveRelay(relayPin);
	}
}

RelayModule::RelayModule(uint8_t relayCount)
{
	_length = relayCount;
	_relay = new RelayPin*[relayCount];
}

void RelayModule::LoadPin(uint8_t in)
{
	Load(new RelayPin(in), _index);
}

void RelayModule::EnableRelay(uint8_t in)
{
	Action(in, true);
}

void RelayModule::DisableRelay(uint8_t in)
{
	Action(in, false);
}

void RelayModule::ActiveRelay(RelayPin * relay)
{
	relay->Enable();
	//задаем первоначальный уровень
	relay->Low();
}

void RelayModule::Load(RelayPin * relayPin, uint8_t in)
{
	_index++;
	LoadRelay(relayPin, in);
}

void RelayModule::Action(uint8_t in, bool enable)
{
	if (in == _length) {
		for (short i = 0; i < _length; i++)
		{
			_relay[i]->SetLevel(enable);
		}
	}
	else
	{
		_relay[in]->SetLevel(enable);
	}
}

bool RelayModule::IsActive(uint8_t in)
{
	return _relay[in]->Status();
}
