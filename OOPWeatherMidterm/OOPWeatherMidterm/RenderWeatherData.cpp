#include "RenderWeatherData.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

//This class has been created for TASK 2 of the midterm

RenderWeatherData::RenderWeatherData()
{
}
/* Function to render the weather data
A LOT of trial and error went into this function until I managed to get the plot to actually work and look decent
I am aware it might not be the best way to do it, but it works */
//THIS CODE HAS BEEN WRITTEN BY ME WITHOUT ASSISTANCE
void RenderWeatherData::renderWeatherData(const std::map<std::string, std::vector<Candlestick>>& allData, double minTemp, double maxTemp)
{
	int numRows { 45 };
	int numCols { 45 };
	double temperatureRangePerRow { (maxTemp - minTemp) / numRows };
	std::vector<int> years;

	for (const auto& country : allData) {
		int col{ 0 };
		years.clear();	//Clearing the years vector for every country
		//Creating a 2D vector to store the plot
		std::vector<std::vector<std::string>> plot(numRows, std::vector<std::string>(numCols, "      "));
		std::cout << "Country: " << country.first << std::endl;
		for (const auto& candle : country.second) {
			int openRow = getRow(candle.open, minTemp, temperatureRangePerRow, numRows);
			int closeRow = getRow(candle.close, minTemp, temperatureRangePerRow, numRows);
			int highRow = getRow(candle.high, minTemp, temperatureRangePerRow, numRows);
			int lowRow = getRow(candle.low, minTemp, temperatureRangePerRow, numRows);
			//Populating the years vector for the year labels
			years.push_back(candle.year);

			//Bounds checking
			if (col < 0 || col >= numCols) {
				std::cerr << "Error: Column out of bounds. Col: " << col << ", NumCols: " << numCols << std::endl;
				break;
			}

			//Plotting the candlestick body based on the open and close values
			if (candle.open <= candle.close) {
				for (int row = std::min(openRow, closeRow); row <= std::max(openRow, closeRow); ++row) {
					plot[row][col] = "  [+] ";
				}
			}
			else {
				for (int row = std::min(openRow, closeRow); row <= std::max(openRow, closeRow); ++row) {
					plot[row][col] = "  [-] ";
				}
			}
			
			//Plotting the wick
			for (int row = highRow; row < std::min(openRow, closeRow); ++row) {
				plot[row][col] = "   |  ";
			}
			for (int row = std::max(openRow, closeRow) + 1; row <= lowRow; ++row) {
				plot[row][col] = "   |  ";
			}
			++col;
			if (col >= numCols)	break;
		}
		//Printing the plot with temperature labels and year labels
		for (int i = 0; i < numRows; ++i) {
			//Temperature labels
			double temp = maxTemp - i * temperatureRangePerRow;
			std::cout << std::setw(5) << std::right << static_cast<int>(std::round(temp));
			for (std::string c : plot[i]) {
				std::cout << c;
			}
			std::cout << '\n';
		}
		//Year labels
		std::cout << "       ";
		for (const auto& year : years) {
			std::cout << std::setw(6) << std::left << year;
		}
		std::cout << '\n';
		std::cout << '\n';
	}
}
//Function to get the right row for the temperature in the plot
//THIS CODE HAS BEEN WRITTEN BY ME WITHOUT ASSISTANCE
int RenderWeatherData::getRow(double temperature, double minTemperature, double temperatureRangePerRow, int numRows)
{
	return numRows - 1 - static_cast<int>((temperature - minTemperature) / temperatureRangePerRow);
}
