#include <stdlib.h>
#include <wchar.h>
#include <stdio.h>
#include <locale.h>
#include "ant.h"

/*param getparam(int argc, char** argv) {
	param p = malloc(sizeof(*p));
	p->m = -1;
	p->n = -1;
	p->i = -1;
	p->k = -1;
	p->end = 0;
	p->name = NULL;
} */

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

wchar_t* symbol(board b, int k, int w) {
	if (b->board[w][k] == 0) {
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

void fprint_board(FILE * stream, board b, int x) {
	int i, j;
	setlocale(LC_ALL, "C.UTF-8");
	if (stream == stdout)
		printf("\033[0;30;47m\n");
	fprintf(stream, "%d:\n", x);
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

void move(board b) {
	if (b->board[b->w][b->k] == 0) {
		b->kier++;
		if (b->kier == 4)
			b->kier = 0;
		b->board[b->w][b->k] = 1;
	}
	else {
		b->kier--;
		if (b->kier == -1)
			b->kier = 3;
		b->board[b->w][b->k] = 0;
	}
	switch (b->kier) {
		case 0:
			if (b->w == 0)
				b->w = b->m - 1;
			else
				b->w--;
			break;
		case 1:
			if (b->k == b->n - 1)
				b->k = 0;
			else
				b->k++;
			break;
		case 2:
			if (b->w == b->m - 1)
				b->w = 0;
			else
				b->w++;
			break;
		case 3:
			if (b->k == 0)
				b->k = b->n - 1;
			else
				b->k--;
			break;
	}
}

void ant(board b, int i, char* name) {
	int j;
	char file[100];
	FILE* f;
	if (name == NULL)
		f = stdout;
	for (j = 0; j < i; j++) {
		if (name != NULL) {
			sprintf(file, "./boards/%s_%d", name, j);
			f = fopen(file, "w");
			if (f == NULL) {
				fprintf(stderr, "Nie udalo sie otworzyc pliku %s\n", file);
				exit(5);
			}
		}
		fprint_board(f, b, j);
		if (name != NULL)
			fclose(f);
		move(b);
	}
}
