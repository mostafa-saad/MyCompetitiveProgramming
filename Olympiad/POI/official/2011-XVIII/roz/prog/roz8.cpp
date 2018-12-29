/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Jacek Tomasiewicz                                *
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
	/* zapamietuje pozycje liter */
	for (int i = 0; i < n; ++i) {
		V[s[i]-'a'].push_back(i);
	}
	/* wrzucam straznikow */
	for (int p = 0; p < ALF; ++p) {
		V[p].push_back(n+1);
	}
	/* dla wszystkich fragmentow */
	for (int p = 0; p < ALF; ++p)  {
		for (int m = 0; m < ALF; ++m) {
			vector<int>::const_iterator it = V[p].begin(), jt=V[m].begin();
			/* scalam i znajduje pociag o najwiekszej sumie */
			int ile = V[p].size() + V[m].size() -2;
			int suma = 0, suma_pop = 0, mini = INF;
			for (int i = 0; i < ile; i++) {
				if (*it < *jt) {
					++suma; 
					++it;
				} else {
					--suma;
					mini = min(mini, suma_pop);
					suma_pop = suma;
					++jt;
				}
				wynik = max(wynik, suma-mini);
			}
		}
	}
	printf("%d\n", wynik);
	return 0;
}
