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

typedef struct parametrs {
	int m;
	int n;
	int i;
	int k;
	int generuj;
	char *wczytaj;
	char *name;
} *param;

void generuj(int, int, int, char*);

board wczytaj(char*, int);

param getparam(int, char**);

board init_board(int, int, int);

void free_board(board);

wchar_t* symbol(board, int, int);

void fprint_board(FILE *, board, int);

void move(board);

void ant(board, int, char *);

#endif
