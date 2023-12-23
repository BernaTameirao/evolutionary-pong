#ifndef ESYSTEM_H
#define ESYSTEM_H

typedef struct{

    int *geneReaction;
    int *geneSpeed;

} geneStruct;

geneStruct *createPopulation(int numPopulation);
void newGeneration(geneStruct *oldPopulation, geneStruct bestStats, int numPopulation);
void genocide(geneStruct *oldPopulation, int numPopulation);

#endif