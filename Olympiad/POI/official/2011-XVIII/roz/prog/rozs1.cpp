/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n ^ 3)                                         *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Sprawdzamy kazdy mozliwy segment                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <set>
#include <iostream>
#include <cstring>
#include <cmath>

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

int slowo[MAXN];		// tablica z wczytanym slowem
int licznik[26];		// tymczasowa tablica trzymajaca liczbe poszczegolnych liter
int n, temp,  maks, mini, wynik;
char c;


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

	//REP(i, n)
	//	cout << int(slowo[i]) << " ";
	//cout << endl;
	

	// wyliczamy najlepszy fragment dla kazdych koncow
	REP(i, n)
		FOR(j, i + 1, n - 1)
		{
			// czyszczenie licznika
			REP(k, 26)
				licznik[k] = 0;

			// petla po segmencie
			FOR(k, i, j)
				licznik[slowo[k]]++;
			
			// szukamy max i min
			maks = 0;
			mini = MAXN;
			REP(k, 26)
			{
				maks = max(maks, licznik[k]);
				if(licznik[k] > 0)
					mini = min(mini, licznik[k]);
			}
			
			wynik = max(wynik, maks - mini);
			
			//cout << "pocz " << i << " kon " << j << " w sumie " << maks - mini << endl;
		}


	// wypisanie wyniku
	printf("%d\n", wynik);

	return 0;
}
