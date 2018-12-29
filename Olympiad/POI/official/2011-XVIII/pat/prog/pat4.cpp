/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Patyczki                                         *
 *   Autor:             Miroslaw Michalski                               *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie weryfikujace                         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

inline bool triangle(const int a, const int b, const int c) {
    return (a + b > c && a + c > b && b + c > a);
}

inline bool diff(const int a, const int b, const int c) {
    return (a != b && a != c && b != c);
}

size_t n;

// zwraca element z pozycji >= pos tze jego kolor jest rowny 
// kolorowi pos
size_t analBlock(const vector<pair<int, int> >& v, size_t pos) {
    int currColor = v[pos].second;
    while (pos + 1 < n && v[pos + 1].second == currColor) {
        pos++;
    }
    return pos;
}

int main() {
    int k, il, x;
    vector<pair<int, int> > v;

    scanf("%d", &k);
    for(int c = 1; c <= k; c++) {
        scanf("%d", &il);
        for(int i = 0; i < il; i++) {
            scanf("%d", &x);
            v.push_back(make_pair(x, c));
        }
    }
    sort(v.begin(), v.end());
    n = v.size();
    v.push_back(make_pair(-1, -1));

    bool done = false;
    size_t pos = 0;
    while (!done) {
        size_t p1 = analBlock(v, pos);
        size_t p2 = analBlock(v, p1 + 1);
        size_t p3 = p2 + 1;
        pos = p2;
        if (p1 < n && p2 < n && p3 < n) {
            if (triangle(v[p1].first, v[p2].first, v[p3].first) && 
                    diff(v[p1].second, v[p2].second, v[p3].second)) {
                printf("%d %d %d %d %d %d\n", v[p1].second, v[p1].first, 
                        v[p2].second, v[p2].first, v[p3].second, v[p3].first);
                return 0;
            }
        } else {
            done = true;
        }
    }
    printf("NIE\n");
    return 0;
}

