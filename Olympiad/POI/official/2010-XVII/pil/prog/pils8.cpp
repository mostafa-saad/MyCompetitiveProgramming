/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Piloci (PIL)                                     *
 *   Plik:              pils8.cpp                                        *
 *   Autor:             Bartosz Gorski                                   *
 *   Opis:              Rozwiazanie powolne - brutalne.                  *
 *                      Nie sprawdza przedzialow krotszych od rekordu.   *
 *   Zlozonosc czasowa: O(n^3)                                           *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<algorithm>
#include<assert.h>
using namespace std;

#define MAX_N 3000000

int n, t, a[MAX_N], r = 1;

bool ok(int x, int y) {
	for(int i = x; i <= y; ++i)
		for(int j = i + 1; j<= y; ++j)
			if(abs(a[i] - a[j]) > t)
				return false;
	return true;
}

int main()
{
	assert(scanf("%d%d", &t, &n) == 2);
	for(int i = 0; i < n; ++i)
		assert(scanf("%d", &a[i]) == 1);	
	for(int i = 0; i < n; ++i)
		for(int j = r; j < n - i; ++j) {
			if(!ok(i, i + j))
				break;
			r = j + 1;
		}
	printf("%d\n", r);
	return 0;
}
