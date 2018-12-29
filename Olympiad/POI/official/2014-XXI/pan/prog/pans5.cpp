/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Panele sloneczne                              *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n sqrt(m log m))                            *
 *   Zlozonosc pamieciowa: O(m)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

typedef long long LL;

const int M = 10 * 1000 * 1000;
const int T = 1000;

int dv[M + 1];

void sieve() {
    for(int i = 2; i <= M; i++) if(dv[i] == 0) {
            for(int j = i; j <= M; j += i) dv[j] = i;
        }
}

void get_dvs(int x, vector<int> &dvs) {
    vector<pair<int, int> > pdvs;
    for(; x != 1; x /= dv[x]) {
        int p = dv[x];
        if(!pdvs.empty() && pdvs.back().first == p) {
            pdvs.back().second++;
        } else {
            pdvs.push_back(make_pair(p, 1));
        }
    }
    vector<int> cnt(pdvs.size(), 0);
    size_t rgs = 0;
    int y = 1;
    while(true) {
        dvs.push_back(y);
        for(rgs = 0; rgs < cnt.size() && cnt[rgs] == pdvs[rgs].second; rgs++) {
            while(cnt[rgs] > 0) {
                cnt[rgs]--;
                y /= pdvs[rgs].first;
            }
        }
        if(rgs == cnt.size()) break;
        cnt[rgs]++;
        y *= pdvs[rgs].first;
    }
}

inline bool check(int d, int b, int e) {
    int q = (b - 1) / d + 1;
    return (LL)d * (LL)q <= (LL)e;
}

int krotki(int xb, int xe, int yb, int ye) {
    int maxd = 0;
    for(int i = xb; i <= xe; i++) {
        vector<int> dvs;
        get_dvs(i, dvs);
        for(int i = 0; i < (int)dvs.size(); i++) {
            int d = dvs[i];
            if(check(d, yb, ye)) maxd = max(maxd, d);
        }
    }
    return maxd;
}

inline pair<int, int> get_range(int b, int e, int d) {
    return make_pair((b - 1) / d + 1, e / d);
}

int dlugi(int xb, int xe, int yb, int ye) {
    int l = xe - xb + 1;
    int maxd = l;
    int q = xe / l;
    vector<pair<int, int> > rgs;
    for(int i = 1; i <= q; i++) {
        pair<int, int> range = get_range(xb, xe, i);
        if(!rgs.empty()) {
            range.second = min(range.second, rgs.back().first - 1);
        }
        if(range.first <= range.second) rgs.push_back(range);
    }
    reverse(rgs.begin(), rgs.end());
    q = ye / l;
    for(int i = 1; i <= q; i++) {
        pair<int, int> range = get_range(yb, ye, i), found;
        if(range.first > range.second) continue;
        while(!rgs.empty() && rgs.back().first > range.second)
            rgs.pop_back();
        if(rgs.empty()) break;

        if(rgs.back().second >= range.first) {
            maxd = max(maxd, min(rgs.back().second, range.second));
            return maxd;
        }
    }
    return maxd;
}

int main() {
    sieve();
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int xb, xe, yb, ye;
        scanf("%d%d%d%d", &xb, &xe, &yb, &ye);
        if(xe - xb > ye - yb) {
            swap(xb, yb);
            swap(xe, ye);
        } // teraz [xb, xe] jest krotszy
        int res;
        if(xe - xb < T) {
            res = krotki(xb, xe, yb, ye);
        } else {
            res = dlugi(xb, xe, yb, ye);
        }
        printf("%d\n", res);
    }
    return 0;
}
