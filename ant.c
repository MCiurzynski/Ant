#include <stdlib.h>
#include <wchar.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "ant.h"

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

void generuj(int m, int n, int prop, char* name) {
	FILE * f = fopen(name, "w");
	int i, j, los;
	srand(time(NULL));
	if (f == NULL) {
		fprintf(stderr, "Nie udalo sie otworzyc pliku\n");
		return;
	}
	fprintf(f, "%dx%d\n\n", m, n);
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
	p->generuj = 0;
	p->wczytaj = NULL;
	int opt, end = 0;
	p->name = NULL;
	int *ile = malloc( 123 * sizeof(int) );
	if( ile == NULL ){
		printf("Blad alokacji pamieci!\n");
		return NULL;
	}

	while ((opt = getopt(argc, argv, ":-:n:m:i:p:k:g:w:")) != -1) {
		switch (opt) {
			case '-':
				if (strcmp("name", optarg) == 0) {
					ile['-']++;
					if( ile['-'] < 2 ){
						if ( optind == argc || argv[optind][0] == '-' ) {
							fprintf(stderr, "Argument nr %d: Nie wprowadzono wartosci parametru '--name'\n", optind - 1);
							end = 1;
							//return NULL;
						}
						else{
							p->name = argv[optind];
						}
					}
					if( ile['-'] == 2 ){
						printf("Wystepuja powtorzenia paramteru --name\n");
						end = 1;
					}
				}
				else {
					fprintf(stderr, "Nieznana opcja: '--%s'\n", optarg);
					end = 1;
					//return NULL;
				}
				break;
			case 'm':
				ile['m']++;
				if( ile['m'] < 2 ){
					if (optarg[0] == '-') {
						fprintf(stderr, "Argument nr %d: Podaj wartosc dla parametru -m\n", optind - 2);
						end = 1;
						p->m = 0;
						//return NULL;
					}
					else{
						p->m = atoi(optarg);
                                        	if ((p->m < 2 || p->m > 512) && p->m != -1) {
                                                	printf("Argument nr %d: Wprowadzono niepawidlowa wartosc parametru -m\n", optind - 2);
                                                	end = 1;
                                        	}
                                	}
				}
				if( ile['-'] == 2 ){
                                        printf("Wystepuja powtorzenia paramteru -m\n");
                                	end = 1;
                                }
				break;
			case 'n':
				ile['n']++;
				if( ile ['n'] < 2 ){
					if (optarg[0] == '-') {
						fprintf(stderr, "Argument nr %d: Podaj wartosc dla parametru n\n", optind - 2);
						end = 1;
						p->n = 0;
						//return NULL;
					}
					else{
						p->n = atoi(optarg);
						if ((p->n < 2 || p->n > 512) && p->n != -1) {
							printf("Argument nr %d: Wprowadzono niepawidlowa wartosc parametru -n\n", optind - 2);
                					end = 1;
        					}
					}
				}
				if( ile['n'] == 2 ){
					printf("Wystepuja powtorzenia parametru -n\n");
                                        end = 1;
                                }
				break;
			case 'i':
				ile['i']++;
				if( ile['i'] < 2 ){
					if (optarg[0] == '-') {
						fprintf(stderr, "Argument nr %d: Podaj wartosc dla parametru i\n", optind - 2);
						end = 1;
						p->i = 0;
						//return NULL;
					}
					else{
						p->i = atoi(optarg);
					}
				}
				if( ile['i'] == 2 ){
                                        printf("Wystepuja powtorzenia parametru -i\n");
                                        end = 1;
                                }
				break;
			case 'k':
				ile['k']++;
				if( ile['k'] < 2 ){
					if (optarg[0] == '-') {
                                        	fprintf(stderr, "Argument nr %d: Podaj wartosc dla parametru k\n", optind - 2);
                                        	end = 1;
						p->k = 0;
                                        	//return NULL;
                                	}
					else{
						if (optarg[0] == '0' && strlen(optarg) == 1)
							p->k = 0;
						if (atoi(optarg) == 1)
							p->k = 1;
						if (atoi(optarg) == 2)
							p->k = 2;
						if (atoi(optarg) == 3)
							p->k = 3;
						if (p->k == -1) {
        	                                	fprintf(stderr, "Argument nr %d: Wprowadzono nieprawidlowa wartosc parametru 'k'\n", optind - 2);
                	                        	end = 1;
							p->k = 0;
                                	        	//return NULL;
						}
                                	}
				}
				if( ile['k'] == 2 ){
					printf("Wystepuja powtorzenia parametru -k\n");
					end = 1;
				}
				break;
			case 'g':
				ile['g']++;
				if( ile['g'] < 2 ){
					if (optarg[0] == '-') {
						fprintf(stderr, "Argument nr %d: Podaj wartosc dla parametru -g\n", optind - 2);
						end = 1;
						//return NULL;
					}
					else{
						if (p->generuj < 1 || p->generuj > 100) {
							fprintf(stderr, "Argument nr %d: Nieprawidlowa wartosc parametru -g\n", optind - 2);
							end = 1;
							//return NULL;
						}
						else{
							p->generuj = atoi(optarg);
						}
					}
				}
				if( ile['g'] == 2 ){
					printf("Wystepuja powtorzenia parametru -g\n");
					end = 1;
				}
				break;
			case 'w':
				ile['w']++;
				if( ile['w'] < 2 ){
					if (optarg[0] == '-') {
						fprintf(stderr, "Argument nr %d: Podaj wartosc dla parametru -w\n", optind - 2);
						end = 1;
						//return NULL;
					}
					else{
						p->wczytaj = optarg;
					}
				break;
				}
				if( ile['w'] == 2 ){
					printf("Wystepuja powtorzenia parametru -w\n");
					end = 1;
				}
			case '?':
				fprintf(stderr, "Nieznana opcja: '-%c'\n", optopt);
				end = 1;
				//return NULL;
			case ':':
				if( ile[optopt] == 0 ){
					fprintf(stderr, "Podaj wartosc dla paramteru %c\n", optopt);
					end = 1;
				}
				//return NULL;
			//default:
				//fprintf(stderr, "Nie powinno cie tu byc\n");
				//return NULL;
		}
	}
	if (p->i == 0 && p->generuj == 0) {
		printf("Wprowadzono niepawidlowy parametr i\n");
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
	free(ile);
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

void fprint_board(FILE * stream, board b, int x, int digits ) {
	int i, j;
	setlocale(LC_ALL, "C.UTF-8");
	if (stream == stdout)
		printf("\033[0;30;47m\n");
	fprintf(stream, "#%0*d\n", digits, x);
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

void ant(board b, int i, char* name, int digits) {
	int j;
	FILE* f;
	int dlugosc;
	if (name == NULL){
		dlugosc = 0;
		f = stdout;
	}
	else{
		dlugosc = strlen(name);
	}
	char file[dlugosc + digits + 2];
	for (j = 0; j < i; j++) {
		if (name != NULL) {
			sprintf(file, "%s_%0*d", name, digits, j);
			f = fopen(file, "w");
			if (f == NULL) {
				fprintf(stderr, "Nie udalo sie otworzyc pliku %s\n", file);
				exit(5);
			}
		}
		fprint_board(f, b, j, digits);
		if (name != NULL)
			fclose(f);
		move(b);
	}
}
