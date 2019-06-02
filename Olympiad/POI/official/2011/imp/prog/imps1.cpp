/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Impreza                                          *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n * 2^n)                                       *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#define MAXN 3000
 
using namespace std;

bool kmatrix[MAXN][MAXN]; //macierz sąsiedztwa
bool used[MAXN]; //czy użyty?
int n, m, a, b; //jak w treści
bool done; //czy mamy wynik?

void Find(int act, int left){ //rekurencyjny backtracking
	if(done)return;
	if(left == 0){ //jeśli mamy n/3 wybranych to je wypisujemy
		for(int i = 0; i < n; ++i){
			if(used[i])cout << i+1 << " ";
		}
		cout << endl;
		done = 1;
	}
	if(act >= n)return;
	bool cb = 1;
	for(int i = 0; i < act && cb; ++i){ //sprawdzamy, czy mając wybrane, można dodać act
		if(used[i] && !kmatrix[i][act])cb = 0;
	}
	if(cb){
		used[act] = 1;
		Find(act + 1, left - 1); //jeśli tak, to próbujemy dodać
		used[act] = 0;
	}
	Find(act + 1, left); //jak się nie udało to nie dodajemy
}

int main(){
	ios_base::sync_with_stdio(0);
	cin >> n >> m; //wczytywanie danych
	for(int i = 0; i < m; ++i){
		cin >> a >> b;
		kmatrix[a-1][b-1] = kmatrix[b-1][a-1] = 1;
	} 
	Find(0, (n / 3));
	return 0;
}
