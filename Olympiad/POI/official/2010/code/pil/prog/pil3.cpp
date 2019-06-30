/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Piloci (PIL)                                     *
 *   Plik:              pil3.cpp                                         *
 *   Autor:             Bartosz Gorski                                   *
 *   Opis:              Rozwiazanie weryfikujace.                        *
 *   Zlozonosc czasowa: O(n)                                             *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<algorithm>
#include<assert.h>
using namespace std;

#define MAX_N 3000000

int n, t, a[MAX_N], qmin[MAX_N], qmax[MAX_N], ibx, iex, ibn, ien, ia, r;
int main()
{
	assert(scanf("%d%d", &t, &n) == 2);
	for(int i = 0; i < n; ++i)
		assert(scanf("%d", &a[i]) == 1);
	ia = -1;
	for(int i = 0; i < n; ++i) {
		if(ibn < ien && qmin[ibn] < i)
			++ibn;
		if(ibx < iex && qmax[ibx] < i)
			++ibx;
		while((ia + 1) < n && (!(ibx < iex) || !(ibn < ien) ||
					(max(a[qmax[ibx]], a[ia + 1]) - min(a[qmin[ibn]], a[ia + 1])) <= t)) {
			++ia;
			while(ibn < ien && a[qmin[ien - 1]] >= a[ia])
				--ien;
			qmin[ien++] = ia;
			while(ibx < iex && a[qmax[iex - 1]] <= a[ia])
				--iex;
			qmax[iex++] = ia;
		}
		r = max(r, ia - i + 1);
	}
	printf("%d\n", r);
	return 0;
}
