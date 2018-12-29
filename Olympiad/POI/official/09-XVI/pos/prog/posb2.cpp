/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Poszukiwania (POS)                                        *
 *   Plik:     pos1.pas                                                  *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie prawie wzorcowe O(max(a,b)*log n), ktore      *
 *             nie sprawdza czy poprawilo sie szacowanie pesymistycznego *
 *             kosztu                                                    *
 *                                                                       *
 *************************************************************************/

#include "poslib.h"

#define MAX(a,b) ((a)>(b)?(a):b)

#define MAXN 1000000000
#define MAXAB 10000

#define TAK 1
#define NIE 0

int n,a,b;
int l,r,w;

/*
Oblicza lub zwraca spamietane Q[i]
*/
int Q[100*MAXAB]; // Q[i] - maksymalna liczba pieter wsrod ktorych mozna znalezc odpowiedz kosztem i
int q(int i) {
	if(i < 0) return 0;
	if(Q[i] == 0) { // jesli nie bylo jeszcze obliczone, to oblicz
		/* Majac do dyspozycji i bajtalarow zadajemy pytanie
		i albo zostajemy z i-a bajtalarami i maksymalnie mozemy obsluzyc i-a pieter
		albo zostajemy z i-b bajtalarami i maksymalnie mozemy obsluzyc i-b pieter
		*/
		Q[i] = q(i-a) + q(i-b);
		if(Q[i] == 0) Q[i] = 1; // zawsze mozna zgadnac jak sie ma jedno pietro.
	}
	return Q[i];
}

int main() {
	inicjuj(&n, &a, &b);
	l = 1; r = n;
	
	// Wyznacza koszt jaki musi poniesc Bajtek.
	int step = 1; w=step;
	do {
		w -= step;
		while(q(w) < n) w += step;
		step /= 2;
	} while(step != 0);
	
	// Szuka Bajtyny
	while(l < r) {
		// Po odpowiedzi Bitocego moglo sie poprawic szacowanie - rozwiazanie bledne tego nie sprawdza
		//while(q(w) >= r-l+1) w--; w++;
		
		// Zadaj pytanie
		if(pytaj('N', l+q(w-a))) { // odpowiedz TAK
			// Bajtyna w przedziale [l, l+q(w-A)-1] dlugosci q(w-A) => do znalezienia w koszcie w-A
			r = l+q(w-a)-1;
			w -= a;
		} else { // odpowiedz NIE
			// Bajtyna w przedziale [l+q(w-A), r] dlugosci q(w)-q(w-A)=q(w-B) => do znalezienia w koszcie w-B
			l = l+q(w-a);
			w -= b;
		}
	}
	
	// Udziela odpowiedzi
	odpowiedz(l);
	return 0;
}
