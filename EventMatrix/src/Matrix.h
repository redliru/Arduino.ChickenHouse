/*
 Name:		Matrix.h
 Created:	08.01.2018 16:33:42
 Author:	redliru
 Editor:	http://www.visualmicro.com
*/

#ifndef _Matrix_h
#define _Matrix_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "MatrixElement.h"
#include "RTClib.h"

class Matrix
{
private:
	uint8_t _length;
	MatrixElement** _matrix;
	uint8_t _index = 0;
	bool _debugLog;
	TimeSpan ToTimeSpan(DateTime date);

public:
	Matrix(uint8_t length, bool debugLog);
	~Matrix();

	void Add(MatrixElement* element);

	void Initialize();
	void SetTime(DateTime time);
	void Loop();
};
#endif

