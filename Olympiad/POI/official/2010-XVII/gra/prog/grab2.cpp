/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Gra w minima (GRA)                               *
 *   Plik:              grab2.cpp                                        *
 *   Autor:             Jakub Lacki                                      *
 *   Opis:              Rozwiazanie niepoprawne.                         *
 *                      Polaczenie dwoch strategii: wez zawsze maksimum  *
 *                      oraz wez zawsze wszystkie maksima.               *
 *   Zlozonosc czasowa: O(n * log n)                                     *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define MAXN 1000000

int wez_maks(vector<int> karty)
{
    int wynik[MAXN];
    int n = karty.size();

    wynik[0] = karty[0];
    for(int i=1; i<n; i++)
	wynik[i] = karty[i] - wynik[i-1];
    return wynik[n-1];
}

int wez_wszystkie_maksy(vector<int> karty)
{
    karty.erase(unique(karty.begin(), karty.end()), karty.end());
    return wez_maks(karty);
}

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

    printf("%d\n", max(wez_maks(karty), wez_wszystkie_maksy(karty)));
}
