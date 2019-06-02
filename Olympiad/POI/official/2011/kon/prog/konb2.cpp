/*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    konb2.cpp                                                  *}
{*   Autor:   Bartosz Górski                                             *}
{*   Opis:    Rozwiązanie nieefektywne czasowo i niestabilne numerycznie *}
{*            Złożoność: O(n * 2 ^ n)                                    *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************/

#include<cstdio>
#include<assert.h>

#define MAX_N 5000

int n, k, a, p2[MAX_N + 1], e[MAX_N], ep[MAX_N], sep, res;
bool ok;

int main()
{
	assert(scanf("%d", &n) == 1);
	p2[0] = 1;
	for(int i = 0; i < n; ++i)
		p2[i + 1] = p2[i] << 1;
	for(int i = 0; i < n; ++i) {
		assert(scanf("%d", &k) == 1);
		for(int j = 0; j < k; ++j) {
			assert(scanf("%d", &a) == 1);
			e[i] |= p2[a - 1];
		}
	}
	for(int i = 0; i < n; ++i)
		ep[i] = (p2[n] - 1) ^ e[i];
	for(int i = 0; i < (p2[n]); ++i) {
		ok = true;
		sep = (p2[n] - 1) ^ i;
		for(int u = 0; u < n && ok; ++u)
			if(i & p2[u])
				ok &= (((e[u] | p2[u]) & i) == i);
			else
				ok &= ((ep[u] & sep) == sep);
		res += ok;
	}
	printf("%d\n", res);
	return 0;
}

