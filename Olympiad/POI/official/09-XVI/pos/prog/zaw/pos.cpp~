/*
Rozwiazanie przykladowe dla zawodnikow do zadania POS
*/
#include "poslib.h"

int n, a, b;
int l, r;

int main() {
	inicjuj(&n, &a, &b);
	l = 1; r = n;
	
	// Szuka Bajtyny
	while(l < r) {
		int p = (l + r) / 2;
		if(pytaj('W', p)) l = p + 1; else r = p;
	}
	
	// Udziela odpowiedzi
	odpowiedz(l);
	return 0;
}
