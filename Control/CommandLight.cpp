// 
// 
// 

#include "CommandLight.h"

Light1Command::Light1Command(LightControl & light) : CommandLine("S1"), _light(light)
{
}

void Light1Command::Execute(const String& val)
{
	if (val == "1")
	{
		_light.ManualRelay(Relay4IN1, true);
	}
	else if (val == "0")
	{
		_light.ManualRelay(Relay4IN1, false);
	}
}

String Light1Command::Description() const
{
	return String("Light relay module control.");// Set \"1\" to enable");
}

Light2Command::Light2Command(LightControl & light) : CommandLine("S2"), _light(light)
{
}

void Light2Command::Execute(const String& val)
{
	if (val == "1")
	{
		_light.ManualRelay(Relay4IN2, true);
	}
	else if (val == "0")
	{
		_light.ManualRelay(Relay4IN2, false);
	}
}

String Light2Command::Description() const
{
	return String("Light relay module control.");// Set \"1\" to enable");
}

Light3Command::Light3Command(LightControl & light) : CommandLine("S3"), _light(light)
{
}

void Light3Command::Execute(const String& val)
{
	if (val == "1")
	{
		_light.ManualRelay(Relay4IN3, true);
	}
	else if (val == "0")
	{
		_light.ManualRelay(Relay4IN3, false);
	}
}

String Light3Command::Description() const
{
	return String("Light relay module control.");// Set \"1\" to enable");
}
