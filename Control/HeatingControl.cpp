// 
// 
// 

#include "HeatingControl.h"

//диоды 1
const uint8_t LED_PIN1 = 11;
//диоды 2
const uint8_t LED_PIN2 = 12;

//шина температурных датчиков
const uint8_t ONE_WIRE_BUS = 7;

//делитель времени 60 - 1 минута
const uint8_t Time_Delimeter = 60;

//стартовое значение градации
const int8_t GRADIENT_MIN = -100;

//количество элементов для градации
const uint8_t GRADIENT_COUNT = 1;

//поддерживаемая температура
const float temperature = 22.5;
const float lowTemperature = 21.0;

//Множитель работы одного реле
const uint8_t workTimeFactor = 3;

//Количество делителей используемых при прогреве
const uint8_t heating = 10;

//рабочее время реле на основе делителя
unsigned long workTime[2] = { 0, 0 };

//время включения прогрева другого реле
unsigned long lastDelay = 0;

//признак переключения между реле
bool switching = false;

//отключаемое реле
RelayModule2Enum stoppedRelay = Relay2IN2;
RelayModule2Enum workingRelay = Relay2IN1;

//признак работы в сменном режиме
bool IsSingleWork = false;

//градация температуры
float gradient[GRADIENT_COUNT];
uint8_t pozitionGradient = 0;

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

DeviceAddress Thermometer1 = {
	0x28, 0xFF, 0xED, 0x1F, 0x68, 0x14, 0x03, 0x69 };

void HeatingControl::Begin()
{
	_module.LoadPin(2);
	_module.LoadPin(3);

	pinMode(LED_PIN1, OUTPUT);
	pinMode(LED_PIN2, OUTPUT);

	sensors.begin();
	sensors.setResolution(Thermometer1, 10);

	//инициализируем массив градаций
	for (int i = 0; i < GRADIENT_COUNT; i++)
	{
		gradient[i] = GRADIENT_MIN;
	}

	//todo: убрать
	_debugLog = false;
}

uint32_t HeatingControl::Delay()
{
	return 1000;
}

float HeatingControl::GetTemperature()
{
	float value = 0.0;

	uint8_t count = 0;
	for (uint8_t i = 0; i < GRADIENT_COUNT; i++)
	{
		if (gradient[i] != GRADIENT_MIN)
		{
			count++;
			value += gradient[i];
		}
	}
	value = value / count;

	return value;
}

void HeatingControl::Loop()
{
	StatusWork();

	float currentTemp = GetTemperature(Thermometer1);

	if (currentTemp == GRADIENT_MIN)
	{
		if (_debugLog) Serial.println();
		return;
	}

	//если текущая температура ниже нижнего порога и меньше на 0.5 желаемого, то включаем розжиг)
	if (currentTemp < lowTemperature ||
		(currentTemp >= lowTemperature && currentTemp <= (temperature - 0.75)))
	{
		if (_debugLog) Serial.print("\tfull");

		switching = false;
		lastDelay = 0;
		IsSingleWork = false;

		//включаем розжиг для поднятия температуры
		this->ActiveRelay(Relay2IN1, true);
		this->ActiveRelay(Relay2IN2, true);
		this->StatusWork(true);
	}
	else if (currentTemp <= temperature)
	{
		if (_debugLog) {
			Serial.print("\tsingle\tsw: ");
			Serial.print(switching);
		}

		if (!switching)
		{
			long different = workTime[0] - workTime[1];

			if (_debugLog) {
				Serial.print("\tdif: ");
				Serial.print(different);
			}

			//вычисляем разницу между работой и если она составлет больше 3 делителей времени переключаем
			//но необходимо время на включение, примерно 10 минут
			if (different > (workTimeFactor * Time_Delimeter) || different < (workTimeFactor * Time_Delimeter * -1))
			{
				switching = true;
				lastDelay = millis() / 1000 / Time_Delimeter;

				//если разница больше 0, то это работает первый, меньше второй
				if (different < 0)
				{
					this->SetWorkingRelay(Relay2IN2);
				}
				else
				{
					this->SetWorkingRelay(Relay2IN1);
				}
			}
			else
			{
				//если они оба выключены, то включаем первый
				if (_module.IsActive(Relay2IN1) && _module.IsActive(Relay2IN2))
				{
					this->ActiveRelay(workingRelay, true);
				}

				///если перешли из прогрева, включаем
				if (!IsSingleWork)
				{
					this->ActiveRelay(stoppedRelay, false);
					StatusWork(true);
				}
			}
		}
		else {
			unsigned long last = millis() / 1000 / Time_Delimeter - lastDelay;

			if (_debugLog) {
				Serial.print("\tL: ");
				Serial.print(last);
			}

			//если разница больше константы, то отключаем долгоиграющий
			if (last >= heating)
			{
				this->ActiveRelay(stoppedRelay, false);
				switching = false;
				lastDelay = 0;
				this->StatusWork(true);
			}
		}
		IsSingleWork = true;
	}
	else if (currentTemp > temperature)
	{
		if (_debugLog) {
			Serial.print("\toff");
		}

		switching = false;
		lastDelay = 0;
		IsSingleWork = false;

		//выключаем все
		this->ActiveRelay(Relay2IN1, false);
		this->ActiveRelay(Relay2IN2, false);
		this->StatusWork(true);
	}

	if (_debugLog) {
		Serial.println();
	}
}

//Включение работы релюхи с записью в workingRelay
void HeatingControl::SetWorkingRelay(RelayModule2Enum relay)
{
	workingRelay = relay;
	switch (relay)
	{
	case Relay2IN1:
		stoppedRelay = Relay2IN2;
		break;
	case Relay2IN2:
		stoppedRelay = Relay2IN1;
		break;
	default:
		break;
	}
	this->ActiveRelay(relay, true);
}

//включение и отключение реле
void HeatingControl::ActiveRelay(RelayModule2Enum relay, bool enable)
{
	switch (relay)
	{
	case Relay2IN1:
		digitalWrite(LED_PIN1, (enable ? HIGH : LOW));
		break;
	case Relay2IN2:
		digitalWrite(LED_PIN2, (enable ? HIGH : LOW));
		break;
	default:
		break;
	}

	if (_module.IsActive(relay) != enable)
	{
		_module.Action(relay, enable);
	}
}

//снимаем отпечаток начала работы
void HeatingControl::StatusWork()
{
	this->StatusWork(false);
}

//снимаем отпечаток начала работы
//write = true - фиксирует время для всех релюшек
void HeatingControl::StatusWork(bool write)
{
	unsigned long current = millis();

	bool state1 = _module.IsActive(Relay2IN1) || write;
	bool state2 = _module.IsActive(Relay2IN2) || write;

	unsigned long different = workTime[0] - workTime[1];

	unsigned long mlls = current / 1000 / Time_Delimeter;

	//если мы прошли максимальную отметку времени в 50 дней, то устанавливаем
	//релюхам текущее время, из-за сложности сбрасываем оба
	if (current < workTime[0] || current < workTime[1])
	{
		workTime[0] = workTime[1] = 0;
		this->StatusWork(true);
		return;
	}

	if (state1)
	{
		workTime[0] = mlls;
	}

	if (state2)
	{
		workTime[1] = mlls;
	}

	if (write)
	{
		//если разница больше нуля, то это работает второе реле, меньше первая
		//запоминаем разницу чтобы реле работали равное время
		if (different > 0)
		{
			workTime[1] = workTime[0] - different;
		}
		else {
			workTime[0] = workTime[1] - different;
		}
	}
}

//следующая позиция градиента
uint8_t HeatingControl::NextPozition(uint8_t current)
{
	current++;
	if (current >= GRADIENT_COUNT)
	{
		current = 0;
	}
	return current;
}

float HeatingControl::GetTemperature(DeviceAddress deviceAddress)
{
	sensors.requestTemperatures();

	if (!sensors.isConnected(deviceAddress)) return GRADIENT_MIN;

	float tempC = sensors.getTempC(deviceAddress);

	if (_debugLog) {
		Serial.print("S1: ");
		Serial.print(tempC);
		Serial.print(" *C");
	}

	if (tempC >= 4294967040.0)
	{
		tempC = 0;
	}

	//записали текущее значение градиента
	gradient[pozitionGradient] = tempC;

	//помечаем область в которую будим писать в след. раз
	pozitionGradient = this->NextPozition(pozitionGradient);

	float tempGradient = 0.0;

	uint8_t i = pozitionGradient;
	do {
		i = this->NextPozition(i);

		if (gradient[i] == GRADIENT_MIN)
		{
			return GRADIENT_MIN;
		}

		tempGradient += gradient[i];

		if (i == pozitionGradient)
		{
			break;
		}
	} while (true);

	tempGradient = tempGradient / GRADIENT_COUNT;

	if (_debugLog) {
		Serial.print("\tGR: ");
		Serial.print(tempGradient);
		Serial.print(" *C");
	}

	return tempGradient;
}