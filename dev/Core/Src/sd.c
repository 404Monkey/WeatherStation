
/*
 * Sdcard.c
 *
 *  Created on: Dec 8, 2021
 *      Author: theo
 */
#include "sd.h"

char buff [10000] = {};
char number[10] = {};
const char rc [] = "\r\n";
const char coma []= ";";
const char point[] = ":";
const char space[] = " ";
const char slash[] = "/";
const char wtext[] = "date; time; temperature; humidity; pressure; wind speed; wind direction; rain\r\n";

void initSD(){


	printf("card initializationSD\r\n");

	//Checking the presence of the sd card ###########################
	if(BSP_SD_IsDetected() == 1){

		//Register the work area of the volume ###########################
		if(f_mount(&SDFatFS, (TCHAR const*)SDPath, 0) != FR_OK)
		{
			Error_Handler();
		}

		else
		{
			//Open file for writing (Create if not present) ###########################
			if(f_open(&SDFile, "DATA.CSV", FA_OPEN_ALWAYS | FA_WRITE) != FR_OK)
			{
				printf("cannot open SD card\r\n");
			}
			else
			{
				//Write to the csv file ###########################
				res = f_write(&SDFile, wtext, strlen(wtext), (void *)&byteswritten);
				if((byteswritten == 0) || (res != FR_OK))
				{
					printf("cannot write to SD card \r\n");
				}
				else
				{
					f_close(&SDFile);
					printf("successful initialization \r\n");
				}

			}
		}
		//Unregister the work area of the volume ###########################
		f_mount(&SDFatFS, (TCHAR const*)NULL, 0);
	}else
	{
		printf("no card is mounted \r\n");
	}
}




void saveSD(){

	// prepation of data for saving ###########################
	for(int i = 0; i<Data_to_save.nb_data; i++){

		itoa(Data_to_save.dates[i].day,number,10);
		strcat(buff, number);
		memset(number, 0, sizeof number);
		strcat(buff, slash);

		itoa(Data_to_save.dates[i].month,number,10);
		strcat(buff, number);
		memset(number, 0, sizeof number);
		strcat(buff, slash);

		itoa(Data_to_save.dates[i].year,number,10);
		strcat(buff, number);
		memset(number, 0, sizeof number);
		strcat(buff, coma);

		itoa(Data_to_save.dates[i].hour,number,10);
		strcat(buff, number);
		memset(number, 0, sizeof number);
		strcat(buff, point);

		itoa(Data_to_save.dates[i].minute,number,10);
		strcat(buff, number);
		memset(number, 0, sizeof number);
		strcat(buff, point);

		itoa(Data_to_save.dates[i].seconds,number,10);
		strcat(buff, number);
		memset(number, 0, sizeof number);
		strcat(buff, coma);

		itoa(Data_to_save.temperatures[i],number,10) ;
		strcat(buff, number);
		memset(number, 0, sizeof number);
		strcat(buff, coma);

		itoa(Data_to_save.humidities[i],number,10) ;
		strcat(buff, number);
		memset(number, 0, sizeof number);
		strcat(buff, coma);

		itoa(Data_to_save.pressures[i],number,10);
		strcat(buff, number);
		memset(number, 0, sizeof number);
		strcat(buff, coma);

		itoa(Data_to_save.wind_speeds[i],number,10) ;
		strcat(buff, number);
		memset(number, 0, sizeof number);
		strcat(buff, coma);

		itoa(Data_to_save.wind_directions[i],number,10) ;
		strcat(buff, number);
		memset(number, 0, sizeof number);
		strcat(buff, coma);

		itoa(Data_to_save.rainfalls[i],number,10) ;
		strcat(buff, number);
		memset(number, 0, sizeof number);
		strcat(buff, rc);
	}

	printf("backup in progress \r\n");
	printf("value of buffeur %s \r\n", buff);




	//Save protocole #########################################


	//Checking the presence of the sd card ###########################
	if(BSP_SD_IsDetected() == 1){

		//Link the driver to sd card ###########################
		FATFS_LinkDriver(&SD_Driver, SDPath);

		//Register the work area of the volume ###########################
		f_mount(&SDFatFS, (TCHAR const*)NULL, 0);

		//Open file for writing ###########################
		if(f_open(&SDFile, "DATA.CSV", FA_OPEN_APPEND | FA_WRITE) != FR_OK)
		{

			printf("cannot open SD card\r\n");
		}

		else
		{

			//Write to the csv file ###########################
			res = f_write(&SDFile, buff, strlen(buff), (void *)&byteswritten);
			if((byteswritten == 0) || (res != FR_OK))
			{
				printf("cannot write to SD card \r\n");
			}
			else
			{

				f_close(&SDFile);
			}

			//Unlink the driver ###########################
			printf("save success\r\n");
			memset(buff, 0, sizeof buff);
			for(int i = 0; i<Data_to_save.nb_data; i++){
				Data_to_save.dates[i].seconds = 0;
				Data_to_save.dates[i].minute = 0;
				Data_to_save.dates[i].hour = 0;
				Data_to_save.temperatures[i] = 0;
				Data_to_save.pressures[i] = 0;
				Data_to_save.wind_directions[i] = 0;
				Data_to_save.wind_speeds[i] = 0;
				Data_to_save.wind_directions[i] = 0;
				Data_to_save.humidities[i] = 0;
			}
			Data_to_save.nb_data = 0;
			FATFS_UnLinkDriver(SDPath);
			memset(buff, 0, sizeof buff);
			//clearBuffers(T_DataToSave);
		}

	}
	else
	{
		printf("no card is mounted\r\n");
		memset(buff, 0, sizeof buff);
		FATFS_UnLinkDriver(SDPath);
	}
}

