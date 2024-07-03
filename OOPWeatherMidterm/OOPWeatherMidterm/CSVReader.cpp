#include "CSVReader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

//This class has been created for TASK 1 of the midterm

CSVReader::CSVReader()
{
}
//This function reads the weather data from the csv file and returns a map of data with country and vector pairs of year and temperature
std::map<std::string, std::vector<std::pair<int, double>>> CSVReader::readWeatherData(std::string filename)
{
	std::map<std::string, std::vector<std::pair<int, double>>> allData;
	std::ifstream file(filename);
	std::string line;

	if (file.is_open())
	{
		//Reading the header line to get the country names
		std::getline(file, line); 
		std::vector<std::string> headers = tokenise(line, ',');
		//While file is open, read each line and store the data in the map
		while (std::getline(file, line)) {
			try {
				std::vector<std::string> tokens = tokenise(line, ',');
				std::string timeStamp = tokens[0];
				int year = std::stoi(timeStamp.substr(0, 4));

				//Storing data for each country
				for (size_t i = 1; i < tokens.size(); ++i) {
					std::string country = headers[i].substr(0, 2);
					double temperature = std::stod(tokens[i]);

					//Adding the data to the map
					allData[country].push_back(std::make_pair(year, temperature));
				}
			}
			catch (std::exception& e) {
				std::cout << "Error reading line: " << line << std::endl;
			}
		}
	}
	else
	{
		std::cout << "Could not open file: " << filename << std::endl;
	}
	return allData;
}
//Tokenise the csv line by separator, this function was taken from the MerkelMaine project and reused here
std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
	std::vector<std::string> tokens;
	signed int start, end;
	std::string token;
	start = csvLine.find_first_not_of(separator, 0);
	do {
		end = csvLine.find_first_of(separator, start);
		if (start == csvLine.length() || start == end) break;
		if (end >= 0) token = csvLine.substr(start, end - start);
		else token = csvLine.substr(start, csvLine.length() - start);
		tokens.push_back(token);
		start = end + 1;
	} while (end > 0);

	return tokens;
}
//This function processes the yearly data and adds it to the allData map that will be ready to be rendered
void CSVReader::processYearlyData(std::map<std::string, std::vector<std::pair<int, double>>> allRawData)
{
	//Looping through countries
	for (auto& countryData : allRawData) {
		std::string country = countryData.first;
		std::map<int, Candlestick> yearlyCandlesticks;
		double close = 0;
		int count = 0;
		double sum = 0;
		//Looping through the data points for each country
		for (auto& dataPoint : countryData.second) {
			int year = dataPoint.first;
			double temperature = dataPoint.second;

			//calculate close average mean price
			sum += temperature;
			count++;
			//Will create a candlestick object for each year only if it does not exist
			if (yearlyCandlesticks.find(year) == yearlyCandlesticks.end()) {
				yearlyCandlesticks[year] = Candlestick(year, temperature, temperature, temperature, temperature);
			}
			else {
				//Updating the candlestick object for the year
				yearlyCandlesticks[year].high = std::max(yearlyCandlesticks[year].high, temperature);
				yearlyCandlesticks[year].low = std::min(yearlyCandlesticks[year].low, temperature);
				//If there was a candlestick object last year, we will update the open price to the close price of the last year
				if (yearlyCandlesticks.find(year-1) != yearlyCandlesticks.end()) {
					yearlyCandlesticks[year].open = yearlyCandlesticks[year-1].close;
				}
			}
			//Only calculating the average mean close price for current year if its the last data point for the year
			if (count == countryData.second.size()) {
				close = sum / count;
				yearlyCandlesticks[year].close = close;
			}
		}
		//Pushing the candlesticks for the country to the allData map
		for (auto& candlestick : yearlyCandlesticks) {
			allData[country].push_back(candlestick.second);
		}
	}
}