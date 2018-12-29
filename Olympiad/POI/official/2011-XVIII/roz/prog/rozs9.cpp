/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Roznica                                          *
 *   Autor:             Jacek Tomasiewicz                                *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************/

#include<iostream>
using namespace std;

string s;
const int INF = 1000 * 1000 * 1000;

int main() {
	int n, wynik = 0;
	cin >> n ;
	cin >> s;
	for (char plus='a'; plus <= 'z'; plus++) 
		for (char minus='a'; minus <= 'z'; minus++) {
			int mini = INF;
			int suma = 0;
			int suma_pop = 0;
			for (int i=0; i<n; i++) {
				if (s[i] == plus) {
					++suma;
					wynik = max(wynik, suma - mini);
				} else if (s[i] == minus) {
					--suma;
					mini = min(mini, suma_pop);
					suma_pop = suma;
					wynik = max(wynik, suma - mini);
				}  
			}
		}
		cout << wynik << endl;
		return 0;
}
