
/*
 * Sdcard.c
 *
 *  Created on: Dec 8, 2021
 *      Author: theo
 */
#include "sd.h"

char buff [1000] = {};
char number[100];
char rc [] = "\r\n";
char coma []= ";";
char wtext[100] = "numero de mesure; temperature; humidity; pressure; wind speed; wind direction; rain \r\n";

void initSD(){
	printf("initialisation de la carte SD\r\n");
	if(BSP_SD_IsDetected() == 1){
		if(f_open(&SDFile, "DATA.CSV", FA_READ) != FR_OK)
		{
			/* 'STM32.TXT' file Open for read Error */
			printf("Init : fichier non existant \r\n");
		}
		else
		{
			/*##-8- Read data from the text file ###########################*/
			res = f_read(&SDFile, rtext, sizeof(rtext), (UINT*)&bytesread);

			if((bytesread =! 0) || (res != FR_OK))
			{
				/* 'STM32.TXT' file Read or EOF Error */
				printf("init : fichier vide \r\n");
			}
			else
			{
				/*##-9- Close the open text file #############################*/
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
				Error_Handler();
			}
			else
			{
				//Write to the text file
				res = f_write(&SDFile, wtext, strlen(wtext), (void *)&byteswritten);
				if((byteswritten == 0) || (res != FR_OK))
				{
					Error_Handler();
				}
				else
				{
					f_close(&SDFile);
					printf("initialisation reussi \r\n");
				}

			}
		}
		f_mount(&SDFatFS, (TCHAR const*)NULL, 0);
	}else
	{
		printf("aucune carte est monte \r\n");
	}
}


void saveSD(){
	char buff [1000] = {};
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
		printf("sauvegarde en cours \r\n");
		printf("valeur du buffeur %s \r\n", buff);

		if(BSP_SD_IsDetected() == 1){
			//Open file for writing (Create)
			FATFS_LinkDriver(&SD_Driver, SDPath);
			f_mount(&SDFatFS, (TCHAR const*)NULL, 0);
			printf("1\r\n");
			if(f_open(&SDFile, "Data.csv", FA_OPEN_APPEND | FA_WRITE) != FR_OK)
			{
				printf("impossible d'ouvrire la carte SD \r\n");
				f_close(&SDFile);
			}
			else
			{

				printf("3\r\n");
				res = f_write(&SDFile, buff, strlen(buff), (void *)&byteswritten);
				if((byteswritten == 0) || (res != FR_OK))
				{
					printf("impossible d'écrire sur la carte SD \r\n");
				}
				else
				{

					printf("sauvegarde reussite\r\n");
					f_close(&SDFile);
				}


				FATFS_UnLinkDriver(SDPath);
				memset(buff, 0, sizeof buff);
			}
		}

		else
		{
			printf("aucune carte est monte \r\n");
		}


	}
}
