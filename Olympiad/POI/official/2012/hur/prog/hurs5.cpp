/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Hurtownia                                        *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(2^n)                                           *
 *   Opis:              Rozwiazanie powolne: wykladnicze                 *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#define MAXN 250000

using namespace std;

long long a[MAXN], b[MAXN];
int n;
vector <int> result;
vector <int> act;

void solve(int ind, long long sum){
    if(ind == n){
        if(act.size() > result.size()){
            result.clear();
            for(unsigned int i = 0; i < act.size(); ++i)result.push_back(act[i]);
        }
        return;
    }
    sum += a[ind];
    solve(ind + 1, sum);
    if(b[ind] <= sum){
        act.push_back(ind + 1);
        solve(ind + 1, sum - b[ind]);
        act.pop_back();
    }
    return;
}
        
int main(){
    ios_base::sync_with_stdio(0);
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> a[i];
    }
    for(int i = 0; i < n; ++i){
        cin >> b[i];
    }
    solve(0, 0ll);
    cout << result.size() << endl;
    for(unsigned i = 0; i < result.size(); ++i){
        cout << result[i] << " ";
    }
    cout << endl;
    return 0;
}

