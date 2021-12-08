/*
 * pressure.h
 *
 *  Created on: Dec 8, 2021
 *      Author: theo
 */

#ifndef INC_PRESSURE_H_
#define INC_PRESSURE_H_

#include "main.h"
#include "stm32f7xx_hal.h"
#include "i2c.h"
#include "lps22hh_reg.h"

#define SENSOR_BUS hi2c1
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

static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);
static void platform_delay(uint32_t ms);
double getpressure();

#endif /* INC_PRESSURE_H_ */
