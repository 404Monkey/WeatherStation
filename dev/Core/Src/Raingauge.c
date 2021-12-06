#include "Raingauge.h"

// - Start the timer dedicated to the rain gauge
void Raingauge_start(TIM_HandleTypeDef *htim2){
	//Start the counter/timer
	HAL_TIM_Base_Start(htim2);
}

// - Give the rainfall saved since the last call function
double Raingauge_captureRainfall(TIM_HandleTypeDef *htim2, int _DELAY){
	//Stock the value of the rain gauge counter and reset the counter
	long _COUNTER = __HAL_TIM_GET_COUNTER(htim2);
	__HAL_TIM_SetCounter(htim2,0);

	//Check if delay equals to zero
	if (_DELAY == 0) {
		//If so, display an error message and return an error value

		Raingauge_displayRainfall(_COUNTER, RAINGAUGE_ERROR_VAL, 0);
		return RAINGAUGE_ERROR_VAL;
	} else {
		//If not, compute rainfall then display and return it

		double _RAINFALL = _COUNTER * CAPACITY * 3600 / _DELAY;
		Raingauge_displayRainfall(_COUNTER, _RAINFALL, _DELAY);
		return _RAINFALL;
	}
}

// - Monitoring data via UART serial port
void Raingauge_displayRainfall(long _COUNTER, double _RAINFALL, int _DELAY) {
	printf("====== MONITORING RAIN GAUGE ======\r\n");
	if (_DELAY == 0) {
		printf("=> ERROR RAIN GAUGE : In function \"Raingauge_captureRainfall\", delay cannot be equal to 0. \r\n");
	}
	printf("Counter : %ld \r\n", _COUNTER);
	printf("Rainfall : %f mm/h\r\n", _RAINFALL);
}
