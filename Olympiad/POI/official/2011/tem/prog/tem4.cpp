/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Temperatura                                      *
 *   Autor:             Maciej Andrejczuk                                *
 *   Opis:              Rozwiazanie alternatywne                         *
 *   Zlozonosc czasowa: O(n)                                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <deque>

using namespace std;

typedef pair<int, int> PII;
#define FI first
#define SE second
deque<PII> q;

int main() {
    int n;
    int pp = scanf("%d", &n);
    int ret = 0;
    for (int i = 0; i < n; i++) {
        int a, b;
        pp = scanf("%d %d", &a, &b);
        while (!q.empty() && q.front().FI > b) {
            int ile = i - q.front().SE;
            ret = max(ret, ile);
            q.pop_front();
        }
        int pocz = i;
        while (!q.empty() && q.back().FI <= a) {
            pocz = q.back().SE;
            q.pop_back();
        }
        q.push_back(PII(a, pocz));
    }
    if (!q.empty()) {
        int ile = n - q.front().SE;
        ret = max(ret, ile);
    }
    printf("%d\n", ret);
}

