/*
 Name:		Matrix.cpp
 Created:	08.01.2018 16:33:42
 Author:	redliru
 Editor:	http://www.visualmicro.com
*/

#include "Matrix.h"

Matrix::Matrix(uint8_t length, bool debugLog)
{
	_length = length;
	_debugLog = debugLog;
	_matrix = new MatrixElement *[length];
}

Matrix::~Matrix()
{
	delete[] _matrix;
}

void Matrix::Add(MatrixElement * element)
{
	_matrix[_index++] = element;
	if (_debugLog)
	{
		element->Debug();
	}
}

//первичная инициализация при включении устройства (запуск пропущенных)
void Matrix::Initialize()
{
	//инициализируем все заложенные таймеры
	//также проверяем необходимость работы какого либо из имеющихся таймеров
	for (int i = 0; i < _length; i++)
	{
		MatrixElement* elem = _matrix[i];
		String name = elem->Name();

		if (_debugLog)
		{
			Serial.print("Init module:");
			Serial.println(name);
		}

		//иницализируем
		elem->Begin();
	}
}

//задание текущего времени
void Matrix::SetTime(DateTime time)
{
	TimeSpan span = ToTimeSpan(time);

	for (int i = 0; i < _length; i++)
	{
		MatrixElement* elem = _matrix[i];

		if (!elem->IsTimer()) continue;

		bool isWork = elem->IsWork();

		if (elem->Work(&span))
		{
			if (!isWork)
			{
				if (_debugLog)
				{
					Serial.print("Start: ");
					Serial.println(elem->Name());
				}
				elem->Start();
			}
		}
		else if (isWork)
		{
			if (_debugLog)
			{
				Serial.print("Stop: ");
				Serial.println(elem->Name());
			}
			elem->Stop();
		}
	}
}

void Matrix::Loop()
{
	for (int i = 0; i < _length; i++)
	{
		MatrixElement* elem = _matrix[i];

		if (!elem->IsEvent()) continue;
		
		elem->Loop(millis());
	}
}

TimeSpan Matrix::ToTimeSpan(DateTime date)
{
	return TimeSpan(0, date.hour(), date.minute(), date.second());
}