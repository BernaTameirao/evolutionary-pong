#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "Pong.h"

/*typedef struct{

    int HEIGHT, WIDTH;
    int ballX, ballY;
    int paddle1Y, paddle2Y;
    int ballDirectionX, ballDirectionY;
    int scorePaddle1, scorePaddle2;

} gameValues;*/

void initializeGame(gameValues *pongValues) {
    // Set initial positions and directions
    pongValues->ballX = pongValues->WIDTH / 2;
    pongValues->ballY = pongValues->HEIGHT / 2;
    pongValues->paddle1Y = pongValues->HEIGHT / 2 - 2;
    pongValues->paddle2Y = pongValues->HEIGHT / 2 - 2;



    pongValues->ballDirectionX = -1;

    pongValues->ballDirectionY = 1;
}

void drawGame(gameValues *pongValues) {

    system("clear"); // For Linux/Unix
    //system("cls"); // For Windows

    // Draw top border
    for (int i = 0; i < pongValues->WIDTH; i++) {
        printf("-");
    }
    printf("\n");

    // Draw the game
    for (int i = 0; i < pongValues->HEIGHT; i++) {
        for (int j = 0; j < pongValues->WIDTH; j++) {
            // Draw paddles
            if ((j == 1 && i >= pongValues->paddle1Y-2 && i < pongValues->paddle1Y + 2) || (j == pongValues->WIDTH - 1 && i >= pongValues->paddle2Y-2 && i < pongValues->paddle2Y + 2)) {
                printf("#");
            } else if (j == pongValues->ballX && i == pongValues->ballY) { // Draw ball
                printf("O");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    // Draw bottom border
    printf(" ");
    for (int i = 0; i < pongValues->WIDTH; i++) {
        printf("-");
    }
    printf("\n");

}

void updateGame(gameValues *pongValues) {
    // Update ball position

    int aux = pongValues->ballDirectionY;

    pongValues->ballX += pongValues->ballDirectionX;
    pongValues->ballY += pongValues->ballDirectionY;

    // Check for collisions with paddles
    if(pongValues->ballX == 1 && pongValues->ballY >= pongValues->paddle1Y-2 && pongValues->ballY < pongValues->paddle1Y + 2){

        pongValues->scorePaddle1 += 1;
        pongValues->ballDirectionX = -pongValues->ballDirectionX;
    }

    if(pongValues->ballX == pongValues->WIDTH - 2 && pongValues->ballY >= pongValues->paddle2Y-2 && pongValues->ballY < pongValues->paddle2Y + 2){

        pongValues->ballDirectionX = -pongValues->ballDirectionX;
    }

    if ((pongValues->ballX == 1 && pongValues->ballY == pongValues->paddle1Y-2)||(pongValues->ballX == pongValues->WIDTH - 2 && pongValues->ballY == pongValues->paddle2Y-2)){

        switch(aux){

            case 0:
                pongValues->ballDirectionY = -1;
                break;

            case 1:
                pongValues->ballDirectionY = 0;
                break;

            case -1:
                pongValues->ballDirectionY = 0;
                break;
        }
    }

    if ((pongValues->ballX == 1 && pongValues->ballY == pongValues->paddle1Y+2)||(pongValues->ballX == pongValues->WIDTH - 2 && pongValues->ballY == pongValues->paddle2Y+2)){

        switch(aux){

            case 0:
                pongValues->ballDirectionY = 1;
                break;

            case 1:
                pongValues->ballDirectionY = 0;
                break;

            case -1:
                pongValues->ballDirectionY = 0;
                break;
        }
    }

    // Check for collisions with top and bottom walls
    if (pongValues->ballY == 0 || pongValues->ballY == pongValues->HEIGHT - 1) {
        pongValues->ballDirectionY = -pongValues->ballDirectionY;
    }

    // Check for scoring
    if (pongValues->ballX == 0) {

        //pongValues->scorePaddle1 -= 1;
        initializeGame(pongValues); // Reset the game

    } else if (pongValues->ballX == pongValues->WIDTH - 1){

        //pongValues->scorePaddle2 -= 1;
        initializeGame(pongValues); // Reset the game
    }
}

void updateGameEvolutive(gameValues *pongValues) {
    // Update ball position

    int aux = pongValues->ballDirectionY;

    pongValues->ballX += pongValues->ballDirectionX;
    pongValues->ballY += pongValues->ballDirectionY;

    // Check for collisions with paddles
    if(pongValues->ballX == 1 && pongValues->ballY >= pongValues->paddle1Y-2 && pongValues->ballY < pongValues->paddle1Y + 2){

        pongValues->scorePaddle1 += 1;
        initializeGame(pongValues);
    }

    // Check for collisions with top and bottom walls
    if (pongValues->ballY == 0 || pongValues->ballY == pongValues->HEIGHT - 1) {
        pongValues->ballDirectionY = -pongValues->ballDirectionY;
    }

    // Check for scoring
    if (pongValues->ballX == 0) {

        //pongValues->scorePaddle1 -= 1;
        initializeGame(pongValues); // Reset the game

    } else if (pongValues->ballX == pongValues->WIDTH - 1){

        //pongValues->scorePaddle2 -= 1;
        initializeGame(pongValues); // Reset the game
    }
}



/*int main() {

    char input;
    gameValues pongValues;

    srand(time(NULL));

    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    getmaxyx(stdscr, pongValues.HEIGHT, pongValues.WIDTH);
    pongValues.HEIGHT /= 3;

    initializeGame(&pongValues);

    while (1) {
        getmaxyx(stdscr, pongValues.HEIGHT, pongValues.WIDTH);
        pongValues.HEIGHT /= 3;
        drawGame(&pongValues);
        updateGame(&pongValues);

        input = wgetch(stdscr);

            // Update paddle positions
        switch (input) {
            case 'w':
                pongValues.paddle1Y = (pongValues.paddle1Y > 0) ? pongValues.paddle1Y - 1 : pongValues.paddle1Y;
                break;
            case 's':
                pongValues.paddle1Y = (pongValues.paddle1Y < pongValues.HEIGHT - 4) ? pongValues.paddle1Y + 1 : pongValues.paddle1Y;
                break;
            case 'q':
                exit(0);
        }

        usleep(18400); // Sleep for 100 milliseconds (adjust as needed)
    }

    endwin();

    return 0;
}*/
