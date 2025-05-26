/*
* Filename: CFFC_v1.c
*
*
*
*
*
*
*
*/

#include <stdio.h>

int main(void)
{
    const char CELSIUS = 'C'
    char choice = CELSIUS;
    float celTemp = 0.0;
    float fahTemp = 0.0;
    
	printf("To convert temperature from Celsius to Fahrenheit ... Enter F\n");
    printf("To convert temperature from Fahrenheit to Celsius ... Enter C\n");
    printf("Your Choice: ");
    scanf("%c", &choice);
    
    if( choice == CELSIUS)
    {
    // F to C
    printf("Please, enter a temperature in Fahrenheit: ");
    scanf("%f", &fahTemp);
    
    //convert F to C
    celTemp = fahTemp * 5/9 - 32;
    
    printf(" %.1f Fahrenheit => %.1f Celsius\n", fahTemp, celTemp);
    }
    
    else
    {
    // C to F
    printf("Please, enter a temperature in Celsius: ");
   
    //Read the user input
    scanf("%f", &celTemp);
    
    //Convert C to F
    fahTemp = 32 + (float) 9/5 * celTemp;
    
    //Print results
    printf(" %.1f Celcius => %.1f Fahrenheit\n", celTemp, fahTemp);
    }
    
    return 0;
}