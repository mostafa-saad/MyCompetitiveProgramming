/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Hurtownia                                        *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie powolne: programowanie dynamiczne    *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#define MAXN 1000 // dla wiecej pamieci nie starczy
#define MINF -9000000000000000000ll

using namespace std;

long long a[MAXN], b[MAXN];
long long t[MAXN][MAXN + 1];
bool from[MAXN][MAXN];
int n;

int main(){
    ios_base::sync_with_stdio(0);
    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> a[i];
    }
    for(int i = 0; i < n; ++i){
        cin >> b[i];
    }
    t[0][0] = a[0];
    for(int i = 0; i < n; ++i){
        t[i][0] = t[i - 1][0] + a[i];
    }
    if(a[0] >= b[0]) t[0][1] = a[0] - b[0];
    else t[0][1] = MINF;
    from[0][1] = true;
    for(int i = 2; i <= n; ++i){
        t[0][i] = MINF;
    }
    for(int i = 1; i < n; ++i){
        for(int j = 1; j <= n; ++j){
            if(t[i - 1][j - 1] + a[i] >= b[i]){
                if(t[i - 1][j] + a[i] < t[i - 1][j - 1] + a[i] - b[i])from[i][j] = true;
                t[i][j] = max(t[i - 1][j] + a[i], t[i - 1][j - 1] + a[i] - b[i]);
            }
            else
                t[i][j] = t[i - 1][j] + a[i];
        }
    }
    int result = -1;
    for(int i = 0; i <= n; ++i){
        if(t[n - 1][i] >= 0)result = i;
    }
    vector <int> vresult;
    int i = n - 1, j = result;
    while(j){
        if(from[i][j]){
            vresult.push_back(i + 1);
            --j;
        }
        --i;
    }
    cout << vresult.size() << endl;
    for(unsigned int i = 0; i < vresult.size(); ++i){
        cout << vresult[vresult.size() - 1 - i] << " " ;
    }
    cout << endl;
    return 0;
}

