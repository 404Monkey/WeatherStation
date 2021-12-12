
/*
 * Sdcard.c
 *
 *  Created on: Dec 8, 2021
 *      Author: theo
 */
#include "sd.h"

char buff [2000] = {};
char number[100];
char rc [] = "\r\n";
char coma []= ";";
char wtext[100] = "dated; time; temperature; humidity; pressure; wind speed; wind direction; rain\r\n";

void initSD(){


	printf("card initializationSD\r\n");

	//##-1- Checking the presence of the sd card ##########################
	if(BSP_SD_IsDetected() == 1){

		//##-2- Opening the "data.csv" file###########################
		if(f_open(&SDFile, "DATA.CSV", FA_READ) != FR_OK)
		{
			printf("Init: non-existent file \r\n");
		}
		else
		{
			//##-3- Read data from the text file ###########################
			res = f_read(&SDFile, rtext, sizeof(rtext), (UINT*)&bytesread);

			if((bytesread =! 0) || (res != FR_OK))
			{
				printf("init: empty file\r\n");
			}
			else
			{
				//##-4- Close the open text file #############################
				f_close(&SDFile);
			}
		}


		if(f_mount(&SDFatFS, (TCHAR const*)SDPath, 0) != FR_OK)
		{
			Error_Handler();
		}

		else
		{
			//Open file for writing (Create)
			if(f_open(&SDFile, "Data.csv", FA_OPEN_ALWAYS | FA_WRITE) != FR_OK)
			{
				printf("cannot open SD card\r\n");
			}
			else
			{
				//Write to the text file
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
		f_mount(&SDFatFS, (TCHAR const*)NULL, 0);
	}else
	{
		printf("no card is mounted \r\n");
	}
}




void saveSD(){

	// prepation of data for saving ###################################
	for(int i = 0; i<Data_to_save.nb_data; i++){
		itoa(i,number,10) ;
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


		printf("backup in progress \r\n");
		printf("valeur du buffeur %s \r\n", buff);




		//Save protocole #########################################
		if(BSP_SD_IsDetected() == 1){
			FATFS_LinkDriver(&SD_Driver, SDPath);
			f_mount(&SDFatFS, (TCHAR const*)NULL, 0);
			if(f_open(&SDFile, "Data.csv", FA_OPEN_APPEND | FA_WRITE) != FR_OK)
			{
				printf("cannot open SD card\r\n");
			}
			else
			{
				res = f_write(&SDFile, buff, strlen(buff), (void *)&byteswritten);
				if((byteswritten == 0) || (res != FR_OK))
				{
					printf("cannot write to SD card \r\n");
				}
				else
				{

					printf("save success\r\n");
					f_close(&SDFile);
				}


				FATFS_UnLinkDriver(SDPath);
				memset(buff, 0, sizeof buff);
			}
		}

		else
		{
			printf("no card is mounted\r\n");
		}


	}
}
