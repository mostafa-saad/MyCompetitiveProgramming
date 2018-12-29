/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n * k * k)                                     *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Sprawdzamy klopotliwy przypadek oddzielnie tzn.  *
 *                      gdy mniej liczne litery sa w liczbie 1,          *
 *                      nastepnie przerabiamy slowo na ciag -1 0 1       *
 *                      i znajdujemy segment o maksymalnej sumie,        *
 *                      ktory zawiera -1                                 *
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

	// sprawdzanie czy mniejliczne litery sa jednoelementowe
	REP(i, MAXK)
	{	
		// czyszczenie
		REP(j, MAXK)
			licznik[j] = false;
		ok = false;

		REP(j, n)
			if(slowo[j] == i)
			{
				ok = true;
				REP(k, MAXK)
				{
					if(licznik[k] > maks)
						maks = max(maks, licznik[k] - 1);
					licznik[k] = 0;
				}
			}
			else
				licznik[slowo[j]]++;

		if(ok)
			REP(k, MAXK)
				if(licznik[k] > maks)
					maks = max(maks, licznik[k] - 1);
	}


	REP(i, MAXK)
		REP(j, MAXK)
		{
			// konwersja ciagu liter do ciagu -1 0 1
			REP(k, n)
			{
				if(slowo[k] == i)
					ciag[k] = 1;
				else 
					if(slowo[k] == j)
						ciag[k] = -1;
					else
						ciag[k] = 0;
			}
			suma = 0;
			ok = false;

			// wyszukiwanie segmentu o maksymalnej sumie
			REP(k, n)
			{
				suma += ciag[k];
			
				if(suma < 0)
				{
					suma = 0;
					ok = false;
				}
				else
					if(ciag[k] == -1)
						ok = true;

				if(ok)
					maks = max(maks, suma);
			}				
	}

	// wypisanie wyniku
	printf("%d\n", maks);

	return 0;
}

