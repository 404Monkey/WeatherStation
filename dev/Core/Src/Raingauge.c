#include "Raingauge.h"

// - Start the timer dedicated to the rain gauge
void RaingaugeStart(TIM_HandleTypeDef *htim2){
	//Start the counter/timer
	HAL_TIM_Base_Start(htim2);
}

// - Give the rainfall saved since the last call function
double RaingaugeCaptureRainfall(TIM_HandleTypeDef *htim2, int delay){
	//Stock the value of the rain gauge counter and reset the counter
	long counter = __HAL_TIM_GET_COUNTER(htim2);
	__HAL_TIM_SetCounter(htim2,0);

	//Check if delay equals to zero
	if (delay == 0) {
		//If so, display an error message and return an error value

		RaingaugeDisplayRainfall(counter, RAINGAUGE_ERROR_VAL, 0);
		return RAINGAUGE_ERROR_VAL;
	} else {
		//If not, compute rainfall then display and return it

		double rainfall = counter * CAPACITY * 3600 / delay;
		RaingaugeDisplayRainfall(counter, rainfall, delay);
		return rainfall;
	}
}

// - Monitoring data via UART serial port
void RaingaugeDisplayRainfall(long counter, double rainfall, int delay) {
	printf("====== MONITORING RAIN GAUGE ======\r\n");
	if (delay == 0) {
		printf("=> ERROR RAIN GAUGE : In function \"Raingauge_captureRainfall\", delay cannot be equal to 0. \r\n");
	}
	printf("Counter : %ld \r\n", counter);
	printf("Rainfall : %f mm/h\r\n", rainfall);
}
