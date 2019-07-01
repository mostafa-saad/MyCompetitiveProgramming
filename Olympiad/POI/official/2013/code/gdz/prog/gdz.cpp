/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gdzie jest jedynka?                           *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(n lg n)                                     *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include "cgdzlib.h"

#include <utility>
using namespace std;

const int MAXN = 500000;

int q[MAXN];

pair<int, int> FindCandidates(int beg, int end, int d) {
    if (end - beg == 2) return make_pair(q[beg], q[beg+1]);

    // Partition
    int mid = beg + 1;
    for (int i = beg + 1; i < end; ++i)
        if (f(q[beg], q[i], d*2))
            swap(q[i], q[mid++]);

    // Wywolanie rekurencyjne
    if (mid - beg == end - mid) {
        pair<int, int> a = FindCandidates(beg, mid, d*2);
        int a1 = a.first, a2 = a.second;
        pair<int, int> b = FindCandidates(mid, end, d*2);
        int b1 = b.first, b2 = b.second;
        int delta = (end - beg - 1) * d;
        if (f(a1, b1, delta))
            return make_pair(a1, b1);
        else if (f(a1, b2, delta))
            return make_pair(a1, b2);
        else if (f(a2, b1, delta))
            return make_pair(a2, b1);
        else  // f(a2, b2, delta)
            return make_pair(a2, b2);
    } else if (mid - beg > end - mid) {
        return FindCandidates(beg, mid, d*2);
    } else {  // mid - beg < end - mid
        return FindCandidates(mid, end, d*2);
    }
}

int main() {
    int n = inicjuj();

    if (n == 1) odpowiedz(1);

    for (int i = 0; i < n; ++i) q[i] = i + 1;
    pair<int, int> cand = FindCandidates(0, n, 1);
    if (g(cand.first, cand.second) == 0)
        odpowiedz(cand.first);
    else
        odpowiedz(cand.second);
}
