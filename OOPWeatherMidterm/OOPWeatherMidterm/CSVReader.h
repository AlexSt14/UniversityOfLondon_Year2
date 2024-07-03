#pragma once
#include <string>
#include <vector>
#include <map>
#include "Candlestick.h"

//This class has been created for TASK 1 of the midterm

class CSVReader
{
public:
	CSVReader();
	/*Reads the weather data from the csv file and returns a map of data with country and candlestick objects*/
	static std::map<std::string, std::vector<std::pair<int, double>>> readWeatherData(std::string filename);
	/*Tokenises the csv line by separator*/
	static std::vector<std::string> tokenise(std::string csvLine, char separator);
	/*Processes the yearly data and adds it to the allData map*/
	void processYearlyData(std::map<std::string, std::vector<std::pair<int, double>>> allRawData);
	std::map<std::string, std::vector<Candlestick>> allData;

private:
};

