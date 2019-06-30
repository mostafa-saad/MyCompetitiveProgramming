/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Jedynki (JED)                                 *
 *   Plik:                 jed4.cpp                                      *
 *   Autor:                Jakub Pachocki                                *
 *   Opis:                 Rozwiązanie alternatywne - krótkie.           *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *                                                                       *
 *************************************************************************/

#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

bool cmp(int a, int b) {
    return abs(a) < abs(b);
}

vector<int> normalize(vector<int> v) {
    sort(v.begin(), v.end(), cmp);
    v.push_back(2e9);
    vector<int> res;
    int count = 0;
    int prev = 0;
    bool negative = true;
    for (unsigned i = 0; i < v.size(); ++i) {
        while (abs(v[i]) != prev) {
            if (count % 2 != 0) {
                if (negative) {
                    res.push_back(-prev);
                    ++count;
                } else {
                    res.push_back(prev);
                    --count;
                }
                negative = !negative;
            }
            count /= 2;
            ++prev;
            if (count == 0)
                prev = abs(v[i]);
        }
        if (v[i] < 0)
            --count;
        else
            ++count;
    }
    return res;
}

int t[1000005];

int main() {
    vector<int> v;
    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i)
        scanf("%d", &t[i]);
    if (k == 1 && t[0] == 1) {
        printf("1\n1\n");
        return 0;
    }
    int l = 0;
    for (int i = k - 1; i >= 0; --i) {
        if (i % 2 == 0) {
            if (t[0] == 1) {
                v.push_back(l + t[i] + 1);
                v.push_back(-(l + 1));
            }
            v.push_back(l + t[i]);
            v.push_back(min(-l, -1));
        }
        l += t[i];
    }
    --l;
    int ad = l - (k + 1) / 2 + 1;
    if (t[0] > 1)
        v.push_back(l + 1);
    else {
        v.push_back(-l);
        --ad;
    }
    if (ad < 0)
        v.push_back(1);
    else {
        for (int i = 0; i < 30; ++i)
            if ((ad >> i) & 1)
                v.push_back(-i - 1);
    }
    v = normalize(v);
    vector<int> res;
    for (int i = v.size() - 1; i >= 1; i -= 2) {
        res.push_back(v[i] + v[i - 1]);
        if (i > 1)
            res.push_back(-v[i - 1] - v[i - 2]);
        else if (v[0] != -1)
            res.push_back(-v[0] - 1);
    }
    printf("%u\n", res.size());
    for (unsigned i = 0; i < res.size(); ++i)
        printf("%d ", res[i]);
    printf("\n");
}
