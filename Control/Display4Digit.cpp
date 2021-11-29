// 
// 
// 

#include "Display4Digit.h"

bool debug;
bool _dot;
bool _switching;
uint8_t _showingMinutes;

unsigned long _showInterval;

Display4Digit::Display4Digit(int SCLK, int RCLK, int DIO, bool debugArg)
{
	debug = debugArg;
	_display.Initialize(SCLK, RCLK, DIO);
}

void Display4Digit::Draw()
{
	_display.timerIsr();
}

void Display4Digit::Prepare(unsigned long millis)
{
	uint8_t delay = 10;

	switch (_showData)
	{
	case Clock:
		if (_time.minute() != _showingMinutes || _switching)
		{
			_display.clear();
			_dot = false;
			ShowClock();
			Tick();
		}
		else {
			Tick();
		}

		if (debug)
		{
			ToSerial(_time);
		}

		delay = 10;
		break;
	case Temperature:
		_display.clear();
		ShowTemperature();
		delay = 5;
		break;
	default:
		break;
	}

	_switching = CheckInterval(millis, delay);
}

bool Display4Digit::CheckInterval(unsigned long mills, uint8_t delay)
{
	//если пройденное время стало больше интервала, то переключаем
	if ((mills / 1000) >= (_showInterval / 1000 + delay))
	{
		_manualShow = false;
		_showInterval = millis();

		unsigned c = _showData;
		c++;
		if (c == End)
		{
			c = Clock;
		}
		_showData = (ShowDataEnum)c;

		return true;
	}
	return false;
}

void Display4Digit::SetTime(DateTime date)
{
	_time = date;
}

void Display4Digit::SetTemperature(float temperature)
{
	_temperature = temperature;
}

void Display4Digit::SetShow(ShowDataEnum show)
{
	_manualShow = true;
	_showInterval = millis();
	_showData = show;
}

void Display4Digit::SetDefault(ShowDataEnum show)
{
	_manualShow = false;
	_showInterval = millis();
	_showData = show;
}

void Display4Digit::ShowTemperature()
{
	if (_temperature < 0)
	{
		_display.dispFloat(_temperature, 4);
	}
	else{
		//отсекаем хвост
		int c = _temperature;
		//определяем хвост
		float d = _temperature - c;
		int f = d * 10;

		if ((d * 100 - f * 10) >= 5)
		{
			f++;
		}

		if (c < 10)
		{
			_display.setDigit(c, 1);
		}
		else {
			_display.digit2(c, 1);
		}
		_display.setDot(1);
		_display.setDigit(f, 0);
	}
}

//Вывести время на дисплей
void Display4Digit::ShowClock()
{
	_showingMinutes = _time.minute();

	_display.digit2(_time.hour(), 2);
	_display.digit2(_showingMinutes, 0);
}

void Display4Digit::Tick()
{
	_dot = !_dot;
	_display.clockTick(_dot);
}

void Display4Digit::ToSerial(DateTime date)
{
	Serial.print(To(date.day()));
	Serial.print("-");
	Serial.print(To(date.month()));
	Serial.print("-");
	Serial.print(To(date.year()));
	Serial.print("  ");

	Serial.print(To(date.hour()));
	Serial.print(":");
	Serial.print(To(date.minute()));
	Serial.print(":");
	Serial.println(To(date.second()));
}

String Display4Digit::To(uint16_t c)
{
	String str = String(c, DEC);

	while (str.length() < 2)
	{
		str = '0' + str;
	}
	return str;
}