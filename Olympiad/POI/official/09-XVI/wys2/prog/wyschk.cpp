/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wyspa (WYS)                                               *
 *   Plik:     wyschk.cpp                                                *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Sprawdzarka poprawnosci wyjsc.                            *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>

#define REP(a,n) for (int a=0; a<(n); ++a)
#define FOR(a,b,c) for (int a=(b); a<=(c); ++a)

using namespace std;

void error(const char *str)
{
	printf("WRONG (line 1): %s\n", str);
	exit(1);
}

int main(int argc, char **argv)
{
	if (argc!=4)
	{
		fprintf(stderr, "Potrzebujê trzech argumentów!!!\n");
		return -1;
	}
	FILE *fin = fopen(argv[1], "r");
	FILE *foutgr = fopen(argv[2], "r");
	FILE *foutok = fopen(argv[3], "r");
	if (fin==NULL || foutgr==NULL || foutok==NULL)
	{
		fprintf(stderr, "Nie umiem otworzyæ plików!!!\n");
		return -2;
	}
	double wyn_ok, wyn_gr;
	fscanf(foutok, "%lf", &wyn_ok);
	int ile = fscanf(foutgr, "%lf ", &wyn_gr);
	if (ile<1)
		error("Brak liczby");
	ile = fscanf(foutgr, "%*c"); // zwraca -1 jak koniec pliku, wpp. 0 (wczesniej wczytalismy spacje i \n)
	if (ile>=0)
		error("Smieci na koncu pliku");
	if (fabs(wyn_ok-wyn_gr)>=0.00001)
		error("Nieprawidlowy wynik");
	printf("OK\n");
}
