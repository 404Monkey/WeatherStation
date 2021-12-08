/**************************************************************
   Raingauge, from WeatherStation library, is available for STM32F746G platform to manage
   our connected WeatherStation.

   Licensed under University of Poitiers M1 Connected Objects by TD1 GRP1.
   Produced by Henintsoa Andrianarivony.
 **************************************************************/

#include "Raingauge.h"

// - Start the timer dedicated to the rain gauge
void RaingaugeStart(TIM_HandleTypeDef *htim2){
	//Start the counter/timer
	HAL_TIM_Base_Start(htim2);
}

// - Give the rainfall saved since the last call function
double captureRainfall(TIM_HandleTypeDef *htim2){
	//Stock the value of the rain gauge counter and reset the counter
	long counter = __HAL_TIM_GET_COUNTER(htim2);
	__HAL_TIM_SetCounter(htim2,0);
	//Compute rainfall then display and return it
	double rainfall = counter * CAPACITY;
	displayRainfall(counter, rainfall);

	return rainfall;
}

// - Monitoring data via UART serial port
void displayRainfall(long counter, double rainfall) {
	printf("====== MONITORING RAIN GAUGE ======\r\n");
	printf("Counter : %ld \r\n", counter);
	printf("Rainfall : %f mm\r\n", rainfall);
}
