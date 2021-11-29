// 
// Таймер управления светом (управляется с помощью 4-х модульного реле)
// 

#include "LightControl.h"

const uint8_t sensLength = 3;

uint32_t LightControl::Delay()
{
	return 1000;
}

void LightControl::Begin()
{
	Serial.println(" LightControl starting");

	_module.LoadPin(8);
	_module.LoadPin(9);
	_module.LoadPin(10);

	//пока 4-м реле не управляем
	//_module.LoadPin(11);

	//управляющие фоторезисторы
	_sensor = new PhotoSensor*[sensLength];

	_sensor[Relay4IN1] = new PhotoSensor(A0, 700, 950); //yellow
	_sensor[Relay4IN2] = new PhotoSensor(A1, 700, 950); //orange
	_sensor[Relay4IN3] = new PhotoSensor(A2, 700, 950); //red
}

void LightControl::ManualRelay(RelayModule4Enum relay, bool enable)
{
	if (relay > sizeof(_manual))
	{
		return;
	}
	Serial.println(enable ? "Enable" : "Disable");
	_manual[relay] = enable;
	_module.Action(relay, enable);
}

void LightControl::Loop()
{
	if (IsWork())
	{
		CheckSensors();
	}
}

void LightControl::CheckSensors()
{
	//учитываем показание всех сенсоров
	for (uint8_t i = 0; i < sensLength; i++)
	{
		//PhotoLevelEnum level = _sensor[i]->Level();

		//todo: необходимо проверить статус ручного включения реле

		if (_debugLog)
		{
			Serial.print("S:");
			Serial.print(i);
			Serial.print(" Val:");
			Serial.print(_sensor[i]->Value());
			Serial.print(" ");
		}

		//если уровень больше порога, то включаем
		/*switch (level)
		{
		case PhotoLevelMin:
			if (_debugLog)
			{
				Serial.print("Min");
			}

			if (!_module.IsActive((RelayModule4Enum)i))
			{
				_module.EnableRelay((RelayModule4Enum)i);
			}
			break;
		case PhotoLevelAvg:
			if (_debugLog)
			{
				Serial.print("Avg");
			}

			break;
		case PhotoLevelMax:
			if (_debugLog)
			{
				Serial.print("Max");
			}

			if (_module.IsActive((RelayModule4Enum)i))
			{
				_module.DisableRelay((RelayModule4Enum)i);
			}
			break;
		default:
			break;
		}*/

		if (_debugLog)
		{
			Serial.print(" ");
		}
	}

	if (_debugLog)
	{
		Serial.println();
	}
}

void LightControl::StartAction()
{
	_module.EnableRelay(Relay4All);
}

void LightControl::StopAction()
{
	_module.DisableRelay(Relay4All);
}
