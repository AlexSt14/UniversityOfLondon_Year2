#pragma once
#include <map>
#include <vector>
#include <string>
#include "Candlestick.h"

//This class has been created for TASK 4 of the midterm
//See the cpp file for clearly labelled sections of code written by me
class PredictWeatherData
{
public:
	PredictWeatherData();
	/*Calculates a Simple Moving Average for the selected country and the year range given to predict the temperature of the next year*/
	static std::map<std::string, std::vector<Candlestick>> predictWeather(const std::map<std::string, std::vector<Candlestick>>& data);
private:
	/*Calculates the SMA value*/
	static double calculateWMA(double sum, int weightSum);
};

