/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Piorunochron                                     *
 *   Autor:             Juliusz Sompolski                                *
 *   Opis:              Rozwiazanie bledne                               *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cmath>
#include <cstdlib>

#define MAXIMUM(a,b) ((a)>(b)?(a):(b))

#define MAXN 100000

/** Liczba budynkow */
int N;
/** Wysokosci budynkow */
int H[MAXN],HMax,MAXind;

int main() {
	/* Wczytanie danych */
	scanf("%d", &N);
	for(int i = 0; i < N; i++)
		scanf("%d", &H[i]);
	/* Preprocessing */
	HMax = H[0]; MAXind = 0;
	for(int i = 1; i < N; i++) {
		if(H[i] > HMax) {
			MAXind = i;
			HMax = H[i];
		}
	}
		
	/* Odpowiedzi */
	for(int i = 0; i < N; i++)
		printf("%d\n", HMax-H[i] + (int) ceil(sqrt(abs(MAXind-i))));
}
