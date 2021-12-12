/**************************************************************
   Windspeed, from WeatherStation library, is available for STM32F746G platform to manage
   our connected WeatherStation.

   Licensed under University of Poitiers M1 Connected Objects by TD1 GRP1.
   Produced by Theo Biardeau.
 **************************************************************/

#include "Windspeed.h"

// - Give the wind speed saved since the last call function
double captureWindspeed(double *wind_tick, const int delay) {
    //Check if delay equals to zero
    if (delay == 0) {
        //If so, display an error message and return an error value
        displayWindspeed(*wind_tick, WINDSPEED_ERROR_VAL, delay);

        return WINDSPEED_ERROR_VAL;
    } else {
        //If not, compute windspeed and reset the windtick, then display and return it
        double wind_speed = (*wind_tick * 2 * 3.14 * 0.07 * 3.6) / delay;
        //displayWindspeed(*wind_tick, wind_speed, delay);
        *wind_tick = 0;

        return wind_speed;
    }
}

// - Monitoring data via UART serial port
void displayWindspeed(double counter, double windspeed, const int delay) {
    printf("====== MONITORING WIND SPEED ======\r\n");
    if (delay == 0) {
        printf("=> ERROR WIND SPEED : In function \"captureWindspeed\", delay cannot be equal to 0. \r\n");
    }
    printf("Counter : %f \r\n", counter);
    printf("Windspeed : %f km/h\r\n", windspeed);
}
