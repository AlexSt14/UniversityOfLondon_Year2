#include "FilterWeatherData.h"
#include <stdexcept>
#include <iostream>

//This class has been created for TASK 3 of the midterm

FilterWeatherData::FilterWeatherData() 
{
}
//Filter the data by country, return a data structure only containing candlesticks of that country or contries
//THIS CODE HAS BEEN WRITTEN BY ME WITHOUT ASSISTANCE
std::map<std::string, std::vector<Candlestick>> FilterWeatherData::filterDataCountry(const std::map<std::string, std::vector<Candlestick>>& data, std::vector<std::string> countries) 
{
	std::map<std::string, std::vector<Candlestick>> filteredData;
	//Filtering the data by country
	for (const auto& country : countries) {
		if (data.find(country) != data.end()) {
			filteredData.insert(*data.find(country));
		}
		else throw std::runtime_error("Invalid country!");
	}
	return filteredData;
}
//Filter the data by year range, return a data structure only containing candlesticks of that year range
//THIS CODE HAS BEEN WRITTEN BY ME WITHOUT ASSISTANCE
std::map<std::string, std::vector<Candlestick>> FilterWeatherData::filterDataYear(const std::map<std::string, std::vector<Candlestick>>& data, std::vector<std::string> years) 
{
	std::map<std::string, std::vector<Candlestick>> filteredData;
	//In case there are more than 2 elements in the vector, we will throw an exception
	if (years.size() != 2) throw std::runtime_error("Invalid year range! You must only type 2 elements, example: 2010,2019");
	//Checking if the user input is within the years range of the data
	int userStartDate = std::stoi(years[0]);
	int userEndDate = std::stoi(years[1]);
	int actualStartDate = 3000;
	int actualEndDate = 0;
	for (const auto& country : data) {
		for (const auto& candlestick : country.second) {
			actualStartDate = std::min(actualStartDate, candlestick.year);
			actualEndDate = std::max(actualEndDate, candlestick.year);
		}
	}//Throwing an exception in case user input is not within the years range of the data
	if (userStartDate < actualStartDate || userEndDate > actualEndDate) {
		throw std::runtime_error("Invalid year range! Data available only from " + std::to_string(actualStartDate) + " to " + std::to_string(actualEndDate) + ".");
	}
	//Filtering the data by year range
	for (const auto& country : data) {
		std::vector<Candlestick> candlesticks;
		for (const auto& candlestick : country.second) {
			if (candlestick.year >= std::stoi(years[0]) && candlestick.year <= std::stoi(years[1])) {
				candlesticks.push_back(candlestick);
			}
		}//Populating the map with the filtered data if the candlesticks vector is not empty
		if (!candlesticks.empty()) {
			filteredData.insert(std::make_pair(country.first, candlesticks));
		}
	}
	return filteredData;
}
//Filter the data by country and year range, return a data structure only containing candlesticks of that country or contries and year range
//THIS CODE HAS BEEN WRITTEN BY ME WITHOUT ASSISTANCE
std::map<std::string, std::vector<Candlestick>> FilterWeatherData::filterDataCountryYear(const std::map<std::string, std::vector<Candlestick>>& data, std::vector<std::string> countries, std::vector<std::string> years) 
{
	std::map<std::string, std::vector<Candlestick>> filteredData;
	try {
		filteredData = filterDataYear(filterDataCountry(data, countries), years);
	}
	catch (const std::exception& e) {
		throw e;
	}
	
	return filteredData;
}