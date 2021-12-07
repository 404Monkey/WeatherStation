/**
* @author Benjamin Chevais
* @date 01/12/21
*/

#pragma once

#define GRAPHICS_SIZE 24 // size of the history arrays
#define DATA_SIZE 100 // size of the history arrays


// Definition of a simulated database object
typedef struct T_GraphicsData {
    // To store the last 24 acquisitions
    float temperatures[GRAPHICS_SIZE];
    float humidities[GRAPHICS_SIZE];
    float pressures[GRAPHICS_SIZE];
    float rainfalls[GRAPHICS_SIZE];
    float wind_speeds[GRAPHICS_SIZE];
    float wind_directions[GRAPHICS_SIZE];
} T_GraphicsData;

T_GraphicsData GraphicsData(); // T_GraphicsData constructor
void addGraphicsData(T_GraphicsData* gd, float temp, float hum, float press, float rain, float wspeed, float wdir); // add all acquisitions in database


// Definition of DataToSave
typedef struct T_DataToSave {

    // To store the not saved data
    float temperatures[DATA_SIZE];
    float humidities[DATA_SIZE];
    float pressures[DATA_SIZE];
    float rainfalls[DATA_SIZE];
    float wind_speeds[DATA_SIZE];
    float wind_directions[DATA_SIZE];

    // to know how much data we have
    int nb_data;

} T_DataToSave;

T_DataToSave DataToSave(); // T_DataToSave constructor
void addDataToSave(T_DataToSave * ds, float temp, float hum, float press, float rain, float wspeed, float wdir); // add all data to save
void clearBuffers(T_DataToSave* ds);

// Definition of the Weather Station object
typedef struct T_WeatherStation {
    float temperature;
    float humidity;
    float pressure;
    float rainfall;
    float wind_speed;
    float wind_direction; // degrees
} T_WeatherStation;

T_WeatherStation WeatherStationDefault(); // Default Constructor
T_WeatherStation WeatherStation(float temp, float hum, float press, float rain, float wspeed, float wdir); // Constructor with args
void updateWeatherStation(T_WeatherStation* ws, T_GraphicsData* gd, T_DataToSave * ds, float temp, float hum, float press, float rain, float wspeed, float wdir); // Update the current values of the WeatherStation


// Constants
T_WeatherStation Weather_station;
T_GraphicsData Graphics_data;
T_DataToSave Data_to_save;

void WeatherStationInit();
