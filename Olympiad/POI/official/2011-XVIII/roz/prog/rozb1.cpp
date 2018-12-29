/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n * k * k)                                     *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Jedna z blednych wersji rozwiazania              *
 *                      z maksymalnym segmentem                          *
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
#define MAXK 26

int slowo[MAXN];		// tablica z wczytanym slowem
int ciag[MAXN];			// tablica z tymczasowym ciagiem -1 0 1
int n, temp,  maks, mini, wynik, suma, ok;
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


	// wyliczamy najlepszy fragment dla kazdych koncow
	REP(i, MAXK)
		REP(j, MAXK)
		{
			// ustawienie ciagu
			ok = -1;
			REP(k, n)
			{
				if(slowo[k] == i)
					ciag[k] = 1;
				else if(slowo[k] == j)
				{	ok = 1;
					ciag[k] = -1;
				}else 
					ciag[k] = 0;
			}
			suma = 0;
			maks = 0;

			
			// przejscie po ciagu poszukujac maksymalnej sumy
			REP(k, n)
			{
				if(ciag[k] == 1)
				{
					suma++;
					if(suma > maks && ok >= 0)
						maks = max(maks, suma);
		        }
				else 
					if(ciag[k] == -1)
					{
						if(suma > -1)
							suma--;
						if(suma == -1)
							ok = 0;
						else
							if(ok == 0)
							{
								ok = 1;
								suma++;
								maks = max(maks, suma);
							}
					}
			}

			wynik = max(maks, wynik);
		}

	// wypisanie wyniku
	printf("%d\n", wynik);

	return 0;
}
