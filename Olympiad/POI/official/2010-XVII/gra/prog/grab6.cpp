/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Gra w minima (GRA)                               *
 *   Plik:              grab6.cpp                                        *
 *   Autor:             Jakub Lacki                                      *
 *   Opis:              Rozwiazanie niepoprawne.                         *
 *                      Bierze karty z góry aż do napotkania             *
 *                      największej przerwy liczonej jako                *
 *                      iloraz wartosci sasiednich kart.                 *
 *   Zlozonosc czasowa: O(n * log n)                                     *
 *                                                                       *
 *************************************************************************/


#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define MAXN 1000000

long long wynik[MAXN];

int main()
{
    int n, k;
    vector<int> karty;

    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
	scanf("%d", &k);
	karty.push_back(k);
    }

    sort(karty.begin(), karty.end());

    wynik[0] = karty[0];
    long long najlepszy = wynik[0];
    double max_roznica = 0;

    for(int i=1; i<n; i++)
    {
	wynik[i] = max((long long)karty[i] - wynik[i-1], najlepszy);
	if(double(karty[i]) / double(karty[i-1]) > max_roznica)
	{
	    max_roznica = double(karty[i]) / double(karty[i-1]);
	    najlepszy = wynik[i];
	}
    }

    printf("%lld\n", wynik[n-1]);
}
