#ifndef ANT_H
#define ANT_H

typedef struct ant_board {
	int m;
	int n;
	int kier;
	int w;
	int k;
	int **board;
} *board;

board init_board(int, int, int);

void free_board(board);

wchar_t* symbol(board, int, int);

void print_board(board, FILE *, int, int);

int int_digits( int );

char *file_name( char* , int, int );

void langton( board, int, char* );

#endif
