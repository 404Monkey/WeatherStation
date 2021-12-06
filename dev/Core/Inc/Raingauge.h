#ifndef __RAINGAUGE__
#define __RAINGAUGE__

/* LIBRARIES ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>

extern TIM_HandleTypeDef htim2;			// Instance of timer/counter
#define CAPACITY 0.2794					// Bucket capacity of the rain gauge
#define RAINGAUGE_ERROR_VAL -1.0		// Error value of the rain gauge

// - Start the timer dedicated to the rain gauge
void Raingauge_start(TIM_HandleTypeDef *htim2);
// - Give the rainfall saved since the last call function
double Raingauge_captureRainfall(TIM_HandleTypeDef *htim2, int _DELAY);
// - Monitoring data via UART serial port
void Raingauge_displayRainfall(long _COUNTER, double _RAINFALL, int _DELAY);

#endif
