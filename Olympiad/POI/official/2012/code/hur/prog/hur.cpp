/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Hurtownia                                        *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n log n)                                       *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#define MAXN 250000
#define TS 262144

using namespace std;

struct sb{
    long long v;
    int pos;
    bool operator<(const sb& b) const{
        return v < b.v;
    }
}_sb;

long long a, tree[TS * 2], n;
sb b[MAXN];
vector <int> result;

//Standardowa zmiana wartosci w drzewie
void chTree(int pos, long long v){
    pos += TS;
    tree[pos] = v;
    pos /= 2;
    while(pos > 0){
        tree[pos] = tree[pos * 2] + tree[pos * 2 + 1];
        pos /= 2;
    }
}

//Zwraca sume do pozycji pos
long long sumTree(int pos){
    long long res = 0;
    pos += TS + 1;
    while(pos > 0){
        if(pos % 2){
            res += tree[pos - 1];
        }
        pos /= 2;
    }
    return res;
}

//Znajduje pierwsza na lewo niezerowa pozycje
int findNonZeroPos(int pos){
    long long oversum = sumTree(n) - sumTree(pos);
    pos =  1;
    while(pos < TS){
        pos *= 2;
        if(tree[pos + 1] > oversum)++pos;
        else oversum -= tree[pos + 1];
    }
    return pos;
}

//Usuwa oddane v paneli na pozycji pos
void rmTree(int pos, long long v){
    pos = findNonZeroPos(pos);
    while(v){
        long long av = min(tree[pos], v);
        chTree(pos - TS, tree[pos] - av);
        v -= av;
        pos = findNonZeroPos(pos - TS);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> a;
        chTree(i, a);
    }
    for(int i = 0; i < n; ++i){
        cin >> b[i].v;
        b[i].pos = i;
    }
    sort(b, b+n);
    for(int i = 0; i < n; ++i){
        if(sumTree(b[i].pos) >= b[i].v){
            if(b[i].v)rmTree(b[i].pos, b[i].v);
            result.push_back(b[i].pos + 1);
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

