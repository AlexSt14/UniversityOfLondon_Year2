#include "WeatherMain.h"
#include <iostream>

WeatherMain::WeatherMain()
{
}
//Starting the app by reading the data from the csv file and printing menu
void WeatherMain::startApp()
{
	std::map<std::string, std::vector<std::pair<int, double>>> weatherData = reader.readWeatherData("weather.csv");
	reader.processYearlyData(weatherData);
	int userOption;
	while (true)
	{
		printMenu();
		userOption = getUserOption();
		processUserOption(userOption);
	}
}
//Printing the menu
void WeatherMain::printMenu()
{
	std::cout << "Weather App. Collated Yearly Data since 1980!" << std::endl;
	std::cout << "1. View Weather Data" << std::endl;
	std::cout << "2. View Weather Data for a Country" << std::endl;
	std::cout << "3. View Weather Data for a Year" << std::endl;
	std::cout << "4. Help" << std::endl;
	std::cout << "5. Exit" << std::endl;
}
//Printing the year menu
void WeatherMain::printYearMenu()
{
	std::cout << "1. View Weather Data for a Year" << std::endl;
	std::cout << "2. Help" << std::endl;
	std::cout << "3. Exit" << std::endl;
	int option = getUserOption();
	processUserOption(option);
}
//Printing the weather data
void WeatherMain::printWeatherData()
{
	std::cout << "Printing Weather Data..." << std::endl;
	for (auto& data : reader.allData) {
		std::cout << "Country: " << data.first << std::endl;
		for (auto& candle : data.second) {
			std::cout << "Year: " << candle.year << " Open: " << candle.open << " High: " << candle.high << " Low: " << candle.low << " Close: " << candle.close << std::endl;
		}
	}
	//Getting the min and max temperatures across all candlesticks
	double minTemp = 1000;
	double maxTemp = -1000;
	for (auto& data : reader.allData) {
		for (auto& candle : data.second) {
			minTemp = std::min(minTemp, candle.low);
			maxTemp = std::max(maxTemp, candle.high);
		}
	}
	double totalRange = maxTemp - minTemp;
	double temperatureRangePerRow = totalRange / 20;
	std::cout << "Min Temp: " << minTemp << " Max Temp: " << maxTemp << std::endl;
	std::cout << "Temperature Range Per Row: " << temperatureRangePerRow << std::endl;
	renderer.renderWeatherData(renderer.getRow(10, minTemp, temperatureRangePerRow));
}
//Printing the help menu
void WeatherMain::printHelp()
{
	std::cout << "This is a weather app that displays weather data for different countries and years." << std::endl;
	std::cout << "You can view the data for all countries, a specific country, or a specific year." << std::endl;
	std::cout << "You can also exit the app at any time." << std::endl;
	printMenu();
}
//Getting the user option
int WeatherMain::getUserOption()
{
	int option;
	std::cout << "Enter an option: ";
	std::cin >> option;
	return option;
}
//Processing the user option
void WeatherMain::processUserOption(int option)
{
	switch (option)
	{
	case 1:
		printWeatherData();
		break;
	case 2:
		std::cout << "View Weather Data for a Country" << std::endl;
		break;
	case 3:
		std::cout << "View Weather Data for a Year" << std::endl;
		break;
	case 4:
		printHelp();
		break;
	case 5:
		std::cout << "Exiting..." << std::endl;
		break;
	default:
		std::cout << "Invalid option" << std::endl;
		printMenu();
		break;
	}
}