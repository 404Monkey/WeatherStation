/**************************************************************
   Sd, from WeatherStation library, is available for STM32F746G platform to manage
   our connected WeatherStation.

   Licensed under University of Poitiers M1 Connected Objects by TD1 GRP1.
   Author: Theo Biardeau.
 **************************************************************/

#ifndef _SD_
#define _SD_

/* -------------------- LIBRARIES -------------------- */
#include "main.h"
#include "fatfs.h"
#include "sdmmc.h"
#include "tim.h"
#include "gpio.h"
#include "WeatherStation.h"

/* ------------------- DECLARATIONS ------------------ */
FRESULT res; 						// FatFs function common result code
uint32_t byteswritten, bytesread; 	// File write/read counts
uint8_t rtext[_MAX_SS];				// File read buffer

// - SD Card initialization
void initSD();
// - Save data captured in SD Card
void saveSD();

#endif /* _SD_ */
