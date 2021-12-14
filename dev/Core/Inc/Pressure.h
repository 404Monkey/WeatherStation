/**************************************************************
   Pressure, from WeatherStation library, is available for STM32F746G platform to manage
   our connected WeatherStation.

   Licensed under University of Poitiers M1 Connected Objects by TD1 GRP1.
   Author: Theo Biardeau.
 **************************************************************/

#ifndef __INC_PRESSURE_H__
#define __INC_PRESSURE_H__

/* -------------------- LIBRARIES -------------------- */
#include "stm32f7xx_hal.h"
#include "i2c.h"
#include "lps22hh_reg.h"

/* ------------------- DECLARATIONS ------------------ */
#define SENSOR_BUS hi2c1
#define BOOT_TIME 5 		// Sensor boot time (in ms)
#define TX_BUF_DIM 1000		// Size of buffer
static uint32_t data_raw_pressure;
static float pressure_hPa;

/*
 *   WARNING:
 *   Functions declare in this section are defined at the end of this file
 *   and are strictly related to the hardware platform used.
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);
static void platform_delay(uint32_t ms);
// - Give the current pressure
double capturePressure();

#endif /* __INC_PRESSURE_H__ */
