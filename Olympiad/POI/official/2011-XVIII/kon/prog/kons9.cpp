/*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kons9.cpp                                                  *}
{*   Autor:   Bartosz Górski                                             *}
{*   Opis:    Rozwiązanie nieefektywne czasowo                           *}
{*            Złożoność: O(n ^ 3)                                        *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************/

#include<cstdio>
#include<algorithm>
#include<assert.h>
using namespace std;

#define MAX_N 5000

int n, k, a, i1, i2, r1, r2;
bool e[MAX_N][MAX_N], c[2][MAX_N + 1][MAX_N], ok;

int main()
{
	assert(scanf("%d", &n) == 1);
	for(int i = 0; i < n; ++i) {
		assert(scanf("%d", &k) == 1);
		for(int j = 0; j < k; ++j) {
			assert(scanf("%d", &a) == 1);
			e[i][a - 1] = true;
		}
	}
	c[0][0][0] = true;
	c[0][1][0] = false;
	r1 = 2;
	i1 = 0; i2 = 1;
	for(int i = 1; i < n; ++i) {
		r2 = 0;
		for(int j = 0; j < r1; ++j)
			for(int k = 0; k < 2; ++k) {
				ok = true;
				for(int u = 0; u < i && ok; ++u)
					if(e[i][u])
						ok &= (k == 0 || c[i1][j][u] == 0);
					else
						ok &= (k == 1 || c[i1][j][u] == 1);
				if(ok) {
					for(int v = 0; v < i; ++v)
						c[i2][r2][v] = c[i1][j][v];
					c[i2][r2][i] = k;
					++r2;
				}
			}
		swap(i1, i2);
		swap(r1, r2);
	}
	if(r1 > n)
		--r1;
	printf("%d\n", r1);
	return 0;
}

