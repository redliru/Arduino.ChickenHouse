// Display4Digit.h

#ifndef _Display4Digit_h
#define _Display4Digit_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <TM74HC595Display.h>
#include <RTClib.h>

enum ShowDataEnum : byte {
	Clock = 0,
	Temperature = 1,
	End
};

class Display4Digit
{
public:
	Display4Digit(int SCLK, int RCLK, int DIO, bool debug);

	//прорисовать
	void Draw();
	//подготовить отображение
	void Prepare(unsigned long millis);
	//задать отображаемое время
	void SetTime(DateTime date);
	void SetTemperature(float temperature);
	//отображаем
	void SetShow(ShowDataEnum show);

private:
	bool _manualShow = false;
	DateTime _time;
	float _temperature = 0.0;
	ShowDataEnum _showData = Clock;
	TM74HC595Display _display;

	bool CheckInterval(unsigned long millis, uint8_t delay);
	void ToSerial(DateTime date);
	String To(uint16_t c);
	void ShowClock();
	void ShowTemperature();
	void Tick();
	void SetDefault(ShowDataEnum show);
};
#endif



