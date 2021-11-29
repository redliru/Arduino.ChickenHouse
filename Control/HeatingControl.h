// HeatingControl.h

#ifndef _HeatingControl_h
#define _HeatingControl_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "EventElement.h"
#include "RelayModule2.h"

#include <OneWire.h>
#include <DallasTemperature.h>

class HeatingControl : public EventElement
{
private:
	RelayModule2 _module;

protected:
	void Loop();

	//Включение работы релюхи с записью в workingRelay
	void SetWorkingRelay(RelayModule2Enum relay);
	//включение и отключение реле
	void ActiveRelay(RelayModule2Enum relay, bool enable);
	//снимаем отпечаток начала работы
	void StatusWork();
	void StatusWork(bool write);
	//следующая позиция градиента
	uint8_t NextPozition(uint8_t current);
	float GetTemperature(DeviceAddress deviceAddress);

public:
	String Name() {
		return "HeatingControl";
	}

	//инициализация класса
	void Begin();
	//задержка выполнения событий
	uint32_t Delay();
	float GetTemperature();
};
#endif

