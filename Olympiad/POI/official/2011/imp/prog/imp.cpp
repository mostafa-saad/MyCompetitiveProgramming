/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Impreza                                          *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#define MAXN 3000
 
using namespace std;

bool kmatrix[MAXN][MAXN]; //macierz sąsiedztwa
bool erased[MAXN]; //czy usunięty?
int n, m, a, b; //jak w treści

int main(){
	ios_base::sync_with_stdio(0);
	cin >> n >> m; //wczytywanie danych
	for(int i = 0; i < m; ++i){
		cin >> a >> b;
		kmatrix[a-1][b-1] = kmatrix[b-1][a-1] = 1;
	} //usuwanie nieznających się par
	for(int i = 0; i < n; ++i){
		for(int j = i + 1; j < n && !erased[i]; ++j){ //dopóki i nieusunięty
			if(!kmatrix[i][j] && !erased[j]){ //jeśli i nie zna j i j nieusunięty
				erased[i] = 1; //to usuwamy i oraz j
				erased[j] = 1;
			}
		}
	}
	int left = (n/3); //ile zostało do wypisania
	for(int i = 0; left && i < n; ++i){
		if(!erased[i]){ //jeśli nie usunęliśmy i
			--left; //to wypisujemy i zmniejszamy ilość
			cout << i+1 << " ";
		}
	}
	cout << endl;
	return 0;
}
