/*Object Oriented Programming June 2024 Midterm
Weather Data Visualization
We are only initializing and running the app here, maintaining a clean main function*/

#include <iostream>
#include "CSVReader.h"
#include "WeatherMain.h"
#include <Windows.h>
#include <fcntl.h>
#include <io.h>

int main()
{
	WeatherMain app{};
	app.startApp();
}