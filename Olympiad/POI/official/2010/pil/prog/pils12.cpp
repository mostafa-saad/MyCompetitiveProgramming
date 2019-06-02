/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Piloci (PIL)                                     *
 *   Plik:              pils12.cpp                                       *
 *   Autor:             Bartosz Gorski                                   *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Wyszukiwanie binarne i kolejki dwustronne.       *
 *   Zlozonosc czasowa: O(n * log n)                                     *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<algorithm>
#include<assert.h>
using namespace std;

#define MAX_N 3000000

int n, t, a[MAX_N], qmin[MAX_N], qmax[MAX_N], ibx, iex, ibn, ien, l, c, r;

void add(int i) {
	while(ibn < ien && a[qmin[ien - 1]] >= a[i])
		--ien;
	qmin[ien++] = i;
	while(ibx < iex && a[qmax[iex - 1]] <= a[i])
		--iex;
	qmax[iex++] = i;
}

void remove(int i) {
	while(ibn < ien && qmin[ibn] < i)
		++ibn;
	while(ibx < iex && qmax[ibx] < i)
		++ibx;
}

bool check(int l) {
	ibx = iex = ibn = ien = 0;
	for(int i = 0; i < l - 1; ++i)
		add(i);
	for(int i = 0; i < n - l + 1; ++i) {
		remove(i);
		add(i + l - 1);
		if((a[qmax[ibx]] - a[qmin[ibn]]) <= t)
			return true;
	}
	return false;
}	

int main()
{
	assert(scanf("%d%d", &t, &n) == 2);
	for(int i = 0; i < n; ++i)
		assert(scanf("%d", &a[i]) == 1);
	l = 1; r = n;
	while(l < r) {
		c = (l + r + 1) / 2;
		if(check(c))
			l = c;
		else
			r = c - 1;
	}
	printf("%d\n", l);
	return 0;
}
