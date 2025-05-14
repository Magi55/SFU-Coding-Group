/*
* Filename: CtoF_v1.c - version 1
*
* Discription: Convert a Celcius temperature to a Fahrenheit temperature.
*		       Conversion: C * 9/5 + 32 = F
* Source: 
*
* Author: HW
* Date: May 2025
*/

#include <stdio.h>

int main(void)
{
	//Get a C temparature
    float celTemp = 2.0; //Celcius temperature
    float farTemp = 0.0; //Fahrenheit temperature
    
    //Convert C to F
    farTemp = celTemp * 9/5 + 32;
    
    //Print results
    printf(" %.1f Celcius => %.1f Fahrenheit\n", celTemp, farTemp);
    
    return 0;
    
}
    