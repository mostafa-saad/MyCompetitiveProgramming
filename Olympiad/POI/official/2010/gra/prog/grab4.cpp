
/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Gra w minima (GRA)                               *
 *   Plik:              grab4.cpp                                        *
 *   Autor:             Jakub Lacki                                      *
 *   Opis:              Rozwiazanie niepoprawne.                         *
 *                      Rozwiazanie brutalne. Ze wzgledu na uzycie masek *
 *                      bitowych dla n>20 daje zle wyniki                *
 *   Zlozonosc czasowa: O(3^n)                                           *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

int wynik[1<<20];

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

    for(int i=1; i<(1<<n); i++)
    {
	int maska = i;
	int akt = maska;
	while(akt)
	{
	    int pierwszy_bit;
	    for(int j=0; ; j++)
		if(akt & (1<<j))
		{
		    pierwszy_bit = j;
		    break;
		}
	    wynik[maska] = max(wynik[maska], karty[pierwszy_bit] - wynik[maska ^ akt]);
	    akt = (akt - 1) & maska;
	}
    }

    printf("%d\n", wynik[(1<<n)-1]);
}
