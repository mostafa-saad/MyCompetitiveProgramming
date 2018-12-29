/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Patyczki                                         *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie wzorcowe wariant 2                   *
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
bool operator<(const patyczek &a, const patyczek &b){
	if(a.dl != b.dl)return a.dl < b.dl;
	return a.kol < b.kol;
}

vector <patyczek> p; //vector trzymający patyczki
int n, k, m; //n - ilość patyczków, k - ilość kolorów, m - ilość patyczków w kolorze
patyczek np[3]; //trzy najlepsze patyczki

void sprawdz(int i){ //sprawdza, czy można zbudować trójkąt z np i p[i]
	int p1, p2;
	p1 = 1;
	p2 = 2; //są to dwa najdłuższe patyczki z np
	if(np[1].kol == p[i].kol)p1 = 0; //jeśli któryś jest tego samego koloru co p[i] to musimy wziąć np[0]
	if(np[2].kol == p[i].kol)p2 = 0;
	if(np[p1].dl + np[p2].dl > p[i].dl){
		cout << (int)p[i].kol << " " << p[i].dl << " " << (int)np[p1].kol << " " << np[p1].dl << " " << (int)np[p2].kol << " " << np[p2].dl << endl;
		exit(0);
	}
}
void popraw(int i){ //poprawia trzy najlepsze patyczki
	int pw = 0;
	if(np[1].kol == p[i].kol)pw = 1;
	if(np[2].kol == p[i].kol)pw = 2;
	np[pw] = p[i];
	sort(np, np+3);
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
	sort(p.begin(), p.end()); //sortujemy patyczki po długości
	for(int i = 0; i < 3; ++i){
		np[i].kol = -i;
		np[i].dl = -INF;
	}
	//Algorytm właściwy
	for(int i = 0; i < n; ++i){
		sprawdz(i);
		popraw(i);
	}
	cout << "NIE\n";
	return 0;
} 
