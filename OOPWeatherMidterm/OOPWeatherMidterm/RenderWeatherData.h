#pragma once
#include <vector>
#include <map>
#include "Candlestick.h"
#include <string>

//This class has been created for TASK 2 of the midterm

class RenderWeatherData
{
public:
	RenderWeatherData();

	/*This will render the weather data*/
	static void renderWeatherData(const std::map<std::string, std::vector<Candlestick>>& allData, double minTemp, double maxTemp);
	/*This will get the correct row for plotting candlestick parts*/
	static int getRow(double temperature, double minTemperature, double temperatureRangePerRow, int numRows);
};

