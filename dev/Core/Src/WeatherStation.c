/**
 * @author Benjamin Chevais
 * @date 01/12/21
 */

#include <stdlib.h>
#include "WeatherStation.h"
#include "rtc.h"
#include "main.h"

// Default T_WeatherStation Constructor
T_WeatherStation WeatherStationDefault() {

	T_WeatherStation ws;

	ws.temperature = 0;
	ws.humidity = 0;
	ws.pressure = 0;
	ws.rainfall = 0;
	ws.wind_speed = 0;
	ws.wind_direction = 0;
	ws.time = getTime();
	return ws;
}

// T_WeatherStation Constructor with args
T_WeatherStation WeatherStation(double temp, double hum, double press, double rain, double wspeed, double wdir, T_Time t) {

	T_WeatherStation ws;

	ws.temperature = temp;
	ws.humidity = hum;
	ws.pressure = press;
	ws.rainfall = rain;
	ws.wind_speed = wspeed;
	ws.wind_direction = wdir;
	ws.time = t;

	return ws;
}

// Update all the weather station structures
void updateWeatherStation(T_WeatherStation* ws, T_GraphicsData* gd, T_DataToSave * ds, double temp, double hum, double press, double rain, double wspeed, double wdir, T_Time t) {
	ws->temperature = temp;
	ws->humidity = hum;
	ws->pressure = press;
	ws->rainfall = rain;
	ws->wind_speed = wspeed;
	ws->wind_direction = wdir;
	ws->time = t;

	addGraphicsData(gd, temp, hum, press, rain, wspeed, wdir);
	addDataToSave(ds, temp, hum, press, rain, wspeed, wdir, t);
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
void rotation_left(double* tab) {
	if(tab != NULL) {
		float first = tab[0];

		for(int i = 0; i < GRAPHICS_SIZE - 1; i++) {
			tab[i] = tab[i + 1];
		}

		tab[GRAPHICS_SIZE - 1] = first;
	}
}

// add data at the end of one array
void add(double* tab, double data) {
	rotation_left(tab);
	tab[GRAPHICS_SIZE - 1] = data;
}

// add all acquisitions in GraphicsData
void addGraphicsData(T_GraphicsData* gd, double temp, double hum, double press, double rain, double wspeed, double wdir) {
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
		ds.dates[i] = DefaultTime();
	}

	ds.nb_data = 0;

	return ds;
}

// add all data to save
void addDataToSave(T_DataToSave * ds, double temp, double hum, double press, double rain, double wspeed, double wdir, T_Time time) {
	int nb = ds->nb_data;

	ds->temperatures[nb] = temp;
	ds->humidities[nb] = hum;
	ds->pressures[nb] = press;
	ds->rainfalls[nb] = rain;
	ds->wind_speeds[nb] = wspeed;
	ds->wind_directions[nb] = wdir;
	ds->dates[nb] = time;

	ds->nb_data += 1;
};

// Clear all the buffers of DataToSave
void clearBuffers(T_DataToSave* ds){
	for (int i = 0; i < ds->nb_data; i++) {
		ds->temperatures[i] = 0;
		ds->humidities[i] = 0;
		ds->pressures[i] = 0;
		ds->rainfalls[i] = 0;
		ds->wind_speeds[i] = 0;
		ds->wind_directions[i] = 0;
		ds->dates[i] = DefaultTime();
	}

	ds->nb_data = 0;
}

// Initialize the 3 structures
void WeatherStationInit() {
	Weather_station = WeatherStationDefault();
	Graphics_data = GraphicsData();
	Data_to_save = DataToSave();
}

// Default Constructors of T_Time
T_Time DefaultTime(){
	T_Time time;
	time.year = 0;
	time.month = 0;
	time.day = 0;
	time.weekday = 0;
	time.hour = 0;
	time.minute = 0;
	time.seconds = 0;
	return time;
}

// Give the date and the time
T_Time getTime() {

	T_Time time;

	RTC_DateTypeDef sDate;
	RTC_TimeTypeDef sTime;

	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);

	time.year = sDate.Year;
	time.month = sDate.Month;
	time.day = sDate.Date;
	time.weekday = sDate.WeekDay;
	time.hour = sTime.Hours;
	time.minute = sTime.Minutes;
	time.seconds = sTime.Seconds;

	return time;
}

// Display a date
void displayTime(T_Time t){
	printf("Date : %02d-%02d-%02d : %02d:%02u:%02u \r\n\n", t.day, t.month, t.year, t.hour, t.minute, t.seconds);
}

