/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Poszukiwania (POS)                                        *
 *   Plik:     poss1.cpp                                                 *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie wolne O(n^2). Pamiec O(n).                    *
 *                                                                       *
 *************************************************************************/

#include "poslib.h"

#define MAX(a,b) ((a)>(b)?(a):b)
#define INF 2000000000

#define TAK 1
#define NIE 0

int n,a,b;
int l,r;

/*
Oblicza lub zwraca spamietane t[i] i p[i]
*/
int *T; // t[n] - koszt odpowiedzi dla przedzialu zawierajacego i pieter.
int *P; // p[n] - dlugosc przedzialu dla odpowiedzi TAK jaki nalezy zadac majac przedzial zawierajacy n pieter aby utrzymac sie w pesymistycznym koszcie.
int t(int n) { // oblicza t[n] badz zwraca spamietane.
	if(n <= 1) return 0;
	if(T[n] == 0) {
		T[n] = INF;
		for(int i = 1; i < n; i++) {
			/*
			Podzial przedzialu dlugosci n na przedzialy dlugosci i dla TAK i n-i dla NIE.
			Pesymistyczny koszt, to wiekszy z kosztow odpowiedzi 
			- TAK i kosztu dla przedzialu dlugosci i
			- NIE i kosztu dla przedzialu dlugosci n-i
			*/
			int wyn = MAX(a+t(i),b+t(n-i));
			if(wyn < T[n]) { T[n]=wyn; P[n]=i; } // podzial lepszy od dotychczas obliczonego minimum.
		}
	}
	return T[n];
}
int p(int n) { // oblicza t[n] badz zwraca obliczone
	if(P[n] == 0) t(n); // efektem ubocznym obliczenia t[n] bedzie obliczenie p[n].
	return P[n];
}

int main() {
	inicjuj(&n, &a, &b);
	l = 1; r = n;
	T = new int[n+1]; P = new int[n+1];
	
	// Szuka Bajtyny
	while(l < r) {
		int i = p(r-l+1); // dlugosc przedzialu na ktory pytanie powinno dawac odpowiedz TAK
		if(pytaj('N', l+i)) { // TAK
			r = l+i-1;
		} else { // NIE
			l = l+i;
		}
	}
	
	// Udziela odpowiedzi
	odpowiedz(l);
	return 0;
}
