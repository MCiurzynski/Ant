#include <stdlib.h>
#include <stdio.h>
#include "ant.h"
#include <string.h>

board init_board(int m, int n, int k) {
	board b = malloc(sizeof(*b));
	if (b == NULL)
		return NULL;
	b->m = m;
	b->n = n;
	b->kier = k;
	b->y = m / 2;
	b->x = n / 2;
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

void print_board( board b )
{
	int i, j;
	for( i = 0; i < b->m; i++ ){
		for( j = 0; j < b->n; j++ ){
			printf("%d ", b->board[i][j]);
		}
		printf("\n");
	}
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
