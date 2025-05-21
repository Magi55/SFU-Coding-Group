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
   float fahTemp = 0.0; //Fahrenheit temperature
   
   //Ask the user for a Celsius T (prompt)
   printf("Please, enter a temperature in Celsius: ");
   
   //Read the user input
   scanf("%f", &celTemp);
    
   //Convert C to F
   //fahTemp = celTemp * 9/5 + 32;
   //fahTemp = 32 + 9.0/5 * celTemp;
   fahTemp = 32 + (float) 9/5 * celTemp;
    
   //Print results
   printf(" %.1f Celcius => %.1f Fahrenheit\n", celTemp, fahTemp);
    
   return 0;
    
}
    