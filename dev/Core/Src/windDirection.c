/*
 * windDirection.c
 *
 *  Created on: Dec 7, 2021
 *      Author: pauli
 */

// Do not forget to add this in the initialization

double getDirection(code)
{
	//This function does the acquisition and returns the direction of the wind in degrees. It assumes 8 positions depending on the
	//numerical value read by the ADC. We have determined theoretically and confirmed experimentally the range of numerical values
	//for each of the 8 positions

	if (code < 2000)
	{
		//printf("E\n\r");
		return 90.0;
	}
	else if (code < 2200)
	{
		//printf("SE\n\r");
		return 135.0;
	}

	else if (code < 2500)
	{
		//printf("S\n\r");
		return 180.0;
	}

	else if (code < 3000)
	{
		//printf("NE\n\r");
		return 45.0;
	}

	else if (code < 3300)
	{
		//printf("SW\n\r");
		return 225.0;
	}

	else if (code < 3600)
	{
		//printf("N\n\r");
		return 0.0;
	}

	else if (code < 3780)
	{
		//printf("NW\n\r");
		return 315.0;
	}
	else if (code < 4000)
	{
		//printf("W\n\r");
		return 270.0;
	}
}
