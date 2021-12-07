/**************************************************************
   Windspeed, from WeatherStation library, is available for STM32F746G platform to manage
   our connected WeatherStation.

   Licensed under University of Poitiers M1 Connected Objects by TD1 GRP1.
   Produced by Theo Biardeau.
 **************************************************************/

#include "Windspeed.h"

// - Give the wind speed saved since the last call function
double captureWindspeed(double *wind_tick, const int delay) {
    if (delay == 0) {
        //Compute wind speed, reset wind_tick counter and return wind speed
        displayWindspeed(*wind_tick, wind_speed, delay);

        return wind_speed;
    } else {
        //Compute wind speed, reset wind_tick counter and return wind speed
        double wind_speed =  (*wind_tick * 2.4)/delay;
        *wind_tick = 0;
        displayWindspeed(*wind_tick, wind_speed, delay);

        return wind_speed;
    }

}

// - Monitoring data via UART serial port
void displayWindspeed(double counter, double windspeed, const int delay) {
    printf("====== MONITORING WIND SPEED ======\r\n");
    if (delay == 0) {
        printf("=> ERROR WIND SPEED : In function \"captureWindspeed\", delay cannot be equal to 0. \r\n");
    }
    printf("Counter : %ld \r\n", counter);
    printf("Windspeed : %f mm/h\r\n", windspeed);
}