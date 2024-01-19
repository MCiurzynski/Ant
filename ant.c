#include <stdlib.h>
#include <wchar.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "ant.h"

void generuj(int m, int n, int prop, char* name) {
	FILE * f = fopen(name, "w");
	int i, j, los;
	srand(time(NULL));
	if (f == NULL) {
		fprintf(stderr, "Nie udalo sie otworzyc pliku\n");
		return;
	}
	fprintf(f, "%d %d\n", m, n);
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			los = rand() % 100;
			if (los < prop)
				fprintf(f, "1");
			else
				fprintf(f, "0");
		}
		fprintf(f, "\n");
	}
	printf("Wygenerowano plansze\n");
}

board wczytaj(char* name, int k) {
	FILE * f;
	int i, j, m, n;
	f = fopen(name, "r");
	if (f == NULL) {
		fprintf(stderr, "Nie udalo sie wgrac planszy\n");
		return NULL;
	}
	fscanf(f, "%d %d", &m, &n);
	board b = init_board(m, n, k);
	if (b == NULL) {
		fprintf(stderr, "Nie udalo sie wgrac planszy\n");
		fclose(f);
		return NULL;
	}
	b->m = m;
	b->n = n;
	fgetc(f);
	for (i = 0; i < b->m; i++) {
		for (j = 0; j < b->n; j++) {
			b->board[i][j] = fgetc(f) - '0';
		}
		fgetc(f);
	}
	return b;
}

param getparam(int argc, char** argv) {
	param p = malloc(sizeof(*p));
	p->m = -1;
	p->n = -1;
	p->i = -1;
	p->k = -1;
	p->s = -1;
	p->generuj = 0;
	p->wczytaj = NULL;
	int opt, end = 0;
	p->name = NULL;
	while ((opt = getopt(argc, argv, ":-:n:m:i:p:k:g:w:s:")) != -1) {
		switch (opt) {
			case '-':
				if (strcmp("name", optarg) == 0) {
					if (optind == argc || argv[optind][0] == '-') {
						fprintf(stderr, "Nie wprowadzono parametru '--name'\n");
						return NULL;
					}
					else
						p->name = argv[optind];
				}
				else {
					fprintf(stderr, "Nieznana opcja: '--%s'\n", optarg);
					return NULL;
				}
				break;
			case 'm':
				if (optarg[0] == '-') {
					fprintf(stderr, "Parametr 'm' jest wymagany\n");
					return NULL;
				}
				p->m = atoi(optarg);
				break;
			case 'n':
				if (optarg[0] == '-') {
					fprintf(stderr, "Parametr 'n' jest wymagany\n");
					return NULL;
				}
				p->n = atoi(optarg);
				break;
			case 'i':
				if (optarg[0] == '-') {
					fprintf(stderr, "Parametr 'i' jest wymagany\n");
					return NULL;
				}
				p->i = atoi(optarg);
				break;
			case 'k':
				if (optarg[0] == '0' && strlen(optarg) == 1)
					p->k = 0;
				if (atoi(optarg) == 1)
					p->k = 1;
				if (atoi(optarg) == 2)
					p->k = 2;
				if (atoi(optarg) == 3)
					p->k = 3;
				if (optarg[0] == '-') {
					fprintf(stderr, "Parametr 'k' jest wymagany\n");
					return NULL;
				}
				if (p->k == -1) {
					fprintf(stderr, "Wprowadzono nieprawodlowy parametr 'k'\n");
					return NULL;
				}
				break;
			case 'g':
				if (optarg[0] == '-') {
					fprintf(stderr, "Parametr 'g' jest wymagany\n");
					return NULL;
				}
				p->generuj = atoi(optarg);
				if (p->generuj < 1 || p->generuj > 100) {
					fprintf(stderr, "Nieprawidlowy parametr g\n");
					return NULL;
				}
				break;
			case 'w':
				if (optarg[0] == '-') {
					fprintf(stderr, "Parametr 'w' jest wymagany\n");
					return NULL;
				}
				p->wczytaj = optarg;
				break;
			case 's':
				if (optarg[0] == '-') {
					fprintf(stderr, "Parametr 'p' jest wymagany\n");
				}
				p->s = atoi(optarg);
				break;
			case '?':
				fprintf(stderr, "Nieznana opcja: '-%c'\n", optopt);
				return NULL;
			case ':':
				fprintf(stderr, "Opcja %c jest wymagana\n", optopt);
				return NULL;
			default:
				fprintf(stderr, "Nie powinno cie tu byc\n");
				return NULL;
		}
	}
	if ((p->m < 2 || p->m > 512) && p->m != -1) {
		printf("Wprowadzono niepawidlowy parametr 'm'\n");
		end = 1;
	}
	if ((p->n < 2 || p->n > 512) && p->n != -1) {
		printf("Wprowadzono niepawidlowy parametr 'n'\n");
		end = 1;
	}
	if (p->i == 0 && p->generuj == 0) {
		printf("Wprowadzono niepawidlowy parametr 'i'\n");
		end = 1;
	}
	if (p->generuj != 0 && end == 0 && p->name != NULL) {
		if ( p->m != -1 && p->n != -1)
			return p;
	}
	if (p->generuj != 0 && p->name == NULL) {
		fprintf(stderr, "Nie wprowadzono wymaganego podczas generacji planszy parametru 'name'\n");
		end = 1;
	}
	if (p->wczytaj != NULL && p->i > 0 && p->k != -1) {
		return p;
	}
	if (p->m == -1 && p->wczytaj == NULL) {
		fprintf(stderr, "Nie wprowadzono wymaganego parametru m\n");
		end = 1;
	}
	if (p->n == -1 && p->wczytaj == NULL) {
		fprintf(stderr, "Nie wprowadzono wymaganego parametru n\n");
		end = 1;
	}
	if (p->i == -1 && p->generuj == 0) {
		fprintf(stderr, "Nie wprowadzono wymaganego parametru i\n");
		end = 1;
	}
	if (p->k == -1 && p->generuj == 0) {
		fprintf(stderr, "Nie wprowadzono wymaganego parametru k\n");
		end = 1;
	}
	if (end == 1)
		return NULL;
	return p;
}

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
	return 0;
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

void ant(board b, int i, char* name, int s) {
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
		if (s == 0 && ( j == i - 1 || j == 0))
			fprint_board(f, b, j);
		if (s == -1)
			fprint_board(f, b, j);
		if (s != 0 && s != -1) {
			if (j % s == 0 || j == i - 1)
				fprint_board(f, b, j);
		}
		if (name != NULL)
			fclose(f);
		move(b);
	}
}
