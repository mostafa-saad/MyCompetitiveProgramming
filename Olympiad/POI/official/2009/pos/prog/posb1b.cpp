/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Poszukiwania (POS)                                        *
 *   Plik:     posb1b.cpp                                                *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie bledne. Zaklada, ze zawsze nalezy dzielic     *
 *             przedzial w proporcji a do b.                             *
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
		int p = (l*b + r*a)/(a+b); // odpowiedz TAK "ponizej" p, odpowiedz NIE "powyzej" p
		if(pytaj('N', p)) r = p-1; else l = p;
	}
	
	// Udziela odpowiedzi
	odpowiedz(l);
	return 0;
}
