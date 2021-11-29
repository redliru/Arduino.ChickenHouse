#include "Matrix.h"
#include "EventElement.h"

#include "HeatingControl.h"
#include "LightControl.h"

#include "Display4Digit.h"

#include <Wire.h>
#include <RTClib.h>
#include "TimerOne.h"
#include "TimeSetCommand.h"
#include "CommandLight.h"
#include "Command.h"

#define DEBUG false
#define LED_ON 13

const byte SCLK = 6;
const byte RCLK = 5;
const byte DIO = 4;

RTC_DS3231 RTC;

//допустимые команды
Command _commands;

Display4Digit _display(SCLK, RCLK, DIO, DEBUG);
Matrix _timers(2, DEBUG);

//процедура работы обогрева
HeatingControl _heating;

//процедура работы со светом
LightControl light(TimeSpan(0, 6, 0, 0), TimeSpan(0, 21, 00, 00));

unsigned long _last = 0;

void setup() {
//#if defined(__AVR_ATmega2560__)
//	analogReference(INTERNAL2V56);
//#else
//	analogReference(INTERNAL);
//#endif

	Serial.begin(9600);

	//version
	Serial.print("Version: ");
	Serial.println("0.3.7");

	_commands.Setup(9600, 4);

	pinMode(LED_ON, OUTPUT);
	digitalWrite(LED_ON, HIGH);

	//инициализируем список доступных комманд
	_commands.Register(new TimeSetCommand(RTC));
	_commands.Register(new Light1Command(light));
	_commands.Register(new Light2Command(light));
	_commands.Register(new Light3Command(light));

	Wire.begin();

	if (!RTC.begin()) {
		Serial.println("Couldn't find RTC");
		//while (1);
	}

	if (RTC.lostPower()) {
		Serial.println("RTC lost power, lets set the time!");
		// following line sets the RTC to the date & time this sketch was compiled
		//RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
		RTC.adjust(DateTime(2018, 1, 17, 8, 00, 0));
	}

	_timers.Add(&light);
	_timers.Add(&_heating);

	_timers.Initialize();

	Timer1.initialize(1500); // set a timer of length 1500
	Timer1.attachInterrupt(TimerDraw); // attach the service routine here
}

void loop() {
	unsigned long ml = millis();

	if (_last > ml)
	{
		_last = ml;
	}

	//для работы часов необходимо каждую секунду опрашивать текущее время и задавать его
	if (ml % 1000 == 0 || ml - _last > 1000)
	{
		delay(1);

		DateTime now = RTC.now();

		//задаем время
		_display.SetTime(now);
		//задаем температуру

		float temp = _heating.GetTemperature();
		_display.SetTemperature(temp);

		//подготавливаем отображение
		_display.Prepare(ml);

		_timers.SetTime(now);
		_last = ml;
	}

	_timers.Loop();
	_commands.Read();
}

void TimerDraw()
{
	_display.Draw();
}
