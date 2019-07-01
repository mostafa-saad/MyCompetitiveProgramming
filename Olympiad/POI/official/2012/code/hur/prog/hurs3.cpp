/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Hurtownia                                        *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie powolne: algorytm zachlanny          *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#define MAXN 250000

using namespace std;

struct sb{
    long long v;
    int pos;
    bool operator<(const sb& b) const{
        return v < b.v;
    }
}b[MAXN];

long long a[MAXN], sum[MAXN];
int n;
vector <int> result;

void remakeSum(){
    sum[0] = a[0];
    for(int i = 1; i < n; ++i){
        sum[i] = sum[i - 1] + a[i];
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> a[i];
    }
    for(int i = 0; i < n; ++i){
        cin >> b[i].v;
        b[i].pos = i;
    }
    remakeSum();
    sort(b, b+n);
    for(int i = 0; i < n; ++i){
        if(sum[b[i].pos] >= b[i].v){
            result.push_back(b[i].pos + 1);
            int it = b[i].pos;
            long long vl = b[i].v;
            while(vl){
                long long mv = min(vl, a[it]);
                a[it] -= mv;
                vl -= mv;
                --it;
            }
            remakeSum();
        }
    }
    sort(result.begin(), result.end());
    cout << result.size() << endl;
    for(unsigned i = 0; i < result.size(); ++i){
        cout << result[i] << " ";
    }
    cout << endl;
    return 0;
}

