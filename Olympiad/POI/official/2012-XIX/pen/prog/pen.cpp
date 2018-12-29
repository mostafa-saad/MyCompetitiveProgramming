/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Pensje                                           *
 *   Autor:             Adam Karczmarz                                   *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie autorskie                            *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 1000010;
queue<int> K, P;
vector<int> kraw[MAXN];

struct drzewo {
    int id, a;
    drzewo (int _id = 0, int _a = 0) : id(_id), a(_a) {}
    int operator<(const drzewo &t) const {
        return a < t.a;
    }
};

int wielkosc(int v) {
    int res = 1;
    for (vector<int>::iterator it = kraw[v].begin(); it != kraw[v].end(); ++it) {
        res += wielkosc(*it);
    }
    return res;
}

int klucz[MAXN];

void dfs(int v, vector<int> *M) {
    klucz[v] = M->back(); M->pop_back();
    if (kraw[v].size() == 1)
        dfs(kraw[v].back(), M);
}

vector<drzewo> T;
bool nie_j[MAXN], us[MAXN];

int main(void) {
    int n; scanf("%d", &n);
    vector<int> ojciec;
    for (int v = 0; v < n; ++v) {
        int p, z; scanf("%d%d", &p, &z);
        --p; --z;
        ojciec.push_back(p);
        klucz[v] = z;
    }
    for (int v = 0; v < n; ++v) {
        int p = ojciec[v];
        if (p == v)
            klucz[p] = n - 1;
        if (klucz[v] != -1)
            continue;
        if (klucz[p] != -1)
            T.push_back(drzewo(v, klucz[p]));
        else
            kraw[p].push_back(v);
    }
    sort(T.begin(), T.end());
    for (int v = 0; v < n; ++v) {
        if (klucz[v] != -1)
            us[klucz[v]] = true;
    }
    for (int k = 0; k < n; ++k) {
        if (!us[k]) {
            K.push(k);
            P.push(k);
        }
    }
    for (vector<drzewo>::iterator it = T.begin(); it != T.end(); ++it) {
        drzewo Ti = *it;
        int S = wielkosc(Ti.id);
        vector<int> M;
        while (!K.empty() && K.front() < Ti.a && (int)M.size() < S) {
            M.push_back(K.front());
            K.pop();
        }
        bool niej = false;
        if (K.empty() || K.front() > Ti.a)
            dfs(Ti.id, &M);
        else
            niej = true;
        while (!P.empty() && P.front() < Ti.a) {
            if (niej)
                nie_j[P.front()] = true;
            P.pop();
        }
    }
    for (int v = 0; v < n; ++v) {
        printf("%d\n", (klucz[v] != -1 && !nie_j[klucz[v]]) ? klucz[v] + 1 : 0);
    }
    return 0;
}

