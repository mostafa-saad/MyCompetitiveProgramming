/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Lyzwy (LYZ)                                               *
 *   Plik:     lyzs7.cpp                                                 *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie wolniejsze O(n*m*d). Dla kazdego rozmiaru     *
 *             stopu probuje przydzielic lyzwy poczawszy od najmniejszych*
 *                                                                       *
 *************************************************************************/

#include <cstdio>
using namespace std;

#define MAX_N 200001
#define min(a,b) ((a) < (b) ? (a) : (b))

int n, m, k, d;
long long t[MAX_N];

inline bool spr()
{
	int i;
	long long max=0,cur=0;
	/* Szukanie spojnego podciagu o najwiekszej sumie */
	for(i = 1; i <= n-d; i++) {
		cur += t[i];
		if(cur > max) max = cur;
		if(cur < 0) cur = 0;
	}
	if(max > (long long) k * (long long) d) return false; else return true;
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &k, &d);
	for(int i = 1; i <= n-d; i++) t[i] = -k;
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
