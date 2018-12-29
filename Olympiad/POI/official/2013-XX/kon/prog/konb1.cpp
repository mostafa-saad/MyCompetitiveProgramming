/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Konewka                                       *
 *   Autor:                Michal Adamczyk                               *
 *   Zlozonosc czasowa:    O(q log q + n)                                *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Rozwiazanie zaklada, ze wszystkie wywolania   *
 *                         funkcji 'podlej' nastapia przed wywolaniami   *
 *                         funkcji 'dojrzale'.                           *
 *                                                                       *
 *************************************************************************/

#include <vector>
#include <algorithm>
using namespace std;

int N, K;
int t[300000];
int sp[300000];

vector<pair<int,int> > podlania;
bool obliczone;

void oblicz() {
    obliczone = true;
    sort(podlania.begin(), podlania.end());

    int s = 0;
    unsigned int ind = 0;
    for (int i = 0; i < N; ++i) {
        while(ind < podlania.size() && podlania[ind].first == i) {
            s += podlania[ind].second;
            ind++;
        }
        t[i] += s;
        sp[i] = (t[i] >= K) + (i > 0 ? sp[i-1] : 0);
    }
}

void inicjuj(int n, int k, int *D) {
    podlania.clear();
    N = n, K = k;
    for (int i = 0; i < n; ++i)
        t[i] = D[i];
    obliczone = false;
}

void podlej(int a, int b) {
    podlania.push_back(make_pair(a,1));
    podlania.push_back(make_pair(b+1,-1));
}

int dojrzale(int a, int b) {
    if(!obliczone) oblicz();

    if(a == 0) return sp[b];
    return sp[b] - sp[a-1];
}
