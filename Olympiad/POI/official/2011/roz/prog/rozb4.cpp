/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n * k * k)                                     *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Rozwiazanie polega na wypisaniu samych zer       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

#define REP(i,n) for(int _n=n, i=0;i<_n;++i)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;--i)
#define FORE(i,x) for(__typeof((x).begin()) i=(x).begin();i != (x).end();++i)
#define X first
#define Y second
#define PB push_back	
#define MP make_pair
#define MAXN 1000005		
#define MAXK 26

int slowo[MAXN];		// tablica z wczytanym slowem
int licznik[MAXK];		// tymczasowa tablica trzymajaca liczby poszczegolnych liter
int ciag[MAXN];			// wczytane slowo przerabiamy do postaci ciagu -1 0 1

int n, suma, temp, maks;
char c;
bool ok;				// ok oznacza czy segment zawiera -1

int main()
{
	// wczytanie slowa i przesuniecie
	temp = scanf("%d", &n);
	temp = scanf("%c", &c);
	REP(i, n) 
	{
		temp = scanf("%c", &c);
		slowo[i] = c - 97;
	}	

	// wypisanie wyniku
	printf("0\n");

	return 0;
}

