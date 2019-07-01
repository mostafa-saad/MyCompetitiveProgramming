/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Impreza                                          *
 *   Autor:             Alan Kutniewski                                  *
 *   Opis:              Rozwiazanie bledne                               *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 3000
 
using namespace std;

int value[MAXN]; //"wartość": ilość sąsiadów
bool kmatrix[MAXN][MAXN]; //macierz sąsiedztwa
vector<int> pol[MAXN]; //lista sąsiedztwa
vector<int> result; //"wynik"
int sor[MAXN]; //posortowani względem wartości
int n, m, a, b; //jak w treści
bool done; //czy mamy wynik?

bool cmp(int a, int b){
	return value[a] > value[b];
}

int main(){
	srand(time(NULL));
	ios_base::sync_with_stdio(0);
	cin >> n >> m; //wczytywanie danych
	for(int i = 0; i < n; ++i)sor[i] = i;
	for(int i = 0; i < m; ++i){
		cin >> a >> b;
		++value[a-1];
		++value[b-1];
		pol[a-1].push_back(b-1);
		pol[b-1].push_back(a-1);
		kmatrix[a-1][b-1] = kmatrix[b-1][a-1] = true;
	} 
	sort(sor, sor+n, cmp);
	for(int i = 0; i < n; ++i)sort(pol[i].begin(), pol[i].end(), cmp);
	for(int i = 0; i < n; ++i){
		result.clear();
		int act = sor[i];
		result.push_back(act);
		for(int j = 0; j < (int)pol[act].size(); ++j){
			if(value[pol[act][j]] < n/3)j = n;
			else{
				bool ok = true;
				for(int k = 0; k < (int)result.size(); ++k)if(!kmatrix[pol[act][j]][result[k]])ok = false;
				if(ok){
					result.push_back(pol[act][j]);
					if((int)result.size() == n/3){
						for(int l = 0; l < n/3; ++l)cout << result[l] + 1 << " ";
						cout << endl;
						return 0;
					}
				}
			}
		}
	}
	random_shuffle(sor, sor+n);
	for(int i = 0; i < n/3; ++i)cout << sor[i] + 1 << " ";
	cout << endl;
	return 0;
}
