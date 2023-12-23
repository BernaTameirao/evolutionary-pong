#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
#include <omp.h>

#include "Pong.h"
#include "EvolutiveSystem.h"
#include "Extras.h"

#define numIteraction 20000

int main(int argc, char *argv[]){

    srand(time(NULL));

    int numPopulation, numGeneration;
    int bestScoreAuxNow=-1, bestScoreAuxBefore=-1, numIteractionNoChange=0;

    getInput(argc, argv, &numGeneration, &numPopulation);

    gameValues pongValues;

    geneStruct *genes = createPopulation(numPopulation);
    geneStruct bestGene;

    bestGene.geneReaction = malloc(5*sizeof(int));
    bestGene.geneSpeed = malloc(5*sizeof(int));
    
    FILE* f = fopen("score.txt", "w");

    //int *bestScore = malloc(numGeneration*sizeof(int));

    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    for(int counter1=0; counter1<numGeneration; counter1++){

        #pragma omp parallel for default(shared) private(counter2, pongValues)
        for(int counter2=0; counter2<numPopulation; counter2+=1){

            getmaxyx(stdscr, pongValues.HEIGHT, pongValues.WIDTH);
            pongValues.HEIGHT /= 3;


            int speed1 = (int)abs(mean(genes[counter2].geneSpeed, 5));
            int speed2 = 1;

            int reaction1Aux = (int)abs(mean(genes[counter2].geneReaction, 5));
            int reaction2Aux = 1;

            reaction1Aux = (reaction1Aux == 0) ? 1 : reaction1Aux;

            initializeGame(&pongValues);


            for(int counter3=0; counter3<numIteraction; counter3++){

                //getmaxyx(stdscr, pongValues.HEIGHT, pongValues.WIDTH);
                //pongValues.HEIGHT /= 3;
                    
                updateGameEvolutive(&pongValues);

                
                if(counter3%reaction1Aux == 0){

                    if(pongValues.ballY < pongValues.paddle1Y){

                        pongValues.paddle1Y = (pongValues.paddle1Y > speed1+2) ? pongValues.paddle1Y - speed1 : 2;

                    } else if (pongValues.ballY > pongValues.paddle1Y) {

                        pongValues.paddle1Y = (pongValues.paddle1Y < pongValues.HEIGHT - (2+speed1)) ? pongValues.paddle1Y + speed1 : pongValues.HEIGHT - 2;
                    }
                }

                if(counter3%reaction2Aux == 0){

                    if(pongValues.ballY < pongValues.paddle2Y){

                        pongValues.paddle2Y = (pongValues.paddle2Y > speed2+2) ? pongValues.paddle2Y - speed2 : 2;

                    } else if (pongValues.ballY > pongValues.paddle2Y) {

                        pongValues.paddle2Y = (pongValues.paddle2Y < pongValues.HEIGHT - (2+speed2)) ? pongValues.paddle2Y + speed2 : pongValues.HEIGHT - 2;
                    }
                }
            }


            if(bestScoreAuxNow < pongValues.scorePaddle1){

                bestScoreAuxNow = pongValues.scorePaddle1;

                for(int counter3=0; counter3<5; counter3++){
                    
                    bestGene.geneReaction[counter3] = genes[counter2].geneReaction[counter3];
                    bestGene.geneSpeed[counter3] = genes[counter2].geneSpeed[counter3];
                }
            }

            pongValues.scorePaddle1 = 0;
        }

        //bestScore[counter1] = bestScoreAuxNow;

        //
        fprintf(f, "%i ", bestScoreAuxNow);
        fprintf(f, "|%i %i|\n", (int)abs(mean(bestGene.geneReaction, 5)), (int)abs(mean(bestGene.geneSpeed, 5)));
        //

        if(bestScoreAuxNow > 0){

            /*if(bestScoreAuxNow==bestScoreAuxBefore){

                numIteractionNoChange += 1;
            } else {

                numIteractionNoChange = 0;
            }

            if(numIteractionNoChange == 10){

                numIteractionNoChange = 0;
                bestScoreAuxNow = -1;
                genocide(genes, numPopulation);
                fprintf(f, "G\n");
            } else {*/

                newGeneration(genes, bestGene, numPopulation);
            //}

        } else {

            bestScoreAuxNow = -1;
            genocide(genes, numPopulation);
            //fprintf(f, "G\n");
        }

        bestScoreAuxBefore = bestScoreAuxNow;
    }

    fclose(f);

    char input;
    int speed = (int)abs(mean(bestGene.geneSpeed, 5));
    int reactionAux = (int)abs(mean(bestGene.geneReaction, 5));

    int speedPlayer = 1;
    int reactionPlayer = 1;

    reactionAux = (reactionAux == 0) ? 1 : reactionAux;

    initializeGame(&pongValues);

    for(int counter=0; ; counter++) {
        getmaxyx(stdscr, pongValues.HEIGHT, pongValues.WIDTH);
        pongValues.HEIGHT /= 3;
        drawGame(&pongValues);
        updateGame(&pongValues);

        input = wgetch(stdscr);

            // Update paddle positions
        switch (input) {
            case 'w':
                pongValues.paddle1Y = (pongValues.paddle1Y > 2+speedPlayer) ? pongValues.paddle1Y - speedPlayer : 2;
                break;
            case 's':
                pongValues.paddle1Y = (pongValues.paddle1Y < pongValues.HEIGHT - (2+speedPlayer)) ? pongValues.paddle1Y + speedPlayer : pongValues.HEIGHT - 2;
                break;
            case 'q':

                for(int counter=0; counter<numPopulation; counter++){

                    free(genes[counter].geneReaction);
                    free(genes[counter].geneSpeed);
                }
                free(genes);
                //free(bestScore);
                free(bestGene.geneReaction);
                free(bestGene.geneSpeed);


                endwin();
                exit(0);
                break;
        }
        
        if(counter%reactionAux == 0){

            if(pongValues.ballY < pongValues.paddle2Y){

                pongValues.paddle2Y = (pongValues.paddle2Y > speed+2) ? pongValues.paddle2Y - speed : 2;

            } else if (pongValues.ballY > pongValues.paddle2Y){

                pongValues.paddle2Y = (pongValues.paddle2Y < pongValues.HEIGHT - (2+speed) ) ? pongValues.paddle2Y + speed : pongValues.HEIGHT - 2;
            }
        }

        usleep(18400);
    }

    for(int counter=0; counter<numPopulation; counter++){

        free(genes[counter].geneReaction);
        free(genes[counter].geneSpeed);
    }
    free(genes);
    //free(bestScore);
    free(bestGene.geneReaction);
    free(bestGene.geneSpeed);

    endwin();

    return 0;
}