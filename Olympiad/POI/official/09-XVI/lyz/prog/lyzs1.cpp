/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Lyzwy (LYZ)                                               *
 *   Plik:     lyzs1.cpp                                                 *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie wolniejsze O(n*m*d) Dla kazdego rozmiatu stopy*
 *             proboje przydzielic lyzwy poczawszy od najmniejszych      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
using namespace std;

#define MAX_N 200001
#define min(a,b) ((a) < (b) ? (a) : (b))

int n, m, k, d;
long long t[MAX_N],lyzwy[MAX_N];

inline bool spr()
{
	int i,j;
	/* Inicjowanie wolnych lyzew */
	for(i = 1; i <= n; i++) lyzwy[i] = k;
	for(i = 1; i <= n-d; i++) {
		long long ile = t[i]; /* Lyzwiarze ktorym trzeba jeszcze przydzielic lyzwy */
		for(j = i; ile != 0 && j <= i+d; j++) {
			long long przydziel = min(lyzwy[j],ile);
			ile -= przydziel; lyzwy[j] -= przydziel;
		}
		if(ile != 0) return false;
	}
	return true;
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &k, &d);
	while (m--)
	{
		int r, x;
		scanf("%d%d", &r, &x);
		t[r] += x;
		if (spr())
			puts("TAK");
		else
			puts("NIE");
	}
	return 0;
}
