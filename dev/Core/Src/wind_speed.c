/*
 * wind_speed.c
 *
 *  Created on: Dec 3, 2021
 *      Author: theo
 */



int getwind_speed (double *wind_tick, const int sampling){
	double wind_speed =  (*wind_tick * 2.4)/sampling;
	*wind_tick = 0;
	return((int)wind_speed);
}


