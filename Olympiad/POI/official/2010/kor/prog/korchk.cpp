/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Korale (KOR)                                              *
 *   Plik:     korchk.cpp                                                *
 *   Autor:    Wojciech Tyczynski                                        *
 *   Opis:     Weryfikator wyjsc.                                        *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

#define PB push_back
#define MAX_W 200005

char buffer[1000];
int wynik,ile;
int odp_wyn,odp_ile;
int T[MAX_W];

void error (const char *str) {
	printf("WRONG (line 1): %s", str);
	exit(1);
}

int main(int argc, char **argv) {
	if (argc!=4) {
		fprintf (stderr, "Potrzebuje trzech argumentow!!!\n");
		return -1;
	}

	FILE *fin = fopen (argv[1], "r");
	FILE *foutzaw = fopen (argv[2], "r");
	FILE *foutok = fopen (argv[3], "r");
	if (fin==NULL || foutzaw==NULL || foutok==NULL) {
		fprintf (stderr, "Nie umiem otworzyc ktoregos pliku!!!\n");
		return -2;
	}

	fscanf (foutok, "%d %d", &odp_wyn, &odp_ile);	
	if (fscanf (foutzaw, "%d %d", &wynik, &ile)!=2) {
		sprintf (buffer, "Za krotki plik wyjsciowy\n");
		error (buffer);
	}

	if (odp_wyn != wynik) {
		sprintf (buffer, "Nieprawidlowa ilosc sznurkow: wczytano %d oczekiwano %d\n",wynik,odp_wyn);
		error (buffer);
	}
	
	if (odp_ile != ile) {
		sprintf (buffer, "Nieprawidlowa ilosc wyborow: wczytano %d oczekiwano %d\n",ile,odp_ile);
		error (buffer);
	}

	for(int i=0; i<ile; i++)
		if (fscanf (foutzaw, "%d", &T[i]) != 1) {
			sprintf (buffer, "Wczytano eoln, oczekiwano liczby\n");
			error (buffer);
		}
	sort(T,T+ile);

	int x,y;
	for(int i=0; i<ile; i++) {
		fscanf (foutok, "%d", &x);
		y=T[i];
		if (x!=y) {
			sprintf (buffer, "Nieprawidlowa wartosc %d-tego parametru k: wczytano %d oczekiwano %d\n",i+1,y,x);
			error (buffer);
		}
	}

	if (fscanf (foutzaw,"%d", &x) == 1) {
		sprintf (buffer, "Wczytano %d, oczekiwano eoln\n",x);
		error (buffer);
	}
	
	printf("OK\n");
	return 0;
}
