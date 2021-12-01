/*
 * sensor.c
 *
 *  Created on: Nov 27, 2021
 *      Author: theo
 */

#include "i2csensors.h"

float linear_interpolation(lin_t *lin, int16_t x)
{
	return ((lin->y1 - lin->y0) * x + ((lin->x1 * lin->y0) -
			(lin->x0 * lin->y1)))
			/ (lin->x1 - lin->x0);
}


static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len)
{
  reg |= 0x80;
  HAL_I2C_Mem_Write(handle, HTS221_I2C_ADDRESS, reg,
                    I2C_MEMADD_SIZE_8BIT, (uint8_t*) bufp, len, 1000);
  return 0;
}

/*
 * @brief  Read generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to read
 * @param  bufp      pointer to buffer that store the data read
 * @param  len       number of consecutive register to read
 *
 */
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len)
{
  reg |= 0x80;
  HAL_I2C_Mem_Read(handle, HTS221_I2C_ADDRESS, reg,
                   I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);
  return 0;
}


int32_t gettemp ()
{
	stmdev_ctx_t dev_ctx;
	dev_ctx.write_reg = platform_write;
	dev_ctx.read_reg = platform_read;
	dev_ctx.handle = &SENSOR_BUS;
	/* Check device ID */
	/* Read temperature calibration coefficient */
	lin_t lin_temp;
	hts221_temp_adc_point_0_get(&dev_ctx, &lin_temp.x0);
	hts221_temp_deg_point_0_get(&dev_ctx, &lin_temp.y0);
	hts221_temp_adc_point_1_get(&dev_ctx, &lin_temp.x1);
	hts221_temp_deg_point_1_get(&dev_ctx, &lin_temp.y1);
	/* Enable Block Data Update */
	hts221_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
	/* Set Output Data Rate */
	hts221_data_rate_set(&dev_ctx, HTS221_ODR_1Hz);
	/* Device power on */
	hts221_power_on_set(&dev_ctx, PROPERTY_ENABLE);
	/* Read output only if new value is available */
	hts221_reg_t reg;
	hts221_status_get(&dev_ctx, &reg.status_reg);

	if (reg.status_reg.t_da) {
		/* Read temperature data */
		memset(&data_raw_temperature, 0x00, sizeof(int16_t));
		hts221_temperature_raw_get(&dev_ctx, &data_raw_temperature);
		temperature_degC = linear_interpolation(&lin_temp,
				data_raw_temperature);


	}
	return((int32_t)temperature_degC);

}

int32_t gethumidity () {

	stmdev_ctx_t dev_ctx;
	dev_ctx.write_reg = platform_write;
	dev_ctx.read_reg = platform_read;
	dev_ctx.handle = &SENSOR_BUS;
	/* Check device ID */
	/* Read temperature calibration coefficient */
	lin_t lin_hum;
	hts221_hum_adc_point_0_get(&dev_ctx, &lin_hum.x0);
	hts221_hum_rh_point_0_get(&dev_ctx, &lin_hum.y0);
	hts221_hum_adc_point_1_get(&dev_ctx, &lin_hum.x1);
	hts221_hum_rh_point_1_get(&dev_ctx, &lin_hum.y1);
	/* Enable Block Data Update */
	hts221_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
	/* Set Output Data Rate */
	hts221_data_rate_set(&dev_ctx, HTS221_ODR_1Hz);
	/* Device power on */
	hts221_power_on_set(&dev_ctx, PROPERTY_ENABLE);
	/* Read output only if new value is available */
	hts221_reg_t reg;
	hts221_status_get(&dev_ctx, &reg.status_reg);
	if (reg.status_reg.h_da) {
		/* Read humidity data */
		memset(&data_raw_humidity, 0x00, sizeof(int16_t));
		hts221_humidity_raw_get(&dev_ctx, &data_raw_humidity);
		humidity_perc = linear_interpolation(&lin_hum, data_raw_humidity);

		if (humidity_perc < 0) {
			humidity_perc = 0;
		}

		if (humidity_perc > 100) {
			humidity_perc = 100;
		}
		return((int32_t)humidity_perc);

	}

}

static int32_t platform_write_LPS(void *handle, uint8_t reg, const uint8_t *bufp,
		uint16_t len)
{

	/* Write multiple command */
	reg |= 0x80;
	HAL_I2C_Mem_Write(handle, HTS221_I2C_ADDRESS, reg,
			I2C_MEMADD_SIZE_8BIT, (uint8_t*) bufp, len, 1000);

	return 0;
}

static int32_t platform_read_LPS(void *handle, uint8_t reg, uint8_t *bufp,
		uint16_t len)
{

	reg |= 0x80;
	HAL_I2C_Mem_Read(handle, HTS221_I2C_ADDRESS, reg,
			I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);

	return 0;
}





uint32_t getpressure ()
{
  stmdev_ctx_t dev_ctx;
  lps22hh_reg_t reg;
  /* Initialize mems driver interface */
  dev_ctx.write_reg = platform_write_LPS;
  dev_ctx.read_reg = platform_read_LPS;
  dev_ctx.handle = &SENSOR_BUS;
  /* Initialize platform specific hardware */
  /* Enable Block Data Update */
  lps22hh_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
  /* Set Output Data Rate */
  lps22hh_data_rate_set(&dev_ctx, LPS22HH_ONE_SHOOT);
    /* Read output only if new value is available */
    lps22hh_read_reg(&dev_ctx, LPS22HH_STATUS, (uint8_t *)&reg, 1);

    if (reg.status.p_da) {
      memset(&data_raw_pressure, 0x00, sizeof(uint32_t));
      lps22hh_pressure_raw_get(&dev_ctx, &data_raw_pressure);
      pressure_hPa = lps22hh_from_lsb_to_hpa( data_raw_pressure);
      return((int)pressure_hPa);
    }
  }


/*
 * @brief  Write generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to write
 * @param  bufp      pointer to data to write in register reg
 * @param  len       number of consecutive register to write
 *
 */

/*
 * @brief  Write generic device register (platform dependent)
 *
 * @param  tx_buffer     buffer to transmit
 * @param  len           number of byte to send
 *
 */

/*
 * @brief  platform specific delay (platform dependent)
 *
 * @param  ms        delay in ms
 *
 */

/*
 * @brief  platform specific initialization (platform dependent)
 */

