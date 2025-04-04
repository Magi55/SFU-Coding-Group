#include <stdio.h>
#define MAX_TRIES 3

void printARow(int startColNum, const int numOfRow);
void printPattern(int startColNum, const int numRows); 

int main() 
{
    int startColNum = 0;
    int numRows = 0;
    int tries = 0;

    while(tries < MAX_TRIES) 
    {
        printf("Enter the number of rows: ");
        scanf("%d", &numRows);

        if(numRows < 1 || 12 < numRows) 
        {
            printf("ERROR: The number of rows out of range\n 1 <= number of rows <= 12\n");
            tries++;

            if(tries == MAX_TRIES)
            {
                printf("ERROR: Too many tries, attempting to read the number of rows for the pattern.\n");
                return 0;
            }
        } 
        
        else 
        {
            startColNum = (numRows + 1) / 2;
            printPattern(startColNum, numRows);
            return 0;
        }
    }

    return 0;
}

void printARow(int startColNum, const int numOfRow) 
{
    int numOfElements = numOfRow - startColNum + 1;
    int leadingSpaces = (startColNum - 1) * 4;
    
    for(int i = 0; i < leadingSpaces; i++) 
    {
        printf(" ");
    }

    int num = startColNum;
    for(int i = 0; i < numOfElements; i++) 
    {
        printf("%4d", num);
        num += startColNum + i + 1;
    }
    printf("\n");
}

void printPattern(int startColNum, const int numRows) 
{
    if(startColNum < 1) 
    {
        return 0;
    }

    printARow(startColNum, numRows);
    printPattern(startColNum - 1, numRows);

    if(!(startColNum == 1 && numRows % 2 != 0)) 
    {
        printARow(startColNum, numRows);
    }
}
