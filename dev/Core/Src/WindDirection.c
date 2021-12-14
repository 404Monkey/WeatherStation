/**************************************************************
   WindDirection, from WeatherStation library, is available for STM32F746G platform to manage
   our connected WeatherStation.

   Licensed under University of Poitiers M1 Connected Objects by TD1 GRP1.
   Author: Pauline Chiquet.
 **************************************************************/

#include <WindDirection.h>

// - Give the current wind direction
double captureDirection(int code)
{
	// This function does the acquisition and returns the direction of the wind in degrees.
	// It assumes 8 positions depending on the numerical value read by the ADC.
	// We have determined theoretically and confirmed experimentally the range of numerical
	// values for each of the 8 positions.

	double degree = -1.0;

	// East
	if (1500 <= code && code < 2000)
	{
		degree = 90.0;
	}
	// South East
	else if (2000 <= code && code < 2200)
	{
		degree = 135.0;
	}
	// South
	else if (2200 <= code && code < 2500)
	{
		degree = 180.0;
	}
	// North East
	else if (2500 <= code && code < 3000)
	{
		degree = 45.0;
	}
	// South West
	else if (3000 <= code && code < 3300)
	{
		degree = 225.0;
	}
	// North
	else if (3300 <= code && code < 3600)
	{
		degree = 0.0;
	}
	// North West
	else if (3600 <= code && code < 3780)
	{
		degree = 315.0;
	}
	// West
	else if (3780 <= code && code < 4000)
	{
		degree = 270.0;
	}

	return degree;
}
