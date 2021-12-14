/**************************************************************
   WindDirection, from WeatherStation library, is available for STM32F746G platform to manage
   our connected WeatherStation.

   Licensed under University of Poitiers M1 Connected Objects by TD1 GRP1.
   Author: Pauline Chiquet.
 **************************************************************/

#ifndef __INC_WINDDIRECTION_H__
#define __INC_WINDDIRECTION_H__

/* -------------------- LIBRARIES -------------------- */
#include "adc.h"
#include "usart.h"
#include "gpio.h"

/* ------------------- DECLARATIONS ------------------ */
// - Give the current wind direction
double captureDirection(int code);

#endif /* __INC_WINDDIRECTION_H__ */
