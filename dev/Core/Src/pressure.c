/*
 * pressure.c
 *
 *  Created on: Dec 8, 2021
 *      Author: theo
 */
#include "pressure.h"

double getpressure ()
{
	stmdev_ctx_t dev_ctx;
	lps22hh_reg_t reg;
	/* Initialize mems driver interface */
	dev_ctx.write_reg = platform_write;
	dev_ctx.read_reg = platform_read;
	dev_ctx.handle = &SENSOR_BUS;
	/* Initialize platform specific hardware */
	/* Wait sensor boot time */
	platform_delay(BOOT_TIME);
	/* Check device ID */
	/* Restore default configuration */

	/* Enable Block Data Update */
	lps22hh_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
	/* Set Output Data Rate */
	lps22hh_data_rate_set(&dev_ctx, LPS22HH_10_Hz_LOW_NOISE);

	/* Read samples in polling mode (no int) */
		/* Read output only if new value is available */
		lps22hh_read_reg(&dev_ctx, LPS22HH_STATUS, (uint8_t *)&reg, 1);

		if (reg.status.p_da) {
			memset(&data_raw_pressure, 0x00, sizeof(uint32_t));
			lps22hh_pressure_raw_get(&dev_ctx, &data_raw_pressure);
			pressure_hPa = lps22hh_from_lsb_to_hpa( data_raw_pressure);
			return((double)pressure_hPa);


	}
}

static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
		uint16_t len)
{
	HAL_I2C_Mem_Write(handle, LPS22HH_I2C_ADD_H, reg,
			I2C_MEMADD_SIZE_8BIT, (uint8_t*) bufp, len, 1000);
}

static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
		uint16_t len)
{
	HAL_I2C_Mem_Read(handle, LPS22HH_I2C_ADD_H, reg,
			I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
}

static void platform_delay(uint32_t ms)
{
	HAL_Delay(ms);
}
