#include <stdio.h>
#include <stdlib.h>

#include "Extras.h"

float mean(int *numberArray, int size){

    float mean=0;

    for(int counter=0; counter<size; counter++){

        mean += numberArray[counter];
    }

    mean /= size;

    return mean;
}

void getInput(int argc, char *argv[], int *numGeneration, int *numPopulation){

    if(argc > 2){

        *numGeneration = atoi(argv[0]);
        *numPopulation = atoi(argv[1]);

    } else {

        printf("How many generations?\n");
        scanf("%i", numGeneration);

        printf("What is the size of the population?\n");
        scanf("%i", numPopulation);
    }
}