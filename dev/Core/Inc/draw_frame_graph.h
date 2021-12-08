#include <stdio.h>
#include "../../Drivers/BSP/STM32746G-Discovery/stm32746g_discovery.h"
#include "../../Drivers/BSP/STM32746G-Discovery/stm32746g_discovery_lcd.h"
#include "../../Drivers/BSP/STM32746G-Discovery/stm32746g_discovery_ts.h"
#include "WeatherStation.h"

//Extern variables//

/**
 * Flag to know if it's dashboard
 */
extern uint8_t IS_HOME;

/**
 * Index of the screen
 * 0 : Home
 * 1 : Temperature
 * 2 : Humidity
 * 3 : Pressure
 * 4 : Wind speed
 * 5 : Wind direction
 * 6 : Rain
 */
extern uint8_t SCREEN_INDEX;

//----------Constants----------//

/*
 * Ratio to divide the screen (1/3)
 * ! DO NOT EDIT !
 */
#define RATIO 3

/**
 * General offset for the GUI
 * ! DO NOT EDIT !
 */
#define OFFSET 20

/**
 * Texts for the displaying of each measurand
 */
//Temperature
#define TEMP_TITLE "Temperature (C)"
#define TEMP_Y_LABEL "(C)"

//Humidity
#define HUM_TITLE "Humidity (%)"
#define HUM_Y_LABEL "(%)"

//Pressure
#define PRES_TITLE "Pressure (hpa)"
#define PRES_Y_LABEL "(hpa)"

//Rain
#define RAIN_TITLE "Rain (mm/h)"
#define RAIN_Y_LABEL "(mm/h)"

//Wind speed
#define WS_TITLE "Wind speed (km/h)"
#define WS_Y_LABEL "(km/h)"

//Wind direction
#define WD_TITLE "Wind direction"
#define WD_Y_LABEL ""

//----------Functions----------//

/**
 * Hardware initialization of the screen
 */
void init_screen(void);

/**
 * Display the dashboard at the home page
 */
void display_home(void);

/**
 * Display the header and the graph corresponding to a measurand on the screen
 * param1, float values[] : array of measures
 * param2, uint8_t nbMeasures : number of measures
 * param3, char* Ylabel : Label of the Y Axis
 * param4, char* title : title of the screen
 */
void display_screen(float values[], uint8_t nbMeasures, char* YLabel, char* title);

/**
 * Display the header of the graph's/histo's screen
 * param1, char* title : title of the screen
 * param2, uint8_t nbMeasures : number of measures
 */
void display_header(char* title, uint8_t nbMeasures);

/**
 * Display the graph with the curve corresponding to the parameters
 * param1, float values[] : array of measures
 * param2, uint8_t nbMeasures : number of measures
 * param3, char* Ylabel : Label of the Y Axis
 */
void display_graph(float values[], uint8_t nbMeasures, char* YLabel);

/**
 * Display the histogram corresponding to the wind direction
 * and the header of the screen
 * param1, uint16_t values[] : array of measures for wind direction
 * param2, uint8_t nbMeasures : number of measures
 * param3, char* Ylabel : Label for the Y Axis
 * param3, char* title : title of the screen
 */
void display_histo(uint16_t values[], uint8_t nbMeasures, char* YLabel, char* title);

/**
 * Draw a button corresponding to a measure in the dashboard
 * param1, uint16_t x : x coordinate of the top left corner
 * param2, uint16_t y : y coordinate of the top left corner
 * param3, uint8_t* text : label for the button
 * param3, uint8_t* value : measurand's value to display
 */
void draw_main_button(uint16_t x, uint16_t y, uint8_t * text, uint8_t * value);

/**
 * Draw the button to return to the dashboard
 * param1, uint16_t x : x coordinate of the center
 * param2, uint16_t y : y coordinate of the center
 * param3, uint16_t radius : radius of the circle
 */
void draw_return_button(uint16_t x, uint16_t y, uint16_t radius);

/**
 * Display the timestamp
 */
void display_timestamp(void);

/**
 * Simple function to display an error message,
 * if there are too few or too much measures to display the graph or the histo
 * param1, uint8_t bool : precise if there too few or too much values
 * 0 <=> too much values
 * 1+ <=> too few values
 */
void display_error_measures(uint8_t bool);

/**
 * Update the displaying depending of the SCREEN_INDEX
 */
void update_screen(void);

/**
 * Find the min value from the array
 * param1, float values[] : array of values
 * param2, uint8_t size : array length
 */
float min_value(float values[], uint8_t size);

/**
 * Find the max value from the array
 * param1, float values[] : array of values
 * param2, uint8_t size : array length
 */
float max_value(float values[], uint8_t size);

/**
 * Convert the angle in degrees of the wind direction in the corresponding label
 */
uint8_t* windDirectionLabel(float angle);

/**
 * Handler for the interrupt from the touch screen
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
