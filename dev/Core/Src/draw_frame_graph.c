#include "draw_frame_graph.h"

//----------Global variables----------//

TS_StateTypeDef *TS_State;

uint8_t IS_HOME;

uint8_t SCREEN_INDEX;

//----------Functions----------//

void init_screen() {

	BSP_LCD_Init();

	//(uint32_t)0xC0000000 : Address for the Frame Buffer
	BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, (uint32_t)0xC0000000);

	BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
	BSP_TS_ResetTouchData(TS_State);
	BSP_TS_ITConfig();
	BSP_TS_ITClear();
}

void display_home(void) {

	IS_HOME = 1;

	//Set LCD Foreground Layer
	BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

	/* Clear the LCD */
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);

	/* Draw the panel's dashboard */
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
	BSP_LCD_FillRect(20, 40, BSP_LCD_GetXSize()-40, 52);

	/* Home text */
	BSP_LCD_SetFont(&Font20);
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTBLUE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(0, 60, (uint8_t *)"Dashboard", CENTER_MODE);

	double measure;
	uint8_t value[10];

	/* Display our 6 buttons */
	measure = Weather_station.temperature;
	sprintf((char *)value, "%2.f", measure);
	draw_main_button(20, 112,(uint8_t *)TEMP_TITLE, (uint8_t *) value);

	measure = Weather_station.humidity;
	sprintf((char *)value, "%2.f", measure);
	draw_main_button(173, 112,(uint8_t *)HUM_TITLE, (uint8_t *) value);

	measure = Weather_station.pressure;
	sprintf((char *)value, "%2.f", measure);
	draw_main_button(326, 112,(uint8_t *)PRES_TITLE, (uint8_t *) value);

	measure = Weather_station.wind_speed;
	sprintf((char *)value, "%2.f", measure);
	draw_main_button(20, 192,(uint8_t *)WS_TITLE, (uint8_t *) value);

	measure = Weather_station.wind_direction;
	//sprintf((char *)value, "%2.f", measure);
	draw_main_button(173, 192,(uint8_t *) WD_TITLE, windDirectionLabel(measure));

	measure = Weather_station.rainfall;
	sprintf((char *)value, "%2.f", measure);
	draw_main_button(326, 192,(uint8_t *)RAIN_TITLE, (uint8_t *) value);

	display_timestamp();
}

void display_screen(double values[], uint8_t nbMeasures, char* Ylabel, char* title) {

	IS_HOME = 0;

	if (nbMeasures < 3) {
		display_error_measures(1);
		return;
	}

	if (nbMeasures > 24) {

		display_error_measures(0);
		return;
	}

	display_header(title, nbMeasures);

	display_graph(values, nbMeasures, Ylabel);

	//Drawing for the return button
	draw_return_button(480 - (BSP_LCD_GetYSize()/RATIO)/2, (BSP_LCD_GetYSize()/RATIO)/2, 40);
}

void display_header(char* title, uint8_t nbMeasures) {

	//Set LCD Foreground Layer
	BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

	/* Clear the LCD */
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	//Set the LCD Text Color
	BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);

	/* Frame's title */
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt(20, 20,(uint8_t*) title, LEFT_MODE);

	/* Frame's subtitle */
	BSP_LCD_SetFont(&Font12);
	//Label for the steps on the Y axis
	uint8_t infos[50];
	sprintf((char *)infos, "the last %d statements", nbMeasures);
	BSP_LCD_DisplayStringAt(20, 45, infos, LEFT_MODE);

	/* Screen divided */
	BSP_LCD_DrawLine(480 - BSP_LCD_GetYSize()/RATIO, 0, 480 - BSP_LCD_GetYSize()/RATIO, BSP_LCD_GetYSize()/RATIO);//Vertical
	BSP_LCD_DrawLine(0, BSP_LCD_GetYSize()/RATIO, 480, BSP_LCD_GetYSize()/RATIO);//Horyzontal

}

void display_graph(double measures[], uint8_t nbMeasures, char* YLabel) {

	/* Drawing Axis of the graph */
	//Y Axis
	BSP_LCD_DrawLine(OFFSET*2, BSP_LCD_GetYSize() - OFFSET, OFFSET*2, (BSP_LCD_GetYSize()/RATIO) + OFFSET);
	//X Axis
	BSP_LCD_DrawLine(OFFSET*2, BSP_LCD_GetYSize() - OFFSET, BSP_LCD_GetXSize() - OFFSET, BSP_LCD_GetYSize() - OFFSET);

	/* Drawing arrowheads */
	//X arrowhead
	BSP_LCD_DrawLine(BSP_LCD_GetXSize() - OFFSET - 10, BSP_LCD_GetYSize() - OFFSET - 10, BSP_LCD_GetXSize() - OFFSET, BSP_LCD_GetYSize() - OFFSET);
	BSP_LCD_DrawLine(BSP_LCD_GetXSize() - OFFSET - 10, BSP_LCD_GetYSize() - OFFSET + 10, BSP_LCD_GetXSize() - OFFSET, BSP_LCD_GetYSize() - OFFSET);
	//Y arrowhead
	BSP_LCD_DrawLine(OFFSET*2 + 10, (BSP_LCD_GetYSize()/RATIO) + OFFSET + 10, OFFSET*2, (BSP_LCD_GetYSize()/RATIO) + OFFSET);
	BSP_LCD_DrawLine(OFFSET*2 - 10, (BSP_LCD_GetYSize()/RATIO) + OFFSET + 10, OFFSET*2, (BSP_LCD_GetYSize()/RATIO) + OFFSET);

	/* Axis labels */
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_DisplayStringAt(OFFSET * 3, (BSP_LCD_GetYSize()/RATIO) + (OFFSET/2),(uint8_t*) YLabel, LEFT_MODE);

	/* Initialization of the N = size points that will be displayed to draw the curve */
	Point measurePoints[nbMeasures];
	for (int i = 0; i < nbMeasures; i++) {
		measurePoints[i].X = 0;
		measurePoints[i].Y = 0;
	}

	//Number of steps on X Axis
	int nbStepX = nbMeasures + 1;
	//X Axis length
	int axisXLng = (BSP_LCD_GetXSize() - OFFSET) - OFFSET*2;
	//Step of the X axis
	int stepX = axisXLng/nbStepX;

	/* Drawing steps on the X Axis */
	for (int i = 0; i < nbMeasures; i++) {

		//From 0 to size-1, so N = "size" measures

		BSP_LCD_DrawLine(OFFSET*2 + (i+1)*stepX, BSP_LCD_GetYSize() - OFFSET + 2, OFFSET*2 + (i+1)*stepX, BSP_LCD_GetYSize() - OFFSET - 2);//X Axis

		//The X coordinate of the current point is the same as the current step
		measurePoints[i].X = OFFSET*2 + (i+1)*stepX;
	}

	//Label for the steps on the Y axis
	uint8_t stepsLabel[5];

	/* Min and max values from the array of measures */
	double min = min_value(measures, nbMeasures);
	double max = max_value(measures, nbMeasures);

	/* Y Coordinates corresponding at min and max measures */
	uint16_t YMax = 0;
	uint16_t YMin = 0;

	//Number of steps on the Y Axis
	int nbStepY;

	if (nbMeasures > 6) {
		nbStepY = 6;
	} else {
		nbStepY = nbMeasures;
	}

	//Y Axis length
	uint32_t ySize = BSP_LCD_GetYSize();
	int axisYLng = (ySize - OFFSET) - ((ySize/RATIO) + OFFSET);
	//Step of the Y axis
	int stepY = axisYLng/nbStepY;

	//Font for the labels
	BSP_LCD_SetFont(&Font8);

	/* Amplitude of the measurements and steps between each of them */
	double amp = max - min;

	//To counter an array of the same values
	if (amp == 0) {
		amp = 1;
	}

	double stepOfMeasure = amp/(nbStepY-1);

	/* Drawing steps on Y Axis */
	for (int i = 0; i < nbStepY; i++) {

		BSP_LCD_DrawLine(OFFSET*2 - 2, BSP_LCD_GetYSize() - OFFSET - (i)*stepY, OFFSET*2 + 2, BSP_LCD_GetYSize() - OFFSET - (i)*stepY);//Y Axis

		if (i == 0) {

			sprintf((char *)stepsLabel, "%.2f", min);

			YMin = BSP_LCD_GetYSize() - OFFSET - (i)*stepY;
		} else if (i == nbStepY-1) {

			sprintf((char *)stepsLabel, "%.2f", max);

			YMax = BSP_LCD_GetYSize() - OFFSET - (i)*stepY;
		} else {

			sprintf((char *)stepsLabel, "%.2f", min + i*stepOfMeasure);
		}

		BSP_LCD_DisplayStringAt(OFFSET/3, BSP_LCD_GetYSize() - OFFSET - (i)*stepY,(uint8_t *) stepsLabel, LEFT_MODE);
	}

	//Red color for the curve
	BSP_LCD_SetTextColor(LCD_COLOR_RED);

	//Amplitude between Y coordinates of min and max measures
	uint16_t YAmp = YMin - YMax;

	/* Process to determinate Y coordinates of each points of measure */
	for (int i = 0; i < nbMeasures; i++) {

		double currentValue = measures[i];

		//Cross product, where the minimum measurement represents 100% of the Y axis amplitude
		measurePoints[i].Y = (BSP_LCD_GetYSize() - OFFSET) - ((currentValue-min)/amp)*YAmp;

		BSP_LCD_FillCircle(measurePoints[i].X, measurePoints[i].Y, 2);
	}

	for (int i = 0; i < nbMeasures-1; i++) {

		BSP_LCD_DrawLine(measurePoints[i].X, measurePoints[i].Y, measurePoints[i+1].X, measurePoints[i+1].Y);
	}
}

void display_histo(uint16_t values[], uint8_t nbMeasures, char* YLabel, char* title) {

	display_header(title, nbMeasures);

	//Draw histo

	//Drawing for the return button
	draw_return_button(480 - (BSP_LCD_GetYSize()/RATIO)/2, (BSP_LCD_GetYSize()/RATIO)/2, 40);
}

void draw_main_button(uint16_t x, uint16_t y, uint8_t * text, uint8_t* value) {

	/* Draw the button */
	BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
	BSP_LCD_DrawRect(x,y,133,70);
	BSP_LCD_FillRect(x,y,133,20);

	/* Display the button's label */
	BSP_LCD_SetFont(&Font12);
	BSP_LCD_SetBackColor(LCD_COLOR_DARKBLUE);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_DisplayStringAt(x+5,y+5, text,LEFT_MODE);

	/* Display the mesurand's value */
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
	BSP_LCD_DisplayStringAt(x+5,y+35, value,LEFT_MODE);
}

void draw_return_button(uint16_t x, uint16_t y, uint16_t radius) {

	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE);
	BSP_LCD_FillCircle(x,y,radius);

	BSP_LCD_SetFont(&Font20);
	BSP_LCD_SetBackColor(LCD_COLOR_LIGHTBLUE);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

	BSP_LCD_DisplayStringAt(x-27,y-7, (uint8_t *)"HOME",LEFT_MODE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
}

void display_timestamp(void) {

	BSP_LCD_SetFont(&Font12);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(20, 20, (uint8_t *)"05/12/2021 18:35", LEFT_MODE);
}

void display_error_measures(uint8_t bool) {

	//Set LCD Foreground Layer
	BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

	/* Clear the LCD */
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	//Set the LCD Text Color
	BSP_LCD_SetTextColor(LCD_COLOR_RED);

	//Set the LCD Text Font
	BSP_LCD_SetFont(&Font24);

	BSP_LCD_DisplayStringAt(0, 136,(uint8_t*) "ERROR", CENTER_MODE);

	//Set the LCD Text Font
	BSP_LCD_SetFont(&Font12);

	if (bool) {

		BSP_LCD_DisplayStringAt(0, 166,(uint8_t*) "There must be at least 3 measurements for the measurand !", CENTER_MODE);
	} else {

		BSP_LCD_DisplayStringAt(0, 166,(uint8_t*) "There should be a maximum of 24 measurements for the measurand !", CENTER_MODE);
	}

	//Drawing for the return button
	draw_return_button(480 - (BSP_LCD_GetYSize()/RATIO)/2, (BSP_LCD_GetYSize()/RATIO)/2, 40);
}

void update_screen(void) {

	if (IS_HOME == 1) {

		display_home();
	} else {

		switch (SCREEN_INDEX) {
			case 1:
				display_screen(Graphics_data.temperatures, GRAPHICS_SIZE, TEMP_Y_LABEL, TEMP_TITLE);
				break;
			case 2:
				display_screen(Graphics_data.humidities, GRAPHICS_SIZE, HUM_Y_LABEL, HUM_TITLE);
				break;
			case 3:
				display_screen(Graphics_data.pressures, GRAPHICS_SIZE, PRES_Y_LABEL, PRES_TITLE);
				break;
			case 4:
				display_screen(Graphics_data.wind_speeds, GRAPHICS_SIZE, WS_Y_LABEL, WS_TITLE);
				break;
			case 5:
				display_home();
				break;
			case 6:
				display_screen(Graphics_data.rainfalls, GRAPHICS_SIZE, RAIN_Y_LABEL, RAIN_TITLE);
				break;
			default:
				display_home();
				break;
		}
	}
}

double min_value(double values[], uint8_t size) {

	double min = values[0];

	for (int i = 1; i < size; i++) {

		if (values[i] < min) {

			min = values[i];
		}
	}

	return min;
}

double max_value(double values[], uint8_t size) {

	double max = values[0];

	for (int i = 1; i < size; i++) {

		printf("%d",(int)values[i]);

		if (values[i] > max) {

			max = values[i];
		}
	}

	return max;
}

uint8_t* windDirectionLabel(double angle) {

	switch ((int)angle) {
		case 0:
			return "N";
			break;
		case 45:
			return "NE";
			break;
		case 90:
			return "E";
			break;
		case 135:
			return "SE";
			break;
		case 180:
			return "S";
			break;
		case 225:
			return "SW";
			break;
		case 270:
			return "W";
			break;
		case 315:
			return "NW";
			break;
		default:
			return "?";
			break;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	/* Check in polling mode in touch screen the touch status and coordinates */
	/* if touch occurred */
	BSP_TS_GetState(TS_State);

	/* Get X and Y position of the touch post calibrated */
	uint16_t X = TS_State->touchX[0];
	uint16_t Y = TS_State->touchY[0];

	if(IS_HOME == 1) {
		if (X>20 && X<153 && Y>112 && Y<182) {

			SCREEN_INDEX = 1;

			//Temperature
			display_screen(Graphics_data.temperatures, GRAPHICS_SIZE, TEMP_Y_LABEL, TEMP_TITLE);
		}
		else if (X>173 && X<306 && Y>112 && Y<182) {

			SCREEN_INDEX = 2;

			//Humidity
			display_screen(Graphics_data.humidities, GRAPHICS_SIZE, HUM_Y_LABEL, HUM_TITLE);
		}
		else if (X>326 && X<459 && Y>112 && Y<182) {

			SCREEN_INDEX = 3;

			//Pressure
			display_screen(Graphics_data.pressures, GRAPHICS_SIZE, PRES_Y_LABEL, PRES_TITLE);
		}
		else if (X>20 && X<153 && Y>192 && Y<262) {

			SCREEN_INDEX = 4;

			//Wind speed
			display_screen(Graphics_data.wind_speeds, GRAPHICS_SIZE, WS_Y_LABEL, WS_TITLE);
		}
		else if (X>173 && X<306 && Y>192 && Y<262) {

			SCREEN_INDEX = 5;

			//Wind direction
			//do stuff
		}
		else if (X>326 && X<459 && Y>192 && Y<262) {

			SCREEN_INDEX = 6;

			//Pulvimeter
			display_screen(Graphics_data.rainfalls, GRAPHICS_SIZE, RAIN_Y_LABEL, RAIN_TITLE);
		}
	}
	else//Return to home
	{
		if (X>390 && Y<90)
		{
			SCREEN_INDEX = 0;

			display_home();
		}
	}
}
