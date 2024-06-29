#pragma once
#include "CSVReader.h"
#include "RenderWeatherData.h"

class WeatherMain
{
public:
	WeatherMain();
	/*Main function to start the app*/
	void startApp();
private:
	/*This will print the menu of the app*/
	void printMenu();
	/*This will print the menu for the year*/
	void printYearMenu();
	/*This will print the weather data*/
	void printWeatherData();
	/*This will print the help menu*/
	void printHelp();
	/*This will get the user option*/
	int getUserOption();
	/*This will process the user option*/
	void processUserOption(int option);
	CSVReader reader;
	RenderWeatherData renderer;
};

