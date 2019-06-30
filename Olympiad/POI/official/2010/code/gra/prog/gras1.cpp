/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Gra w minima (GRA)                               *
 *   Plik:              gras1.cpp                                        *
 *   Autor:             Jakub Lacki                                      *
 *   Opis:              Rozwiazanie powolne - nieefektywne sortowanie.   *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define MAXN 1000000

long long wynik[MAXN];

void wolne_sortowanie(vector<int>& karty)
{
    int n = karty.size();
    
    for(int i=1; i<n; i++)
	for(int j=i; j>=1; j--)
	{
	    if(karty[j] >= karty[j-1])
		break;

	    swap(karty[j], karty[j-1]);
	}
}

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

    wolne_sortowanie(karty);

    wynik[0] = karty[0];

    for(int i=1; i<n; i++)
	wynik[i] = max((long long)karty[i] - wynik[i-1], wynik[i-1]);

    printf("%lld\n", wynik[n-1]);
}
