#include "WeatherMain.h"
#include <iostream>

//This class serves for TASK1, TASK2, and TASK 3 of the midterm

WeatherMain::WeatherMain()
{
}
//Starting the app by reading the data from the csv file and printing menu
void WeatherMain::startApp()
{
	std::map<std::string, std::vector<std::pair<int, double>>> weatherData = reader.readWeatherData("weather.csv");
	reader.processYearlyData(weatherData);
	int userOption;
	while (isRunning)
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
	std::cout << "1. View Weather Data for all Countries" << std::endl;
	std::cout << "2. Filter Viewed Data" << std::endl;
	std::cout << "3. Predict Weather Data" << std::endl;
	std::cout << "4. Help" << std::endl;
	std::cout << "5. Exit" << std::endl;
}
//Printing the weather data for all countries
void WeatherMain::printWeatherData()
{
	std::cout << "Printing Weather Data..." << std::endl;
	//Getting the min and max temperatures across all candlesticks
	std::pair<double,double> minMaxTemp = calculateMinMaxTemp(reader.allData);
	//Rendering the weather data
	renderer.renderWeatherData(reader.allData, minMaxTemp.first, minMaxTemp.second);
}
//Printing the filtered weather data menu
void WeatherMain::filterWeatherData() {
	std::pair<double, double> minMaxTemp;	
	//If user wants to filter the data by both countries and year range at the same time we call the combined function
	std::cout << "Enter 1 if you want to filter the data by both countries and year range at the same time. Enter 2 if you want to filter by country or year range separately." << std::endl;
	int userOption = getUserOption();
	if (userOption == 1) {
		filterWeatherDataCombined();
	}
	//Else we ask the user if they want to filter by country or year separately
	else if (userOption == 2) {
		std::cout << "Do you want to filter the data by country or year range?" << std::endl;
		std::cout << "Enter 1 to filter data by country. Enter 2 to filter data by year range." << std::endl;
		int userOption = getUserOption();
		if (userOption == 1) {
			//Filtering the data by country and rendering it
			//Handling exception in case user inputs something not correct
			try {
				getAvailableCountries(reader.allData);
				std::cout << std::endl;
				std::cout << "To choose a country, you must enter the 2 letter country code. Make sure to type it in UPPERCASE." << std::endl;
				std::cout << "You can also type 2 or more contries at the same time, separated by commas (NO WHITE SPACE). Example: RO,GB,PL" << std::endl;
				std::cout << "Enter the 2 letter country code: ";
				std::string country;
				std::cin.ignore();	//Clearing the input buffer before taking the line
				std::getline(std::cin, country);
				std::map<std::string, std::vector<Candlestick>> filteredData = filter.filterDataCountry(reader.allData, reader.tokenise(country, ','));
				minMaxTemp = calculateMinMaxTemp(filteredData);
				renderer.renderWeatherData(filteredData, minMaxTemp.first, minMaxTemp.second);
			}
			catch (const std::exception& e) {
				std::cout << e.what() << std::endl;
				filterWeatherData();
			}
		}//Filter the data by year range and rendering it with exception handling
		else if (userOption == 2) {
			try {
				std::cout << "To filter the data by year, you must enter the years range (NO WHITE SPACE). Example: 2010,2019" << std::endl;
				std::cout << "Enter the years separated by comma: ";
				std::string years;
				std::cin.ignore();
				std::getline(std::cin, years);
				std::map<std::string, std::vector<Candlestick>> filteredData = filter.filterDataYear(reader.allData, reader.tokenise(years, ','));
				minMaxTemp = calculateMinMaxTemp(filteredData);
				renderer.renderWeatherData(filteredData, minMaxTemp.first, minMaxTemp.second);
			}
			catch (const std::exception& e) {
				std::cout << e.what() << std::endl;
				filterWeatherData();
			}
		}
		else {
			std::cout << "Invalid option" << std::endl;
			filterWeatherData();
		}
	}
	else {
		std::cout << "Invalid option" << std::endl;
		filterWeatherData();
	}
}
//Filtering the weather data by both countries and year range at the same time
void WeatherMain::filterWeatherDataCombined() {
	try {
		getAvailableCountries(reader.allData);
		std::cout << std::endl;
		std::cout << "To choose a country, you must enter the 2 letter country code. Make sure to type it in UPPERCASE." << std::endl;
		std::cout << "You can type multiple countries separated by commas (NO WHITE SPACE). Example: RO,GB,PL" << std::endl;
		std::cout << "Enter the 2 letter country code: ";
		std::string country;
		std::cin.ignore();
		std::getline(std::cin, country);
		std::cout << "To filter the data by year, you must enter the years range (NO WHITE SPACE). Example: 2010,2019" << std::endl;
		std::cout << "Enter the years separated by comma: ";
		std::string years;
		std::getline(std::cin, years);
		std::map<std::string, std::vector<Candlestick>> filteredData = filter.filterDataCountryYear(reader.allData, reader.tokenise(country, ','), reader.tokenise(years, ','));
		std::pair<double, double> minMaxTemp = calculateMinMaxTemp(filteredData);
		renderer.renderWeatherData(filteredData, minMaxTemp.first, minMaxTemp.second);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		filterWeatherData();
	}	
}
//Predicting weather on the upcoming year
void WeatherMain::predictWeather() {
	getAvailableCountries(reader.allData);
	std::cout << std::endl;
	std::cout << "To choose a country, you must enter the 2 letter country code. Make sure to type it in UPPERCASE." << std::endl;
	std::cout << "You can type multiple countries separated by commas (NO WHITE SPACE). Example: RO,GB,PL" << std::endl;
	std::cout << "Enter the 2 letter country code: ";
	std::string country;
	std::cin.ignore();
	std::getline(std::cin, country);
	std::cout << "To filter the data by year, you must enter the years range (NO WHITE SPACE). Example: 2010,2019" << std::endl;
	std::cout << "Enter the years separated by comma: ";
	std::string years;
	std::getline(std::cin, years);
	std::map<std::string, std::vector<Candlestick>> filteredData = filter.filterDataCountryYear(reader.allData, reader.tokenise(country, ','), reader.tokenise(years, ','));
	std::pair<double,double> minMaxTemp = calculateMinMaxTemp(filteredData);
	std::cout << "Predicting Weather Data..." << std::endl;
	renderer.renderWeatherData(predictor.predictWeather(filteredData),minMaxTemp.first,minMaxTemp.second);
}
//Printing the help menu
void WeatherMain::printHelp()
{
	std::cout << "This is a weather app that displays weather data for different countries and years." << std::endl;
	std::cout << "If you press 1, you will see the weather data for all available countries." << std::endl;
	std::cout << "If you press 2, you can filter the data for multiple countries, a specific country, or a specific set of years." << std::endl;
	std::cout << "You can also filter the data by countries and year range at the same time." << std::endl;
	std::cout << "Press 4 to exit the app" << std::endl;
	printMenu();
}
//Getting the user option
//This function and the processUserOption function below it, were taken from the MerkelMain project and reused here
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
		filterWeatherData();
		break;
	case 3:
		predictWeather();
		break;
	case 4:
		printHelp();
		break;
	case 5:
		std::cout << "Exiting the app..." << std::endl;
		isRunning = false;
		break;
	default:
		std::cout << "Invalid option" << std::endl;
		printMenu();
		break;
	}
}
//Calculating the min and max temperatures required for plotting the data
std::pair<double, double> WeatherMain::calculateMinMaxTemp(const std::map<std::string, std::vector<Candlestick>>& data) {
	double minTemp = 1000;
	double maxTemp = -1000;
	for (const auto& data : data) {
		for (const auto& candle : data.second) {
			minTemp = std::min(minTemp, candle.low);
			maxTemp = std::max(maxTemp, candle.high);
		}
	}
	minTemp -= 3;
	maxTemp += 3;
	return std::make_pair(minTemp, maxTemp);
}
//Getting the available countries in the data
void WeatherMain::getAvailableCountries(const std::map<std::string, std::vector<Candlestick>>& data) {
	std::cout << "Available countries: ";
	for (const auto& country : data) {
		std::cout << country.first << " ";
	}
}