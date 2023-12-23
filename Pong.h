#ifndef PONG_H
#define PONG_H

typedef struct{

    int HEIGHT, WIDTH;
    int ballX, ballY;
    int paddle1Y, paddle2Y;
    int ballDirectionX, ballDirectionY;
    int scorePaddle1, scorePaddle2;

} gameValues;

void initializeGame(gameValues *pongValues);
void drawGame(gameValues *pongValues);
void updateGame(gameValues *pongValues);
void updateGameEvolutive(gameValues *pongValues);

#endif