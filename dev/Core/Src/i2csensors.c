/**************************************************************
   i2CSensors, from WeatherStation library, is available for STM32F746G platform to manage
   our connected WeatherStation.

   Licensed under University of Poitiers M1 Connected Objects by TD1 GRP1.
   Author: Theo Biardeau.
 **************************************************************/

#include <i2CSensors.h>

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

// - Give the current temperature
double captureTemp ()
{
	stmdev_ctx_t dev_ctx;
	dev_ctx.write_reg = platform_write;
	dev_ctx.read_reg = platform_read;
	dev_ctx.handle = &SENSOR_BUS;
    // Check device ID
    // Read temperature calibration coefficient
	lin_t lin_temp;
	hts221_temp_adc_point_0_get(&dev_ctx, &lin_temp.x0);
	hts221_temp_deg_point_0_get(&dev_ctx, &lin_temp.y0);
	hts221_temp_adc_point_1_get(&dev_ctx, &lin_temp.x1);
	hts221_temp_deg_point_1_get(&dev_ctx, &lin_temp.y1);
    // Enable Block Data Update
	hts221_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
    // Set Output Data Rate
	hts221_data_rate_set(&dev_ctx, HTS221_ODR_1Hz);
    // Device power on
	hts221_power_on_set(&dev_ctx, PROPERTY_ENABLE);
    // Read output only if new value is available
	hts221_reg_t reg;
	hts221_status_get(&dev_ctx, &reg.status_reg);

	if (reg.status_reg.t_da) {
        // Read temperature data
		memset(&data_raw_temperature, 0x00, sizeof(int16_t));
		hts221_temperature_raw_get(&dev_ctx, &data_raw_temperature);
		temperature_degC = linear_interpolation(&lin_temp,
				data_raw_temperature);


	}
	return((double)temperature_degC);

}

// - Give the current humidity
double captureHumidity () {

	stmdev_ctx_t dev_ctx;
	dev_ctx.write_reg = platform_write;
	dev_ctx.read_reg = platform_read;
	dev_ctx.handle = &SENSOR_BUS;
    // Check device ID
    // Read temperature calibration coefficient
	lin_t lin_hum;
	hts221_hum_adc_point_0_get(&dev_ctx, &lin_hum.x0);
	hts221_hum_rh_point_0_get(&dev_ctx, &lin_hum.y0);
	hts221_hum_adc_point_1_get(&dev_ctx, &lin_hum.x1);
	hts221_hum_rh_point_1_get(&dev_ctx, &lin_hum.y1);
	// Enable Block Data Update
	hts221_block_data_update_set(&dev_ctx, PROPERTY_ENABLE);
    // Set Output Data Rate
	hts221_data_rate_set(&dev_ctx, HTS221_ODR_1Hz);
    // Device power on
	hts221_power_on_set(&dev_ctx, PROPERTY_ENABLE);
    // Read output only if new value is available
	hts221_reg_t reg;
	hts221_status_get(&dev_ctx, &reg.status_reg);

    if (reg.status_reg.h_da) {
        // Read humidity data
		memset(&data_raw_humidity, 0x00, sizeof(int16_t));
		hts221_humidity_raw_get(&dev_ctx, &data_raw_humidity);
		humidity_perc = linear_interpolation(&lin_hum, data_raw_humidity);

		if (humidity_perc < 0) {
			humidity_perc = 0;
		}

		if (humidity_perc > 100) {
			humidity_perc = 100;
		}

		return((double)humidity_perc);
	}
}
