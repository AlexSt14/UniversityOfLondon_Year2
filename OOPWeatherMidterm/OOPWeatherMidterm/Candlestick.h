#pragma once

//This class has been created for TASK 1 of the midterm

// This class represents a candlestick object
class Candlestick
{
public:
	Candlestick() = default;
	Candlestick(int year, double open, double high, double low, double close)
		: year(year), open(open), high(high), low(low), close(close) {}
	int year = 0;
	double open = 0.0;
	double high = 0.0;
	double low = 0.0;
	double close = 0.0;
};

