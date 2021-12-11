/*
 * sd.h
 *
 *  Created on: Dec 11, 2021
 *      Author: theo
 */


#include "main.h"
#include "fatfs.h"
#include "sdmmc.h"
#include "tim.h"
#include "gpio.h"
#include "WeatherStation.h"

FRESULT res; /* FatFs function common result code */
uint32_t byteswritten, bytesread; /* File write/read counts */
uint8_t rtext[_MAX_SS];/* File read buffer */

void initSD();
void saveSD();
