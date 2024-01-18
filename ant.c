#include <stdlib.h>
#include <wchar.h>
#include <stdio.h>
#include <locale.h>
#include "ant.h"
#include <string.h>

board init_board(int m, int n, int k) {
	board b = malloc(sizeof(*b));
	if (b == NULL)
		return NULL;
	b->m = m;
	b->n = n;
	b->kier = k;
	b->w = m / 2;
	b->k = n / 2;
	int i, j;
	b->board = malloc(sizeof(*(b->board)) * m);
	if (b->board == NULL) {
		free(b);
		return NULL;
	}
	for (i = 0; i < m; i++) {
		b->board[i] = calloc(n, sizeof(int));
		if (b->board[i] == NULL) {
			for (j = 0; j < i; j++)
				free(b->board[j]);
			return NULL;
		}
	}
	return b;
}

void free_board(board b) {
	int i;
	for (i = 0; i < b->m; i++)
		free(b->board[i]);
	free(b->board);
	free(b);
}

int int_digits( int n ) {
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    return 10;
}

void file_out( board b, char *name, int file_no, int digits )
{
        char buffor[ strlen(name) + 1 + digits ];
        sprintf( buffor, "%s_%0*d", name, digits, file_no );
	FILE *f = fopen( buffor, "w" );
	int i;
	//tu wypisanie do pliku
	fclose(f);
}

board langton( board b, int n, char *name )
{
	int digits = int_digits(n);
	int i = 0;
	//for( i = 0; i < n; i++ )
}

wchar_t* symbol(board b, int k, int w) {
	if (b->board[k][w] == 0) {
		switch (b->kier) {
			case 0:
				return L"△";
			case 1:
				return L"▷";
			case 2:
				return L"▽";
			case 3:
				return L"◁";
		}
	}
	else {
		switch (b->kier) {
			case 0:
				return L"▲";
			case 1:
				return L"▶";
			case 2:
				return L"▼";
			case 3:
				return L"◀";
		}
	}
}

void print_board(board b, FILE * stream) {
	int i, j;
	setlocale(LC_ALL, "C.UTF-8");
	if (stream == stdout)
		printf("\033[0;30;47m\n");
	fprintf(stream, "┌");
	for (i = 0; i < b->n; i++)
		fprintf(stream, "─");
	fprintf(stream, "┐\n");
	for (i = 0; i < b->m; i++) {
		fprintf(stream, "|");
		for (j = 0; j < b->n; j++) {
			if (b->k == j && b->w == i) {
				fprintf(stream, "%ls", symbol(b, j, i));
			}
			else {
				if (b->board[i][j] == 0)
					fprintf(stream, " ");
				else
					fprintf(stream, "█");
			}
		}
		fprintf(stream, "|\n");
	}
	fprintf(stream, "└");
	for (i = 0; i < b->n ; i++)
		fprintf(stream, "─");
	fprintf(stream, "┘");
	if (stream == stdout)
		printf("\033[0m\n");
}
