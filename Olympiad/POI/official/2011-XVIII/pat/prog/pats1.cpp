/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Patyczki                                         *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n * lg(n) + k^3 * n)                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#define INF 1000000001
#define MAXK 50

using namespace std;

vector <int> p[MAXK]; //vector trzymający patyczki
int n, k, m; //n - ilość patyczków, k - ilość kolorów, m - ilość patyczków w kolorze

void Solve(int a, int b, int c){ //Sprawdza, czy da się ułożyć trójkąt, gdy najdłuższy patyczek jest koloru a, krótszy b, a najkrótszy c
	int bi = -1, ci = -1; //ai, bi, ci - indeks a, b, c
	int as = p[a].size(), bs = p[b].size(), cs = p[c].size();
	for(int ai = 0; ai < as; ++ai){
		//zwiększamy bi
		while(bi + 1 < bs && p[b][bi + 1] <= p[a][ai])++bi;
		//zwiększamy ci
		while(ci + 1 < cs && p[c][ci + 1] <= p[b][bi])++ci;
		//sprawdzamy, czy tworzą trójkąt
		if(bi < 0 || ci < 0 || p[b][bi] > p[a][ai] || p[c][ci] > p[a][ai])continue;
		if(p[a][ai] < p[b][bi] + p[c][ci]){ //wystarczy to sprawdzenie, gdyż p[a][ai] jest najdłuższy
			cout << a + 1 << " " << p[a][ai] << " " << b + 1<< " " << p[b][bi] << " " << c + 1 << " " << p[c][ci] << endl;
			exit(0);//wypisujemy wynik i kończymy program
		}
	}
}

int main(){
	//Wczytywanie danych
	ios_base::sync_with_stdio(0);
	cin >> k;
	for(int i = 0; i < k; ++i){
		cin >> m;
		n += m;
		for(int j = 0; j < m; ++j){
			int adl;
			cin >> adl;
			p[i].push_back(adl);
		}
		sort(p[i].begin(), p[i].end());
	}
	for(int a = 0; a < k - 2; ++a){
		for(int b = a + 1; b < k - 1; ++b){
			for(int c = b + 1; c < k; ++c){
				//wybrane są trzy kolory a b i c
				Solve(a, b, c);
				Solve(a, c, b);
				Solve(b, a, c);
				Solve(b, c, a);
				Solve(c, a, b);
				Solve(c, b, a);
				//sprawdzone wszystkie sześć możliwości
			}
		}
	}
	cout << "NIE\n"; //jeśli Solve nie zakończył programu, to znaczy, że nie da się ułożyć trójkąta
	return 0;
} 
