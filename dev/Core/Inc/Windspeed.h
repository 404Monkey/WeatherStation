/**************************************************************
   WindSpeed, from WeatherStation library, is available for STM32F746G platform to manage
   our connected WeatherStation.

   Licensed under University of Poitiers M1 Connected Object by TD1 GRP1.
   Produced by Theo Biardeau.
 **************************************************************/

#ifndef INC_WINDSPEED_H_
#define INC_WINDSPEED_H_

// Give the wind speed
double captureWindspeed (double *wind_tick, const int delay);

#endif
