// SenseCommand.h

#ifndef _CommandLight_h
#define _CommandLight_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "CommandLine.h"
#include "LightControl.h"

class Light1Command : public CommandLine
{
private:
	LightControl& _light;
public:
	Light1Command(LightControl& light);

	void Execute(const String& val);

	// Унаследовано через CommandLine
	virtual String Description() const override;
};

class Light2Command : public CommandLine
{
private:
	LightControl& _light;
public:
	Light2Command(LightControl& light);

	void Execute(const String& val);

	// Унаследовано через CommandLine
	virtual String Description() const override;
};

class Light3Command : public CommandLine
{
private:
	LightControl& _light;
public:
	Light3Command(LightControl& light);

	void Execute(const String& val);

	// Унаследовано через CommandLine
	virtual String Description() const override;
};
#endif