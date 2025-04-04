#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_TRIES 3

void WeightedRunningMean(double* measurements, double* weightedRunningMean, int numInRunningMean); 

int main()
{
    int tries = 0;
    double *myMeasurements = NULL;
    double *myRunningMean = NULL;
    char filename[256];
    int numMeas = 0;
    int count = 0;

    while(tries < MAX_TRIES)
    {
        printf("Enter the name of the input file: ");
        scanf("%255s", filename);

        FILE *file = fopen(filename, "r");
        if(file == NULL) 
        {
            printf("ERROR: Input file %s not opened", filename);
            tries++;

            if(tries == MAX_TRIES) 
            {
                printf("ERROR: too many failures opening input file");
                return 0;
            }
        }
  
        else
        {
            tries = 0;

            while(tries < MAX_TRIES)
            {
                printf("Enter the number of measurements: ");
                scanf("%d", &numMeas);

                if(numMeas < 0 || 40 < numMeas)
                {
                    printf("ERROR: numMeas is out of range \n\
           enter 0<numMeas<=40");
                    tries++;

                    if(tries == MAX_TRIES) 
                    {
                        printf("ERROR: too many failures reading the number of measurements");
                        return 0;
                    }
                }

                else
                {
                    double firstChar = 0;

                    if(fscanf(filename, "%lf", &firstChar) != 1)
                    {
                        printf("ERROR: input file is empty");
                        return 0;
                    }

                    myMeasurements = malloc(numMeas * sizeof(double));
                    myRunningMean = malloc(numMeas * sizeof(double));

                    if (myMeasurements == NULL || myRunningMean == NULL) 
                    {
                        printf("ERROR: Memory allocation failed\n");
                        free(myMeasurements);
                        free(myRunningMean);
                        fclose(file);
                        return EXIT_FAILURE;
                    }

                    else
                    {
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
                }
            }
        }
    }

    return 0;
}

void WeightedRunningMean(double* measurements, double* weightedRunningMean, int numInRunningMean)
{
    for(int k = 0; k < numInRunningMean; k++) 
    {
        if(k == 0) 
        {
            weightedRunningMean[k] = measurements[k];
        } 
        
        else 
        {
            weightedRunningMean[k] = (weightedRunningMean[k - 1] / 2.0 + measurements[k]) / 1.5;
        }
    }
}
