#ifndef _CHESS_H
#define _CHESS_H

#define size 15
#define Player1 1
#define Player2 2

extern void printChessboard();
extern int hasWon(int, int);
extern void initBoard();
extern void *startGame();
extern int getNextPlayer();
extern void takeTurn(int, int);

#endif
