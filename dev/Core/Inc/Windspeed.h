/**************************************************************
   Windspeed, from WeatherStation library, is available for STM32F746G platform to manage
   our connected WeatherStation.

   Licensed under University of Poitiers M1 Connected Objects by TD1 GRP1.
   Produced by Theo Biardeau.
 **************************************************************/

#ifndef INC_WINDSPEED_H_
#define INC_WINDSPEED_H_

/* -------------------- LIBRARIES -------------------- */
#include "gpio.h"
#include <stdio.h>

/* ------------------- DECLARATIONS ------------------ */
#define WINDSPEED_ERROR_VAL -1.0		// Error value of the wind speed

// - Give the wind speed saved since the last call function
double captureWindspeed (double *wind_tick, const int delay);
// - Monitoring data via UART serial port
void displayWindspeed(double counter, double windspeed, const int delay);
#endif
