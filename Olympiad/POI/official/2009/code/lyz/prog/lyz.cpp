/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Lyzwy (LYZ)                                               *
 *   Plik:     lyz.cpp                                                   *
 *   Autor:    Jakub Radowszewski                                        *
 *   Opis:     Rozwiazanie wzorcowe O((n+m)*log(n))                      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
using namespace std;

#define MAX_N 200000
#define MAX_N2 262144
#define KORZEN 1

int n, m, k, d;


/* Drzewo przedzialowe */
struct wezel
{
	long long suma;
	long long mx_lewy, mx_prawy, mx;
} drz[2 * MAX_N2 + 1];

int ile;

#define rodzic(v) ((v) / 2)
#define lsyn(v) (2 * (v))
#define psyn(v) (2 * (v) + 1)
#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

/* Zmienia ilosc czlonkow o rozmiarze stopy x o w i uaktualnia drzewo */
inline void ustaw(int x, int w)
{
	/* Ustawia wartosc w wierzcholku reprezentujacym przedzial jednoelementowy */
	int v = ile + x;
	drz[v].suma += w;
	drz[v].mx_lewy = drz[v].mx_prawy = drz[v].mx = max(drz[v].suma, 0LL);

	/* Poprawia idac w gore drzewa */
	while (v != KORZEN)
	{
		v = rodzic(v);
		drz[v].suma = drz[lsyn(v)].suma + drz[psyn(v)].suma;
		drz[v].mx_lewy = max(drz[lsyn(v)].mx_lewy, drz[lsyn(v)].suma + drz[psyn(v)].mx_lewy);
		drz[v].mx_prawy = max(drz[psyn(v)].mx_prawy, drz[psyn(v)].suma + drz[lsyn(v)].mx_prawy);

		drz[v].mx = max(drz[lsyn(v)].mx, drz[psyn(v)].mx);
		drz[v].mx = max(drz[v].mx, drz[lsyn(v)].mx_prawy + drz[psyn(v)].mx_lewy);
	}
}



int main()
{
	/* Inicjalizacja */
	scanf("%d%d%d%d", &n, &m, &k, &d);
	ile = 1;
	while (ile <= n-d)
		ile *= 2;
	for (int i = 1; i <= n-d; i++)
		ustaw(i, -k);
	
	/* Przetwarzanie zdarzen */
	while (m--)
	{
		int r, x;
		scanf("%d%d", &r, &x);
		ustaw(r, x);
		if (drz[KORZEN].mx <= (long long)d * (long long)k)
			puts("TAK");
		else
			puts("NIE");
	}
	return 0;
}
