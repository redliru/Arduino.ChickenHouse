// 
// 
// 

#include "MatrixElement.h"

bool MatrixElement::IsWork()
{
	return true;
}

bool MatrixElement::Work(TimeSpan* time)
{
	return true;
}

void MatrixElement::Debug()
{
	_debugLog = true;
}

void MatrixElement::Loop(unsigned long milliseconds)
{
	_millis = milliseconds;

	if (_millis >= (_lastLoop + Delay()))
	{
		Loop();
		_lastLoop = millis();
	}
}

