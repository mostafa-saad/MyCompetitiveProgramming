/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Patyczki                                         *
 *   Autor:             Alan Kutniewski                                  *
 *   Opis:              Rozwiazanie bardzo powolne                       *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#define INF 1000000001

using namespace std;

struct patyczek{
	int dl; //długość
	char kol; //kolor, nie ma sensu, żeby kol > 50, bo wtedy na pewno będie się dało zbudować trójkąt
}_p;

vector <patyczek> p; //vector trzymający patyczki
int n, k, m; //n - ilość patyczków, k - ilość kolorów, m - ilość patyczków w kolorze

void Solve(){ //sprawdzamy wszystkie możliwości
	for(int a = 0; a < n - 2; ++a){
		for(int b = a + 1; b < n - 1; ++b){
			for(int c = b + 1; c < n; ++c){
				if(p[a].kol != p[b].kol && p[a].kol != p[c].kol && p[b].kol != p[c].kol &&
				p[a].dl + p[b].dl > p[c].dl && p[a].dl + p[c].dl > p[b].dl && p[b].dl + p[c].dl > p[a].dl){
					cout << (int)p[a].kol << " " << p[a].dl << " ";
					cout << (int)p[b].kol << " " << p[b].dl << " ";
					cout << (int)p[c].kol << " " << p[c].dl << "\n";
					exit(0);
				}
			}
		}
	}
	cout << "NIE\n";
}

int main(){
	//Wczytywanie danych
	ios_base::sync_with_stdio(0);
	cin >> k;
	for(int i = 0;i < k; ++i){
		cin >> m;
		n += m;
		_p.kol = i + 1;
		for(int j = 0; j < m; ++j){
			cin >> _p.dl;
			p.push_back(_p);
		}
	}
	Solve();
	return 0;
} 
