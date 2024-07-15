#pragma once

//This class has been created for TASK 1 of the midterm

//This class represents a candlestick object
//See the cpp file for clearly labelled sections of code written by me
class Candlestick
{
public:
	Candlestick() = default;
	Candlestick(int year, double open, double high, double low, double close);
	int year = 0;
	double open = 0.0;
	double high = 0.0;
	double low = 0.0;
	double close = 0.0;
};

