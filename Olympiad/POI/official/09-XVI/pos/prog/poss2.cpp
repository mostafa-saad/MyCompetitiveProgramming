/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Poszukiwania (POS)                                        *
 *   Plik:     poss2.cpp                                                 *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie wolne. Pesymistycznie O(n^2), choc w praktyce *
 *             dziala jak O(n log n).                                    *
 *                                                                       *
 *************************************************************************/

#include "poslib.h"

#define MAX(a,b) ((a)>(b)?(a):b)
#define INF 2000000000

#define TAK 1
#define NIE 0

int n,a,b;
int l,r;

int *T; // t[n] - koszt odpowiedzi dla przedzialu zawierajacego i pieter.
int *P; // p[n] - dlugosc przedzialu dla odpowiedzi TAK jaki nalezy zadac majac przedzial zawierajacy n pieter aby utrzymac sie w pesymistycznym koszcie.
int min(int, int, int);
int t(int);
int p(int);

/*
	Podzial przedzialu dlugosci n na przedzialy dlugosci i dla TAK i n-i dla NIE.
	Pesymistyczny koszt, to wiekszy z kosztow odpowiedzi 
	- TAK i kosztu dla przedzialu dlugosci i
	- NIE i kosztu dla przedzialu dlugosci n-i
	czyli f(i) = MAX(a+t(i),b+t(n-i))
	t(n) jest niemalejace, a wiec a+t(i) jest niemalejace, b+t(n-i) jest nierosnace,
	czyli f(i) ma co najwyzej jedno minimum lokalne.
		
	Funkcja oblicza minimum funkcji f(i) w danym przedziale i dla danego n
*/
int min(int n, int l, int r) {
	if(r - l >= 250) {
		int p1 = (2*l+r)/3,p2=(l+2*r)/3; // punkty podzialu przedzialu [l,r] na 3
		int f1 = MAX(a+t(p1),b+t(n-p1)),f2 = MAX(a+t(p2),b+t(n-p2)); // wartosci funkcji w punktach podzialu
		if(f1 < f2) return min(n,l,p2-1); // f(p2)>f(p1), wiec minimum jest w [l,p2]
		else if(f1 > f2) return min(n,p1+1,r); // f(p1)>f(p2), wiec minimum jest w [p1,r]
		else /* f1 == f2 */ {
			/*
				Jezeli w ktorymkolwiek z przedzialow [l,p1], [p1,p2], [p2,r] jest wartosc mniejsza,
				to jest ona minimum.
			*/
			if(min(n,p1,p2) < f1) return T[n];
			if(min(n,l,p1) < f1) return T[n];
			if(min(n,p2,r) < f1) return T[n];
		}
	}
	else {
		T[n] = INF;
		for(int i = l; i <= r; i++) {
			int wyn = MAX(a+t(i),b+t(n-i));
			if(wyn < T[n]) { T[n]=wyn; P[n]=i; } // podzial lepszy od dotychczas obliczonego minimum.
		}
	}
	return T[n];
}
/*
Oblicza lub zwraca spamietane t[i] i p[i]
*/
int t(int n) { // oblicza t[n] badz zwraca spamietane.
	if(n <= 1) return 0;
	if(T[n] == 0) min(n,1,n-1);
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
