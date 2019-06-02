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

char s[1000001];
const int INF = 1000 * 1000 * 1000;
const int ALF = 26;
vector<int> V[ALF];

int main() {
	int wynik = 0, n;
	scanf("%d", &n);
	scanf("%s", s);
	for (int i = 0; i < n; ++i) {
		V[s[i]-'a'].push_back(i);
	}
	for (int p = 0; p < ALF; ++p) {
		V[p].push_back(n+1);
	}
	for (int p = 0; p < ALF; ++p)  {
		for (int m = 0; m < ALF; ++m) {
			vector<int>::const_iterator it = V[p].begin(), jt=V[m].begin();
			int ile = V[p].size() + V[m].size() -2;
			int suma = 0;
			bool byloB = false, startB = false;
			for (int i = 0; i < ile; i++) {
				if (*it < *jt) {
					++suma; 
					++it;
				} else {
					byloB = true;
					if (startB) startB = false;
					else if (suma >= 0) --suma;
					if (suma < 0) startB = true;;
					++jt;
				}
				if (byloB) wynik = max(wynik, suma);
			}
		}
	}
	printf("%d\n", wynik);
	return 0;
}
