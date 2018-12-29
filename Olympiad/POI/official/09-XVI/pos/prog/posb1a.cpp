/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Poszukiwania (POS)                                        *
 *   Plik:     pos.cpp                                                   *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie bledne. Zaklada, ze zawsze nalezy podzielic   *
 *             przedzial w proporcji a do b                              *
 *                                                                       *
 *************************************************************************/

#include "poslib.h"

int n,a,b;
long long l,r;

int main() {
	inicjuj(&n, &a, &b);
	l = 1; r = n;
	
	// Szuka Bajtyny
	while(l < r) {
		int p = (l*a + r*b)/(a+b); // odpowiedz TAK "powyzej" p, odpowiedz NIE "ponizej" p
		if(pytaj('W', p)) l = p+1; else r = p;
	}
	
	// Udziela odpowiedzi
	odpowiedz(l);
	return 0;
}
