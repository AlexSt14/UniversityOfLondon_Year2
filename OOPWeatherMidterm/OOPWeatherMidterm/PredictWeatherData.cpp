#include "PredictWeatherData.h"
#include <iostream>

//This class has been created for TASK 4 of the midterm
//To better understand how to properly implement and calculate the Weighted Moving Average, I used the following resource:
// https://www.fidelity.com/learning-center/trading-investing/technical-analysis/technical-indicator-guide/wma

PredictWeatherData::PredictWeatherData()
{
}
//Calculates a Weighted Moving Average for the selected country and the year range given to predict the temperature of the next year
//THIS CODE HAS BEEN WRITTEN BY ME WITHOUT ASSISTANCE
std::map<std::string, std::vector<Candlestick>> PredictWeatherData::predictWeather(const std::map<std::string, std::vector<Candlestick>>& data)
{
	std::map<std::string, std::vector<Candlestick>> predictedData = data;
	for (const auto& country : data) {
		double open = country.second.back().close;
		int weight{ 1 };
		int weightSum{ 0 };
		double weightedSumClose{ 0.0 };
		double weightedSumHigh{ 0.0 };
		double weightedSumLow{ 0.0 };
		double wmaClose{ 0.0 };
		double wmaHigh{ 0.0 };
		double wmaLow{ 0.0 };
		for (const auto& candle : country.second) {
			weightedSumClose += (candle.close * weight);
			weightedSumHigh += (candle.high * weight);
			weightedSumLow += (candle.low * weight);
			weightSum += weight;
			++weight;
		}
		wmaClose = calculateWMA(weightedSumClose, weightSum);
		wmaHigh = calculateWMA(weightedSumHigh, weightSum);
		wmaLow = calculateWMA(weightedSumLow, weightSum);
		Candlestick candlestick = { country.second.back().year + 1, open, wmaHigh, wmaLow, wmaClose };
		//Inserting the predicted candlestick into the map, at the end of the map
		predictedData[country.first].push_back(candlestick);
	}

	return predictedData;
}
//Calculates the WMA value
//THIS CODE HAS BEEN WRITTEN BY ME WITHOUT ASSISTANCE
double PredictWeatherData::calculateWMA(double sum, int weightSum)
{
	return sum / weightSum;
}
