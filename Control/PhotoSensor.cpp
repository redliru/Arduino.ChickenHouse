// 
// 
// 

#include "PhotoSensor.h"

PhotoSensor::PhotoSensor(const uint8_t port, const uint16_t min, const uint16_t max) : _address(port), _min(min), _max(max)
{
	pinMode(_address, INPUT);
}

uint16_t PhotoSensor::Value()
{
	int a = analogRead(_address);

	return a +_correction;
	
	//const uint8_t COUNT = 5;

	//// считываем точное напряжение
	//float curVoltage = 0.0;
	//for (uint8_t i = 0; i < COUNT; i++) {
	//	curVoltage = curVoltage + analogRead(_address);
	//	delay(10);
	//}

	//curVoltage = curVoltage / COUNT;

	//return curVoltage + _correction;
}

void PhotoSensor::CorrectionValue(uint16_t value)
{
	_correction = value;
}

PhotoLevelEnum PhotoSensor::Level()
{
	uint16_t val = Value();
	if (val < _min) {
		return PhotoLevelMin;
	}
	else if (val > _max)
	{
		return PhotoLevelMax;
	}
	else {
		return PhotoLevelAvg;
	}
}
