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
void RaingaugeStart(TIM_HandleTypeDef *htim2);
// - Give the rainfall saved since the last call function
double RaingaugeCaptureRainfall(TIM_HandleTypeDef *htim2, int delay);
// - Monitoring data via UART serial port
void RaingaugeDisplayRainfall(long counter, double rainfall, int delay);

#endif
