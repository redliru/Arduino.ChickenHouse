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

	//��������� ������ ������ � ������� � workingRelay
	void SetWorkingRelay(RelayModule2Enum relay);
	//��������� � ���������� ����
	void ActiveRelay(RelayModule2Enum relay, bool enable);
	//������� ��������� ������ ������
	void StatusWork();
	void StatusWork(bool write);
	//��������� ������� ���������
	uint8_t NextPozition(uint8_t current);
	float GetTemperature(DeviceAddress deviceAddress);

public:
	String Name() {
		return "HeatingControl";
	}

	//������������� ������
	void Begin();
	//�������� ���������� �������
	uint32_t Delay();
	float GetTemperature();
};
#endif

