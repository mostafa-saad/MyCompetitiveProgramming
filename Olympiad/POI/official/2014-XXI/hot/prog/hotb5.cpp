/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Hotele                                        *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Zapominamy o odliczeniu sciezek z tego samego *
 *                         poddrzewa.                                    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>

using namespace std;

const int N = 5 * 1000;

vector<int> drz[N];

void dfs(int v, int p, vector<int> &wyn, unsigned int d) {
    if(wyn.size() < d + 1) {
        wyn.resize(d + 1, 0);
    }
    wyn[d]++;
    for(int i = 0; i < (int)drz[v].size(); i++) {
        if(drz[v][i] != p) {
            dfs(drz[v][i], v, wyn, d + 1);
        }
    }
}

vector< vector<int> > przeszukaj(int v) {
    vector< vector<int> > wyn(drz[v].size());
    for(int i = 0; i < (int)drz[v].size(); i++) {
        dfs(drz[v][i], v, wyn[i], 0);
    }
    return wyn;
}

void powieksz_wynik(vector< vector<int> > glebokosci, int &wyn) {
    vector<int> wszystkie;
    for(int i = 0; i < (int)glebokosci.size(); i++) {
        if(wszystkie.size() < glebokosci[i].size()) {
            wszystkie.resize(glebokosci[i].size(), 0);
        }
        for(int j = 0; j < (int)glebokosci[i].size(); j++) {
            wszystkie[j] += glebokosci[i][j];
        }
    }
    /*  for(int i = 0; i < (int)glebokosci.size(); i++) {
        for(int j = 0; j < (int)glebokosci[i].size(); j++) {
          long long ile = glebokosci[i][j];
          wyn -= ile * (ile - 1) * (wszystkie[j] - ile) / 2;
          wyn -= ile * (ile - 1) * (ile - 2) / 6;
        }
      } */
    for(int i = 0; i < (int)wszystkie.size(); i++) {
        long long ile = wszystkie[i];
        wyn += ile * (ile - 1) * (ile - 2) / 6;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--, b--;
        drz[a].push_back(b);
        drz[b].push_back(a);
    }
    int wyn = 0; // ZLE
    for(int i = 0; i < n; i++) {
        vector< vector<int> > glebokosci = przeszukaj(i);
        powieksz_wynik(glebokosci, wyn);
    }
    printf("%d\n", wyn);
    return 0;
}
