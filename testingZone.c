#include <stdio.h>
#include <stdlib.h>

void WeightedRunningMean(double* measurements, double* weightedRunningMean, int numInRunningMean) {
    for (int k = 0; k < numInRunningMean; k++) 
    {
        if (k == 0) 
        {
            weightedRunningMean[k] = measurements[k];
        } 
        
        else 
        {
            weightedRunningMean[k] = (weightedRunningMean[k - 1] / 2.0 + measurements[k]) / 1.5;
        }
    }
}

int main() 
{
    char filename[100];
    int numMeas;
    double *myMeasurements, *myRunningMean;
    FILE *file;
    
    printf("Enter the name of the input file: ");
    scanf("%s", filename);
    
    int attempts = 0;
    while(attempts < 3) 
    {
        file = fopen(filename, "r");
        if(file) break;
        attempts++;

        printf("ERROR: Input file %s not opened\n", filename);
        if(attempts < 3) 
        {
            printf("Enter the name of the input file: ");
            scanf("%s", filename);
        }
    }

    if(attempts == 3) 
    {
        printf("ERROR: too many failures opening input file\n");
        return 1;
    }
    
/*============*/

    attempts = 0;
    while(attempts < 3) 
    {
        printf("Enter the number of measurements: ");
        if(scanf("%d", &numMeas) != 1 || numMeas <= 0 || numMeas > 40)
        {
            printf("ERROR: numMeas is out of range\n enter 0<numMeas<=40\n");
            attempts++;
        } 
        
        else 
        {
            break;
        }
    }

    if(attempts == 3) 
    {
        printf("ERROR: too many failures reading the number of measurements\n");
        fclose(file);
        return 1;
    }

/*============*/
    
    myMeasurements = (double*)malloc(numMeas * sizeof(double));
    myRunningMean = (double*)malloc(numMeas * sizeof(double));
    if(!myMeasurements || !myRunningMean) 
    {
        printf("ERROR: Memory allocation failed\n");
        fclose(file);
        return 1;
    }
    
    int count = 0;
    while(count < numMeas && fscanf(file, "%lf", &myMeasurements[count]) == 1) 
    {
        count++;
    }
    
    if(count == 0) 
    {
        printf("ERROR: input file is empty\n");
        free(myMeasurements);
        free(myRunningMean);
        fclose(file);
        return 1;
    }
    
    if(count < numMeas) 
    {
        printf("ERROR: fewer than numMeas measurements in the file\n");
    }
    
    WeightedRunningMean(myMeasurements, myRunningMean, count);
    
    printf("The running sums are\n");
    for(int i = 0; i < count; i++) 
    {
        printf("%10.2f", myRunningMean[i]);
        if((i + 1) % 5 == 0) 
        {
            printf("\n");
        }
    }
    
    if(count % 5 != 0) 
    {
        printf("\n");
    }
    
    free(myMeasurements);
    free(myRunningMean);
    fclose(file);
    return 0;
}
