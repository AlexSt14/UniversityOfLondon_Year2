#pragma once
#include "CSVReader.h"
#include "RenderWeatherData.h"
#include "FilterWeatherData.h"
#include "PredictWeatherData.h"

//This class serves for TASK1, TASK2, TASK3, and TASK4 of the midterm
//See the cpp file for clearly labelled sections of code written by me

class WeatherMain
{
public:
	WeatherMain();
	/*Main function to start the app*/
	void startApp();
private:
	/*This will print the menu of the app*/
	void printMenu();
	/*This will filter the weather data*/
	void filterWeatherData();
	/*This will filter the weather data by both countries and year range*/
	void filterWeatherDataCombined();
	/*This will print the weather data*/
	void printWeatherData();
	/*This will predict the weather on the upcoming year*/
	void predictWeather();
	/*This will print the help menu*/
	void printHelp();
	/*This will get the user option*/
	int getUserOption();
	/*This will process the user option*/
	void processUserOption(int option);
	//This will print all data to the console
	void printAllData();
	/*This will calculate the minTemp and maxTemp*/
	static std::pair<double,double> calculateMinMaxTemp(const std::map<std::string, std::vector<Candlestick>>& data);
	/*This will get the available countries in the data*/
	static void getAvailableCountries(const std::map<std::string, std::vector<Candlestick>>& data);
	CSVReader reader;
	RenderWeatherData renderer;
	FilterWeatherData filter;
	PredictWeatherData predictor;
	bool isRunning = true;
};

