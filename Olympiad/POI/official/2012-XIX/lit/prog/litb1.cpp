/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Litery                                           *
 *   Autor:             Alan Kutniewski                                  *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Roznica pozycji kolejnych liter                  *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

#define llint long long int

using namespace std;

string jas, mal;
llint n, wynik;

vector <llint> pozj[256], pozm[256];

llint wbw(llint a){
    if(a < 0)return a * -1;
    return a;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin >> n;
    cin >> jas >> mal;
    for(llint i = 0; i < n; ++i){
        pozj[int(jas[i])].push_back(i);
        pozm[int(mal[i])].push_back(i);
    }
    for(int i = 'A'; i <= 'Z'; ++i){
        for(int j = 0; j < int(pozj[i].size()); ++j){
           wynik += wbw(pozj[i][j] - pozm[i][j]);
        }
    } 
    cout << wynik / 2 << endl;
    return 0;
}
