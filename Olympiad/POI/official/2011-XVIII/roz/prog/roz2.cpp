/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n * k)                                         *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                      Sprawdzamy klopotliwy przypadek oddzielnie tzn.  *
 *                      gdy mniej liczne litery sa w liczbie 1, potem    *
 *                      dynamicznie wyliczamy minimalne prefiksy dla     *
 *                      kazdej pary i z tego otrzymujemy maksymalna sume *
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
int pref[MAXK][MAXK];	// roznica pomiedzy liczba liter na najgorszym mozliwym prefiksie

int n, temp, maks;
char c;
bool ok, oki[MAXK][MAXK];	// tablica oki oznacza czy pomiedzy najgorszym mozliwym
							// prefiksem a aktualnym indeksem jest mniejliczna litera
							// ok analogicznie dla szczegolnego przypadku

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

	//czyszczenie
	REP(j, MAXK)	
		licznik[j] = false;


	// dynamik na biezaco uaktualnia najgorsze mozliwe prefiksy
	REP(j, n)
	{
		temp = slowo[j];
		licznik[temp]++;

		REP(k, MAXK)
			if(oki[temp][k])
				maks = max(maks, licznik[temp] - licznik[k] - pref[temp][k]);
		REP(k, MAXK)
		{
			oki[k][temp] = true;
			if (pref[k][temp] > licznik[k] - licznik[temp])
			{
				pref[k][temp] = licznik[k] - licznik[temp];
				oki[k][temp] = false;
			}
		}

		/*
		REP(k, MAXK)
			cout << licznik[k] << " ";
		cout << endl;

		REP(k, MAXK){
			REP(l, MAXK)
				cout << pref[k][l] << " " ;
			cout << endl;
		}
		cout << " maks " << maks << endl;
		*/

	}

	// wypisanie wyniku
	printf("%d\n", maks);

	return 0;
}

