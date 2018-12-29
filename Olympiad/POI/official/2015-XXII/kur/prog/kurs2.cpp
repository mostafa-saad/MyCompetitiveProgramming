/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Kurs szybkiego czytania                            *
 *   Zlozonosc czasowa:    O(n + m)                                           *
 *   Autor programu:       Kamil Debowski                                     *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                         szukanie wzorca, KMP                               *
 *****************************************************************************/

#include<cstdio>
#include<algorithm>
#include<assert.h>
#include<vector>
using namespace std;
typedef long long ll;
const int MAX_M = 1e6 + 5, MAX_N = 1e7 + 5;
char wzorzec_char[MAX_M];
bool wzorzec[MAX_M];
bool slowo[MAX_N];
int pref[MAX_M];

int main() {
	ll n, a, b, p;
	int m;
	scanf("%lld%lld%lld%lld%d", &n, &a, &b, &p, &m);
	scanf("%s", wzorzec_char);
	for(int i = 0; i < m; ++i)
		wzorzec[i] = (wzorzec_char[i] == '1');
	for(ll i = 0; i < n; ++i)
		slowo[(int) i] = ((a * i + b) % n >= p);
	
	pref[0] = -1;
	for(int i = 1; i <= n; ++i) {
		pref[i] = pref[i-1];
		while(pref[i] != -1 && wzorzec[pref[i]] != wzorzec[i-1])
			pref[i] = pref[pref[i]];
		++pref[i];
	}
	int pom = 0, wynik = 0;
	for(int i = 0; i < n; ++i) {
		while(pom != -1 && wzorzec[pom] != slowo[i])
			pom = pref[pom];
		++pom;
		if(pom == m) {
			++wynik;
			pom = pref[pom];
		}
	}
	printf("%d\n", wynik);
	return 0;
}
