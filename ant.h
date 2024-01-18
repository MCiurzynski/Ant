#ifndef ANT_H
#define ANT_H

typedef struct ant_board {
	int m;
	int n;
	int w;
	int k;
	int kier;
	int **board;
} *board;

board init_board(int, int, int);

void free_board(board);

wchar_t* symbol(board, int, int);

void print_board(board);

#endif
