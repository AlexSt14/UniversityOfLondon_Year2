#include "PredictWeatherData.h"

PredictWeatherData::PredictWeatherData()
{
}
//Calculates a Simple Moving Average for the selected country and the year range given to predict the temperature of the next year
std::map<std::string, std::vector<Candlestick>> PredictWeatherData::predictWeather(const std::map<std::string, std::vector<Candlestick>>& data)
{
	std::map<std::string, std::vector<Candlestick>> predictedData = data;
	for (const auto& country : data) {
		double open = country.second.back().close;
		double sumClose{ 0.0 };
		double sumHigh{ 0.0 };
		double sumLow{ 0.0 };
		double smaClose{ 0.0 };
		double smaHigh{ 0.0 };
		double smaLow{ 0.0 };
		for (const auto& candle : country.second) {
			sumClose += candle.close;
			sumHigh += candle.high;
			sumLow += candle.low;
		}
		smaClose = calculateSMA(sumClose, country.second.size());
		smaHigh = calculateSMA(sumHigh, country.second.size());
		smaLow = calculateSMA(sumLow, country.second.size());
		Candlestick candlestick = { country.second.back().year + 1, open, smaHigh, smaLow, smaClose };
		//Inserting the predicted candlestick into the map, at the end of the map
		predictedData[country.first].push_back(candlestick);
	}

	return predictedData;
}
//Calculates the SMA value
double PredictWeatherData::calculateSMA(double sum, int size)
{
	return sum / size;
}
