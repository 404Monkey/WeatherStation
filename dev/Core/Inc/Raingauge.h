/**************************************************************
   Raingauge, from WeatherStation library, is available for STM32F746G platform to manage
   our connected WeatherStation.

   Licensed under University of Poitiers M1 Connected Objects by TD1 GRP1.
   Produced by Henintsoa Andrianarivony.
 **************************************************************/

#ifndef __RAINGAUGE__
#define __RAINGAUGE__

/* -------------------- LIBRARIES -------------------- */
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>

/* ------------------- DECLARATIONS ------------------ */
extern TIM_HandleTypeDef htim2;			// Instance of timer/counter
#define CAPACITY 0.2794					// Bucket capacity of the rain gauge

// - Start the timer dedicated to the rain gauge
void RaingaugeStart(TIM_HandleTypeDef *htim2);
// - Give the rainfall saved since the last call function
double captureRainfall(TIM_HandleTypeDef *htim2);
// - Monitoring data via UART serial port
void displayRainfall(long counter, double rainfall);

#endif
