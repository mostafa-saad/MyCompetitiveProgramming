/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Gildie (GIL)                                              *
 *   Plik:     gil3.cpp                                                  *
 *   Autor:    Juliusz Sompolski                                         *
 *   Opis:     Rozwiazanie weryfikacyjne: zachlannie przydziela          *
 *             nieodwiedzonemu sasiadowi jedna gildie, a wszystkim jego  *
 *             sasiadom gildie przeciwna.                                *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <vector>
using namespace std;

int n,m;
vector<int> v[200000];
char c[200000];

int main() {
	/* Wczytuje dane */
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; i++) {
		int a,b;
		scanf("%d%d", &a,&b);
		v[a-1].push_back(b-1); v[b-1].push_back(a-1);
	}
	for(int i = 0; i < n; i++) if(c[i] == 0) {
		/* Nieprzerobiony wierzcholek */
		if(v[i].size() == 0) {
			/* Jesli izolowany wierzcholek, to odpowiedz nie */
			printf("NIE\n");
			return 0;
		}
		/* Przydziel wierzcholkowi jedna gildie, a wszystkim jego
		 * sasiadom gildie przeciwna */
		c[i] = 1;
		for(unsigned j = 0; j < v[i].size(); j++)
			c[v[i][j]] = 2;
	}
	/* Wypisanie odpowiedzi */
	printf("TAK\n");
	for(int i = 0; i < n; i++)
		printf("%c\n", c[i]==1?'K':'S');
	return 0;
}
