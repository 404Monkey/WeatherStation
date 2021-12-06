/*
 * sensor.h
 *
 *  Created on: Nov 27, 2021
 *      Author: theo
 */

#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include "i2c.h"
#include "usart.h"
#include "hts221_reg.h"
#include "lps22hh_reg.h"

#define SENSOR_BUS hi2c1

static int16_t data_raw_humidity;
static int16_t data_raw_temperature;
static float humidity_perc;
static float temperature_degC;
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);


/*
 *  Function used to apply coefficient
 */
typedef struct {
	float x0;
	float y0;
	float x1;
	float y1;
} lin_t;

float linear_interpolation(lin_t *lin, int16_t x);

double gettemp ();

double gethumidity ();


#define    BOOT_TIME        5 //ms

#define TX_BUF_DIM          1000

/* Private variables ---------------------------------------------------------*/
static uint32_t data_raw_pressure;
static float pressure_hPa;

/* Extern variables ----------------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/*
 *   WARNING:
 *   Functions declare in this section are defined at the end of this file
 *   and are strictly related to the hardware platform used.
 *
 */

static int32_t platform_write_LPS(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len);
static int32_t platform_read_LPS(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);

double getpressure ();

#endif /* INC_SENSOR_H_ */
