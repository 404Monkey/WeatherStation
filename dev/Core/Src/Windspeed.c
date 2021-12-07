/**************************************************************
   Windspeed, from WeatherStation library, is available for STM32F746G platform to manage
   our connected WeatherStation.

   Licensed under University of Poitiers M1 Connected Objects by TD1 GRP1.
   Produced by Theo Biardeau.
 **************************************************************/

#include "Windspeed.h"

// - Give the wind speed saved since the last call function
double captureWindspeed(double *wind_tick, const int delay) {
    //Compute wind speed, reset wind_tick counter and return wind speed
	double wind_speed =  (*wind_tick * 2.4)/delay;
	*wind_tick = 0;

    return wind_speed;
}
