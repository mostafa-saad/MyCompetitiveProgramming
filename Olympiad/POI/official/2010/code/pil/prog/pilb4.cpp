/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Piloci (PIL)                                     *
 *   Plik:              pilb4.cpp                                        *
 *   Autor:             Bartosz Gorski                                   *
 *   Opis:              Rozwiazanie niepoprawne.                         *
 *                      Rozpatruje tylko prefiksy.                       *
 *   Zlozonosc czasowa: O(n)                                             *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<algorithm>
#include<assert.h>
using namespace std;

#define MAX_N 3000000

int n, t, a[MAX_N], qmin, qmax, r;
int main()
{
	assert(scanf("%d%d", &t, &n) == 2);
	for(int i = 0; i < n; ++i)
		assert(scanf("%d", &a[i]) == 1);
	qmin = a[0];
	qmax = a[0];
	r = n;
	for(int i = 0; i < n; ++i) {
		qmin = min(a[i], qmin);
		qmax = max(a[i], qmax);
		if((qmax - qmin) > t) {
			r = i;
			break;
		}
	}
	printf("%d\n", r);
	return 0;
}
