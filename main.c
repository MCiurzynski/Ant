#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "ant.h"

int main(int argc, char **argv) {
	param p = getparam(argc, argv);
	board b;
	if (p == NULL)
		return 2;
	if (p->generuj != 0) {
		generuj(p->m, p->n, p->generuj, p->name);
		return 0;
	}
	if (p->wczytaj == NULL)
		b = init_board(p->m, p->n, p->k);
	if (p->wczytaj != NULL)
		b = wczytaj(p->wczytaj, p->k);
	if (b == NULL)
		return 1;
	int digits = int_digits(p->i);
	ant(b, p->i, p->name, digits);
	free_board(b);
	free(p);
	printf("Zakonczono program!\n");
	return 0;
}
