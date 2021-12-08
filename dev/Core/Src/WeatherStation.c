/**
* @author Benjamin Chevais
* @date 01/12/21
*/

#include <stdlib.h>
#include "WeatherStation.h"

// Default Constructor
T_WeatherStation WeatherStationDefault() {

    T_WeatherStation ws;

    ws.temperature = 0;
    ws.humidity = 0;
    ws.pressure = 0;
    ws.rainfall = 0;
    ws.wind_speed = 0;
    ws.wind_direction = 0;
    return ws;
}

// Constructor with args
T_WeatherStation WeatherStation(double temp, double hum, double press, double rain, double wspeed, double wdir) {

    T_WeatherStation ws;

    ws.temperature = temp;
    ws.humidity = hum;
    ws.pressure = press;
    ws.rainfall = rain;
    ws.wind_speed = wspeed;
    ws.wind_direction = wdir;

    return ws;
}

void updateWeatherStation(T_WeatherStation* ws, T_GraphicsData* gd, T_DataToSave * ds, double temp, double hum, double press, double rain, double wspeed, double wdir) {
    ws->temperature = temp;
    ws->humidity = hum;
    ws->pressure = press;
    ws->rainfall = rain;
    ws->wind_speed = wspeed;
    ws->wind_direction = wdir;

    addGraphicsData(gd, temp, hum, press, rain, wspeed, wdir);
    addDataToSave(ds, temp, hum, press, rain, wspeed, wdir);
}



// T_GraphicsData constructor
T_GraphicsData GraphicsData() {

    T_GraphicsData db;

    for(int i = 0; i < GRAPHICS_SIZE; i++){
        db.temperatures[i] = 0;
        db.humidities[i] = 0;
        db.pressures[i] = 0;
        db.rainfalls[i] = 0;
        db.wind_speeds[i] = 0;
        db.wind_directions[i] = 0;
    }

    return db;
}

// rotation left of a float array
void rotation_left(float* tab) {
    if(tab != NULL) {
        float first = tab[0];

        for(int i = 0; i < GRAPHICS_SIZE - 1; i++) {
            tab[i] = tab[i + 1];
        }

        tab[GRAPHICS_SIZE - 1] = first;
    }
}

// add data at the end of one array
void add(float* tab, float data) {
    rotation_left(tab);
    tab[GRAPHICS_SIZE - 1] = data;
}

// add all acquisitions in database
void addGraphicsData(T_GraphicsData* gd, float temp, float hum, float press, float rain, float wspeed, float wdir) {
    add(gd->temperatures, temp);
    add(gd->humidities, hum);
    add(gd->pressures, press);
    add(gd->rainfalls, rain);
    add(gd->wind_speeds, wspeed);
    add(gd->wind_directions, wdir);
}


// T_DataToSave Constructor
T_DataToSave DataToSave() {

    T_DataToSave ds;

    for(int i = 0; i < DATA_SIZE; i++){
        ds.temperatures[i] = 0;
        ds.humidities[i] = 0;
        ds.pressures[i] = 0;
        ds.rainfalls[i] = 0;
        ds.wind_speeds[i] = 0;
        ds.wind_directions[i] = 0;
    }

    ds.nb_data = 0;

    return ds;
}

// add all data to save
void addDataToSave(T_DataToSave * ds, float temp, float hum, float press, float rain, float wspeed, float wdir) {
    int nb = ds->nb_data;

    ds->temperatures[nb] = temp;
    ds->humidities[nb] = hum;
    ds->pressures[nb] = press;
    ds->rainfalls[nb] = rain;
    ds->wind_speeds[nb] = wspeed;
    ds->wind_directions[nb] = wdir;

    ds->nb_data += 1;
};

void clearBuffers(T_DataToSave* ds){
    for (int i = 0; i < ds->nb_data; i++) {
        ds->temperatures[i] = 0;
        ds->humidities[i] = 0;
        ds->pressures[i] = 0;
        ds->rainfalls[i] = 0;
        ds->wind_speeds[i] = 0;
        ds->wind_directions[i] = 0;
    }

    ds->nb_data = 0;
}

void WeatherStationInit() {
    Weather_station = WeatherStationDefault();
    Graphics_data = GraphicsData();
    Data_to_save = DataToSave();
}
