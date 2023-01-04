#include <stdio.h>
#include "chess.h"

#define size 15
#define Player1 1
#define Player2 2

int chessBoard[size + 1][size + 1] = {0};
int turn = 0;

int getNextPlayer(){
	if(turn%2 == 0){
		return Player1;
	}
	else{
		return Player2;
	}
}

void takeTurn(int row, int col){
	int winner;

	if(chessBoard[row][col] == 0 & row >= 1 & col >= 1 & row <= size & col <= size){
		if(turn % 2 == 0){
			chessBoard[row][col] = Player1;
			turn++;	
		}
		else{
			chessBoard[row][col] = Player2;
			turn++;
		}
	}
	else{
		printf("Not empty, retry/n");
	}
	
}

int horizonalWin(int i, int j){
	int count = 0;
	int left = j;
	int right = j;

	if(chessBoard[i][j] != 0){
		while(left >=1 & chessBoard[i][left] == chessBoard[i][j]){
			count++;
			left--;
		}
		while(right <= size & chessBoard[i][right] == chessBoard[i][j]){
			count++;
			right++;
		}
	}
	if(count > 5){
		return 1;
	}
	return 0;
}

int verticalWin(int i, int j){
	int up = i;
	int down = i;
	int count = 0;
	
	if(chessBoard[i][j] != 0){
                while(up >=1 & chessBoard[up][j] == chessBoard[i][j]){
                        count++;
                        up--;
                }
                while(down <= size & chessBoard[down][j] == chessBoard[i][j]){
                        count++;
                        down++;
                }
        }
        if(count > 5){
                return 1;
        }
        return 0;

}

int diagonalWin1(int i, int j){
	int up = i;
    	int right = j;
    	int down = i;
    	int left = j;
    	int count = 0;
    	
    	if(chessBoard[i][j] != 0) {
    		while(left >= 1 & up >= 1 & chessBoard[up][left] == chessBoard[i][j]) {
    			count++;
    			left--;
    			up--;
    		}
    		while(down <= size & right <= size & chessBoard[down][right] == chessBoard[i][j]) {
                        count++;
                        right++;
                        down++;
                }

    	}
    	if(count > 5) {
    		return 1;
    	}
    	return 0;
}

int diagonalWin2(int i, int j){
        int up = i;
        int right = j;
        int down = i;
        int left = j;
        int count = 0;

        if(chessBoard[i][j] != 0) {
                while(left >= 1 & down <= size & chessBoard[down][left] == chessBoard[i][j]) {
                        count++;
                        left--;
                        down++;
                }
                while(up >= 1 & right <= size & chessBoard[up][right] == chessBoard[i][j]) {
                        count++;
                        right++;
                        up--;
                }

        }
        if(count > 5) {
                return 1;
        }
        return 0;
    
}

int hasWon(int i, int j){
	if(horizonalWin(i, j) || verticalWin(i, j) || diagonalWin1(i, j) || diagonalWin2(i, j) == 1){
		return 1;
	}
	return 0;
}

void printChessBoard(){

	int i, j;

	for (i = 0; i <= size; i++)
	{
		for (j = 0; j <= size; j++)
		{
			if (i == 0){
				printf("%2d", j);
			}

			else if (j == 0){
				printf("%2d", i);
			}

			else if (1 == chessBoard[i][j])
				printf("● ");
			else if (2 == chessBoard[i][j])
				printf("○ ");
			else{
				if(i%2 != j%2){
					printf("  ");
				}
				else{
					printf("░░");
				}

			}
		}
		printf("\n");
	}
}

void initBoard(){
	for(int i = 0; i <= size; i++){
		for(int j = 0; j <= size; j++){
			chessBoard[i][j] = 0;
		}
	}
	turn = 0;
}

void *startGame(){
	initBoard();
	int won = 0;
	int winner;
	int row, col;
	
	while(won == 0){
		printChessBoard();
		printf("Player %d  please take step, input row number and column number\r\n", getNextPlayer());
		scanf("%d %d", &row, &col);
		takeTurn(row, col);
		won = hasWon(row, col);
	}
	if(getNextPlayer() == Player1){
		winner = Player2;
	}
	else{
		winner = Player1;
	}
	printf("Congratulations, player %d has won!!!\r\n", winner);
	printChessBoard();
}
