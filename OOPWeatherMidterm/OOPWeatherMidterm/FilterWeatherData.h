#pragma once
#include <map>
#include <vector>
#include <string>
#include "Candlestick.h"

//This class has been created for TASK 3 of the midterm
//See the cpp file for clearly labelled sections of code written by me
class FilterWeatherData
{
public:
	FilterWeatherData();
	/*Filter the data by country, return a data structure only containing candlesticks of that country or contries*/
	static std::map<std::string, std::vector<Candlestick>> filterDataCountry(const std::map<std::string, std::vector<Candlestick>>& data, std::vector<std::string> countries);
	/*Filter the data by year range, return a data structure only containing candlesticks of that year range*/
	static std::map<std::string, std::vector<Candlestick>> filterDataYear(const std::map<std::string, std::vector<Candlestick>>& data, std::vector<std::string> years);
	/*Filter the data by country and year range, return a data structure only containing candlesticks of that country or contries and year range*/
	static std::map<std::string, std::vector<Candlestick>> filterDataCountryYear(const std::map<std::string, std::vector<Candlestick>>& data, std::vector<std::string> countries, std::vector<std::string> years);
	std::map<std::string, std::vector<Candlestick>> filteredData;
};

