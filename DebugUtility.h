// DebugUtility.h

#ifndef _DEBUGUTILITY_h
#define _DEBUGUTILITY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#define DEBUG true

#if DEBUG
#define PRINTS(s)    { Serial.print(F(s)); }
#define PRINTS(v)    { Serial.print(v); }
#define PRINTSLN(s)  { Serial.println(F(s)); }
#define PRINTSLN()   { Serial.println(); }
#define PRINT(s, v)  { Serial.print(F(s)); Serial.print(v); }
#define PRINTX(s, v) { Serial.print(F(s)); Serial.print(F("0xSerial.print(v, HEX); }
#else
#define PRINTS(s)
#define PRINT(s,v)
#define PRINTX(s,v)
#define PRINTSLN(s)
#define PRINTSLN()
#endif

#endif

