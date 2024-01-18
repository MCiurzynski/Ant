#ifndef ANT_H
#define ANT_H

typedef struct ant_board {
	int m;
	int n;
	int kier;
	int y;
	int x;
	int **board;
} *board;

board init_board(int, int, int);

void free_board(board);

void print_board(board);

#endif
