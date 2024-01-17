#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "ant.h"

int main(int argc, char **argv) {
	int opt, m = -1, n = -1, i = -1, k = -1;
	int end = 0;
	char *name = NULL;
	while ((opt = getopt(argc, argv, ":-:n:m:i:p:k:")) != -1) {
		switch (opt) {
			case '-':
				if (strcmp("name", optarg) == 0) {
					if (argv[optind][0] == '-') {
						fprintf(stderr, "Nie wprowadzono parametru '--name'\n");
						return 4;
					}
					else
						name = argv[optind];
				}
				else {
					fprintf(stderr, "Nieznana opcja: '--%s'\n", optarg);
					return 1;
				}
				break;
			case 'm':
				if (optarg[0] == '-') {
					fprintf(stderr, "Parametr 'm' jest wymagany\n");
					return 3;
				}
				m = atoi(optarg);
				break;
			case 'n':
				if (optarg[0] == '-') {
					fprintf(stderr, "Parametr 'n' jest wymagany\n");
					return 3;
				}
				n = atoi(optarg);
				break;
			case 'i':
				if (optarg[0] == '-') {
					fprintf(stderr, "Parametr 'i' jest wymagany\n");
					return 3;
				}
				i = atoi(optarg);
				break;
			case 'k':
				if (optarg[0] == '0')
					k = 0;
				if (optarg[0] == '1')
					k = 1;
				if (optarg[0] == '2')
					k = 2;
				if (optarg[0] == '3')
					k = 3;
				if (optarg[0] == '-') {
					fprintf(stderr, "Parametr 'k' jest wymagany\n");
					return 3;
				}
				if (k == -1) {
					fprintf(stderr, "Wprowadzono nieprawodlowy parametr 'k'\n");
					return 3;
				}
				break;
			case '?':
				fprintf(stderr, "Nieznana opcja: '-%c'\n", optopt);
				return 1;
			case ':':
				fprintf(stderr, "Opcja %c jest wymagana\n", optopt);
				return 1;
			default:
				printf("Nie powinno cie tu byc\n");
				return 2;
		}
	}
	if (m == -1) {
		fprintf(stderr, "Nie wprowadzono wymaganego parametru m\n");
		end = 1;
	}
	if (n == -1) {
		fprintf(stderr, "Nie wprowadzono wymaganego parametru n\n");
		end = 1;
	}
	if (i == -1) {
		fprintf(stderr, "Nie wprowadzono wymaganego parametru i\n");
		end = 1;
	}
	if (k == -1) {
		fprintf(stderr, "Nie wprowadzono wymaganego parametru k\n");
		end = 1;
	}
	if(m == 0 || m > 50) {
		printf("Wprowadzono niepawidlowy parametr 'm'\n");
		end = 1;
	}
	if(n == 0 || n > 50) {
		printf("Wprowadzono niepawidlowy parametr 'n'\n");
		end = 1;
	}
	if(i == 0) {
		printf("Wprowadzono niepawidlowy parametr 'i'\n");
		end = 1;
	}
	if (end == 1)
		return 3;
	board b = init_board(m, n, k);
	if (b != NULL)
		printf("Sukces\n");
	free_board(b);
	return 0;
}
