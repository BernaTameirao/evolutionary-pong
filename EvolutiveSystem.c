#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "EvolutiveSystem.h"

#define MAX 20

/*typedef struct{

    int *geneReaction;
    int *geneSpeed;

} geneStruct;*/

geneStruct *createPopulation(int numPopulation){

    geneStruct *genes = malloc(numPopulation*sizeof(geneStruct));

    for(int counter=0; counter<numPopulation; counter++){

        genes[counter].geneReaction = malloc(5*sizeof(int));
        genes[counter].geneSpeed = malloc(5*sizeof(int));

        for(int otherCounter=0; otherCounter<5; otherCounter++){

            genes[counter].geneReaction[otherCounter] = rand()%MAX;
            usleep(1);
            genes[counter].geneSpeed[otherCounter] = rand()%MAX;
            usleep(1);
        }
    }

    /*genes[0].geneReaction[0] = 1;
    genes[0].geneSpeed[0] = 1;

    genes[0].geneReaction[1] = 1;
    genes[0].geneSpeed[1] = 1;

    genes[0].geneReaction[2] = 1;
    genes[0].geneSpeed[2] = 1;

    genes[0].geneReaction[3] = 1;
    genes[0].geneSpeed[3] = 1;

    genes[0].geneReaction[4] = 1;
    genes[0].geneSpeed[4] = 1;*/

    return genes;
}

void newGeneration(geneStruct *oldPopulation, geneStruct bestStats, int numPopulation){

    for(int counter=0; counter<numPopulation; counter++){

        //Reproduction

        for(int otherCounter=0; otherCounter<5; otherCounter++){

            oldPopulation[counter].geneReaction[otherCounter] = (oldPopulation[counter].geneReaction[otherCounter] + bestStats.geneReaction[otherCounter])/2;
            oldPopulation[counter].geneSpeed[otherCounter] = (oldPopulation[counter].geneSpeed[otherCounter] + bestStats.geneSpeed[otherCounter])/2;
        }

        //Mutation

        if(rand()%20 == 0){
            
            int aux = rand()%10;

            if(aux<5){

                oldPopulation[counter].geneReaction[aux] += rand()%11 - 5;
            } else {

                oldPopulation[counter].geneSpeed[aux-5] += rand()%11 - 5;
            }
        }
    }
}

void genocide(geneStruct *oldPopulation, int numPopulation){

    for(int counter=0; counter<numPopulation; counter++){

        for(int otherCounter=0; otherCounter<5; otherCounter++){

            oldPopulation[counter].geneReaction[otherCounter] = rand()%MAX;
            usleep(1);
            oldPopulation[counter].geneSpeed[otherCounter] = rand()%MAX;
            usleep(1);
        }
    }
}