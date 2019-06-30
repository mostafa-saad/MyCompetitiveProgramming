/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Gra w minima (GRA)                               *
 *   Plik:              grab3.cpp                                        *
 *   Autor:             Jakub Lacki                                      *
 *   Opis:              Rozwiazanie niepoprawne.                         *
 *                      Polaczenie dwoch strategii: wez wszystko         *
 *                      oraz wez zawsze wszystko poza minimami.          *
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

    int prawie_minimum = karty[0];

    for(int i=0; i<n; i++)
	if(karty[i] > prawie_minimum)
	{
	    prawie_minimum = karty[i];
	    break;
	}
    
    printf("%d\n", max(karty[0], prawie_minimum - karty[0]));
}
