#include "RenderWeatherData.h"
#include <iostream>

RenderWeatherData::RenderWeatherData()
{
}

void RenderWeatherData::renderWeatherData(int rowNumber)
{
	std::cout << "Rendering weather data..." << std::endl;
}

int RenderWeatherData::getRow(double temperature, double minTemperature, double temperatureRangePerRow)
{
	return static_cast<int>((temperature - minTemperature) / temperatureRangePerRow);
}
