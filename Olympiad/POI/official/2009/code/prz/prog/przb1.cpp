/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     przb1.cpp                                                 *
 *   Autor:    Adam Gawarkiewicz                                         *
 *   Opis:     Rozwiazanie bledne. Porownuje kolejnosc pojawiania sie    *
 *             liczb z prawej i lewej strony ciagow                      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <set>
#include <vector>

using namespace std;

#define MAX_N 100000

int x[MAX_N], y[MAX_N];

int main() {
    int k;
    scanf("%d", &k);
    while (k--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++)
            scanf("%d", &x[i]);
        for (int i = 0; i < m; i++)
            scanf("%d", &y[i]);
        set<int> liczbyX, liczbyY;
        vector<int> kolejneX, kolejneY;
        for (int i = 0; i < n; i++)
            if (liczbyX.find(x[i])==liczbyX.end()) {
                kolejneX.push_back(x[i]);
                liczbyX.insert(x[i]);
            }
        for (int i = 0; i < m; i++)
            if (liczbyY.find(y[i])==liczbyY.end()) {
                kolejneY.push_back(y[i]);
                liczbyY.insert(y[i]);
            }
        if (kolejneX != kolejneY) {
            printf("0\n");
            continue;
        }
        liczbyX.clear();
        liczbyY.clear();
        kolejneX.clear();
        kolejneY.clear();
        for (int i = n-1; i >= 0; i--)
            if (liczbyX.find(x[i])==liczbyX.end()) {
                kolejneX.push_back(x[i]);
                liczbyX.insert(x[i]);
            }
        for (int i = m-1; i >= 0; i--)
            if (liczbyY.find(y[i])==liczbyY.end()) {
                kolejneY.push_back(y[i]);
                liczbyY.insert(y[i]);
            }
        if (kolejneX != kolejneY)
            printf("0\n");
        else
            printf("1\n");
    }
    return 0;
}
