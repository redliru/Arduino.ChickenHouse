// PhotoSensor.h

#ifndef _PhotoSensor_h
#define _PhotoSensor_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

enum PhotoLevelEnum { PhotoLevelMin = 0, PhotoLevelMax = 1, PhotoLevelAvg = 2 };

struct PhotoSensor
{
public:
	PhotoSensor(const uint8_t port, const uint16_t min, const uint16_t max);
	uint16_t Value();
	//Задание значения уровня корректировки на датчик
	void CorrectionValue(uint16_t value);
	//уровень датчика в пределах заданных значений
	PhotoLevelEnum Level();

private:
	const uint8_t _address = 0;
	uint16_t _correction = 0;
	const uint16_t _min = 500;
	const uint16_t _max = 1000;
};
#endif

