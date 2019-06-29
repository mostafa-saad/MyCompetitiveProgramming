/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Lyzwy (LYZ)                                               *
 *   Plik:     lyzb1.cpp                                                 *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie bledne. Przydziela lyzwy tak jakby d=0.       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
using namespace std;

#define MAX_N 200001
#define min(a,b) ((a) < (b) ? (a) : (b))

int n, m, k, d;
long long t[MAX_N];

int main()
{
	int brakuje = 0;
	scanf("%d%d%d%d", &n, &m, &k, &d);
	while (m--)
	{
		int r, x;
		scanf("%d%d", &r, &x);
		if(t[r] <= k && t[r] + x > k) brakuje++;
		if(t[r] > k && t[r] + x <= k) brakuje--;
		t[r] += x;
		if (brakuje == 0)
			puts("TAK");
		else
			puts("NIE");
	}
	return 0;
}
