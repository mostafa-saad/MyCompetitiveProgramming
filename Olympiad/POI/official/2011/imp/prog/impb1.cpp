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
#include <algorithm>
#define MAXN 3000
 
using namespace std;

int value[MAXN]; //"wartość": ilość sąsiadów
int res[MAXN]; //"wynik"
int n, m, a, b; //jak w treści
bool done; //czy mamy wynik?

bool cmp(int a, int b){
	return value[a] > value[b];
}

int main(){
	ios_base::sync_with_stdio(0);
	cin >> n >> m; //wczytywanie danych
	for(int i = 0; i < n; ++i)res[i] = i;
	for(int i = 0; i < m; ++i){
		cin >> a >> b;
		++value[a-1];
		++value[b-1];
	} 
	sort(res, res+n, cmp);
	for(int i = 0; i < (n/3); ++i)cout << res[i]+1 << " ";
	cout << endl;
	return 0;
}
