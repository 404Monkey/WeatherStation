#include "../../Drivers/BSP/STM32746G-Discovery/stm32746g_discovery.h"
#include "../../Drivers/BSP/STM32746G-Discovery/stm32746g_discovery_lcd.h"
#include "../../Drivers/BSP/STM32746G-Discovery/stm32746g_discovery_ts.h"
#include <stdio.h>
#include <stdlib.h>

//----------Constants----------//

/*
 * RATIO to divide the screen (1/4, 1/3, ...)
 * (1/RATIO) for Title and subtitle
 * (2/RATIO) for the curve
 */
#define RATIO 3

/**
 * General offset for the GUI
 */
#define OFFSET 20

//Temperature
#define TEMP_TITLE "Temperature (°C)"
#define TEMP_Y_LABEL "(°C)"

//Humidity
#define HUM_TITLE "Humidity (%)"
#define HUM_Y_LABEL "(%)"

//Pressure
#define PRES_TITLE "Pressure (hpa)"
#define PRES_Y_LABEL "(hpa)"

//Rain
#define RAIN_TITLE "Rain (?)"
#define RAIN_Y_LABEL "(mm/h)"

//Wind speed
#define WS_TITLE "Wind speed (km/h)"
#define WS_Y_LABEL "(km/h)"

//----------Extern variables----------//

/**
 *  Define the weather data
 */

/* Values for each mesurand */
extern float* TEMP_VALUES;
extern float* HUM_VALUES;
extern float* PRES_VALUES;
extern float* WS_VALUES;
extern float* RAIN_VALUES;

/* Length for each array of values */
extern int TEMP_SIZE;
extern int HUM_SIZE;
extern int PRES_SIZE;
extern int WS_SIZE;
extern int RAIN_SIZE;

//----------Functions----------//

/**
 * Initialization of the screen
 */
void init_screen(void);

/**
 * Display the dashboard
 */
void display_home(void);

/**
 * Display the frame/screen with the curve corresponding to the parameters
 * param1, float values[] : array of measures
 * param2, int size : array length
 * param3, uint8_t Xlabel[50] : Label of the X Axis
 * param4, uint8_t Ylabel[50] : Label of the Y Axis
 * param5, uint8_t title[50] : title of the screen
 * param6, uint8_t subTitle[50] : infos of the screen
 */
void display_screen(float values[], int size, char* YLabel, char* title);

/**
 * Draw a button corresponding to a measure in the dashboard
 * param1, uint16_t x : x coordinate of the top left corner
 * param2, uint16_t y : y coordinate of the top left corner
 * param3, uint8_t* text : label for the button
 */
void draw_home_button(uint16_t x, uint16_t y, uint8_t * text, uint8_t * value);

/**
 * Draw the button to return to the dashboard
 * param1, uint16_t x : x coordinate of the center
 * param2, uint16_t y : y coordinate of the center
 * param3, uint16_t radius : radius of the circle
 */
void draw_return_button(uint16_t x, uint16_t y, uint16_t radius);

/**
 * Display the timestamp in the main screen
 */
void display_timestamp(void);

/**
 * Simple function to display an error message
 */
void display_error_measures(uint8_t bool);

/**
 * Find the min value from the array
 * param1, float values[] : array of values
 * param2, int size : array length
 */
float min_value(float values[], int size);

/**
 * Find the max value from the array
 * param1, float values[] : array of values
 * param2, int size : array length
 */
float max_value(float values[], int size);

/**
 * Handler for the interrupt from the touch screen
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
