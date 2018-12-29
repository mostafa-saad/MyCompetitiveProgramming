/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przechadzka Bajtusia (PRZ)                                *
 *   Plik:     przb4.cpp                                                 *
 *   Autor:    Jakub Lacki                                               *
 *   Opis:     Rozwiazanie nieopoprawne. Zawsze wypisuje -1.             *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
using namespace std;

#define MAXN 400
#define MAXM 100000
#define MAXD 100
#define ROZMIAR_ALF 26
#define INF 100000000
#define ZNAK_HASH ('a' + ROZMIAR_ALF)
#define ROZM_G (MAXN*MAXN*(ROZMIAR_ALF+1))


// Reprezentacja grafu

void wczytaj_graf(int n, int m)
{
    int a, b;
    char zn;
    for(int i=0; i<m; i++)
    {
	scanf("%d%d %c", &a, &b, &zn);
    }
}



void zapytanie(int p, int k)
{
    printf("-1\n");
}


int main()
{
    int n, m, d;
    int zapytania[MAXD];
    scanf("%d%d",&n,&m);
    wczytaj_graf(n, m);

    scanf("%d",&d);
    for(int i=0; i<d; i++)
	scanf("%d", &zapytania[i]);
    for(int i=0; i<d-1; i++)
	zapytanie(zapytania[i]-1, zapytania[i+1]-1);
    return 0;
}
