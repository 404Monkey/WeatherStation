/**
* @author Benjamin Chevais
* @date 01/12/21
*/


#ifndef INC_WEATHERSTATION_H_
#define INC_WEATHERSTATION_H_

#define GRAPHICS_SIZE 24 // size of the history arrays
#define DATA_SIZE 100 // size of the history arrays


// Definition of a simulated database object
typedef struct T_GraphicsData {
    // To store the last 24 acquisitions
    double temperatures[GRAPHICS_SIZE];
    double humidities[GRAPHICS_SIZE];
    double pressures[GRAPHICS_SIZE];
    double rainfalls[GRAPHICS_SIZE];
    double wind_speeds[GRAPHICS_SIZE];
    double wind_directions[GRAPHICS_SIZE];
} T_GraphicsData;

T_GraphicsData GraphicsData(); // T_GraphicsData constructor
void addGraphicsData(T_GraphicsData* gd, double temp, double hum, double press, double rain, double wspeed, double wdir); // add all acquisitions in database


// Definition of DataToSave
typedef struct T_DataToSave {

    // To store the not saved data
	double temperatures[DATA_SIZE];
	double humidities[DATA_SIZE];
	double pressures[DATA_SIZE];
	double rainfalls[DATA_SIZE];
	double wind_speeds[DATA_SIZE];
	double wind_directions[DATA_SIZE];

    // to know how much data we have
    int nb_data;

} T_DataToSave;

T_DataToSave DataToSave(); // T_DataToSave constructor
void addDataToSave(T_DataToSave * ds, double temp, double hum, double press, double rain, double wspeed, double wdir); // add all data to save
void clearBuffers(T_DataToSave* ds);

// Definition of the Weather Station object
typedef struct T_WeatherStation {
	double temperature;
	double humidity;
	double pressure;
	double rainfall;
	double wind_speed;
	double wind_direction; // degrees
} T_WeatherStation;

T_WeatherStation WeatherStationDefault(); // Default Constructor
T_WeatherStation WeatherStation(double temp, double hum, double press, double rain, double wspeed, double wdir); // Constructor with args
void updateWeatherStation(T_WeatherStation* ws, T_GraphicsData* gd, T_DataToSave * ds, double temp, double hum, double press, double rain, double wspeed, double wdir); // Update the current values of the WeatherStation


// Constants
T_WeatherStation Weather_station;
T_GraphicsData Graphics_data;
T_DataToSave Data_to_save;

void WeatherStationInit();

#endif /* INC_WEATHERSTATION_H_ */

