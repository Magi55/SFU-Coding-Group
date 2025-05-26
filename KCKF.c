*
*
*
*/

#include <stdio.h>

int main(void)
{
	const char CELSIUS = 'C';
    //const char FAHRENHEIT = 'F';
    const double ABS_ZERO_IN_CELSIUS = 
    
    char choice = CELSIUS;
    float celTemp = 0.0;
    float fahTemp = 0.0;
    float kelTemp = 0.0;
    
    printf("To convert temperature to Celsius ... Enter C\n");
    printf("To convert temperature to Fahrenheit ... Enter F\n");
    printf("Your Choice: ");
    scanf("%c", &choice);

	printf("Please, enter a Kelvin temperature: ");
    scanf("%f", kelTemp);

	if(choice == CELSIUS)
    {
        //convert fahTemp to celTemp
        celTemp = kelTemp + ABS_ZERO_IN_CELSIUS;
        
        printf("%0.1f Kelvin => %0.1f Celcius\n",kelTemp, celTemp);
    }
    
    else
    {
        //assume choice == FAHRENHEIT
        
        //convert celTemp to fahTemp
        fahTemp = (kelTemp + ABS_ZERO_IN_CELSIUS) * 9.0/5.0 + 32.0;
        
        printf("%0.1f Kelvin => %0.1f Fahrenheit\n",kelTemp, fahTemp);
    }
    
    return 0;
}