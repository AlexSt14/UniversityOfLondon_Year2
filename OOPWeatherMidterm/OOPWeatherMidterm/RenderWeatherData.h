#pragma once
#include <vector>

class RenderWeatherData
{
public:
	RenderWeatherData();

	/*This will render the weather data*/
	void renderWeatherData(int rowNumber);
	/*This will get the row for the temperature*/
	static int getRow(double temperature, double minTemperature, double temperatureRangePerRow);
private:
	//Initialise a 2d vector to represent the plotted data with columns for years and rows for temperature ranges
	std::vector<std::vector<int>> plottedData;
};

