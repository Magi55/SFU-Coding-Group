#include <std.io>
#include <stdlib.h>
#include <math.h>

void WeightedRunningMean(double* measurements, double* weightedRunningMean, int numInRunningMean); 

int main()
{
    int triesFile = 0;
    int triesMeas = 0;
    double *myMeasurements = NULL;
    double *myRunningMean = NULL;
    char filename[256];
    int numMeas = 0;

    while(triesfile < 3)
    {
        printf("Enter the name of the input file: ");
        scanf("%255s", filename);

        FILE *file = fopen(filename, "r");
        if(file == NULL) 
        {
            printf("ERROR: Input file %s not opened", filename);
            triesFile++;

            if(triesFile == 3) 
            {
                printf("ERROR: too many failures opening input file");
                return 0;
            }
        }
  
        else
        {
            while(triesMeas < 3)
            printf("Enter the number of measurements: ");
            scanf("%d", numMeas);

            if(numMeas < 0 || 40 < numMeas)
            {
                printf("ERROR: numMeas is out of range \n\
       enter 0<numMeas<=40");
                triesMeas++;

                if(triesFile == 3) 
                {
                    printf("ERROR: too many failures reading the number of measurements");
                    return 0;
                }
            }

            else
            {
                int firstChar = fgetc(file);

                if(firstChar == EOF) 
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
                    
                }
        }
    }
}

void WeightedRunningMean()
{

}
