// MatrixElement.h

#ifndef _MatrixElement_h
#define _MatrixElement_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <RTClib.h>

//базовый объект обработчика
class MatrixElement
{
private:
	unsigned long _lastLoop = 0;

protected:
	bool _debugLog = false;
	unsigned long _millis = 0;
	virtual void Loop() = 0;

public:
	virtual String Name() = 0;
	//инициализация класса
	virtual void Begin() = 0;
	void Debug();

	virtual bool IsTimer() { return false; }
	virtual bool IsEvent() { return false; }

	//задержка выполнения событий
	virtual uint32_t Delay() = 0;

	void Loop(unsigned long milliseconds);

	virtual bool IsWork();
	virtual bool Work(TimeSpan* time);
	virtual void Start() = 0;
	virtual void Stop() = 0;
};
#endif

