/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Tomasz Kociumaka                                 *
 *   Zlozonosc czasowa: O(n * k)                                         *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<cstdio>
#include<vector>
#define PB push_back
using namespace std;

int wynik, n, a[1000001];
char s[1000001];
const int ALF = 26;
int suma[ALF];
bool byloB[ALF];
bool startB[ALF];

int main() {
	scanf("%d", &n);
	scanf("%s", s);
	for (int p = 0; p < ALF; ++p) {
		for (int m = 0; m < ALF; ++m) {
			byloB[m] = false;
			startB[m] = false;
			suma[m] = 0;
		}
		for (int i = 0; i < n; ++i) {
			if (s[i] == p+'a') for (int m = 0; m < ALF; ++m) {
				++suma[m];
				if (byloB[m]) wynik = max(wynik, suma[m]);
			}
			else {
				int cur = s[i]-'a';
				byloB[cur] = true;
				if (startB[cur]) startB[cur] = false;
				else if (suma[cur] >= 0) --suma[cur];
				if (suma[cur] < 0) startB[cur] = true;
				if (byloB[cur]) wynik = max(wynik, suma[cur]);
			}
		}
	}
	printf("%d\n", wynik);
	return 0;
}
