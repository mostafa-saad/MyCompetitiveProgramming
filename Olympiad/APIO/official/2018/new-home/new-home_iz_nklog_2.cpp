#include <bits/stdc++.h>
using namespace std;
const int INF = (int)1.01e9;

void print(vector<int> v) {
    for (int x : v) printf("%d\n", x);
}

struct Shop {
    int x, type, a, b;
};

struct Query {
    int x, time;
};

struct fenwick {
    int n;
    vector<int> f;

    fenwick() {}

    fenwick(int N) {
        n = N;
        f.resize(n);
    }

    void add(int x, int y) {
        for (; x < n; x |= x + 1) f[x] += y;
    }

    int get(int x) {
        int res = 0;
        for (; x >= 0; x = (x & (x + 1)) - 1) res += f[x];
        return res;
    }

    int get(int l, int r) {
        return get(r) - get(l - 1);
    }

    // return min i: sum(0, i) > x
    int upper_bound(int x) {
        int k = 1;
        while (2 * k <= n) k *= 2;

        int res = 0;
        while (k > 0) {
            if (res + k - 1 < n && f[res + k - 1] <= x) {
                x -= f[res + k - 1];
                res += k;
            }
            k /= 2;
        }
        return res;
    }
};

vector<int> slow(vector<Shop> a, int k, vector<Query> b) {
    int n = a.size(), m = b.size();
    vector<int> ans(m);
    struct Event {
        int time, type, id;
        bool operator< (const Event &ev) const {
            return make_pair(time, -type) < make_pair(ev.time, -ev.type);
        }
    };
    vector<Event> events;
    for (int i = 0; i < (int)a.size(); i++) {
        events.push_back({ a[i].a, +1, i });
        events.push_back({ a[i].b, -1, i });
    }
    for (int i = 0; i < (int)b.size(); i++) {
        events.push_back({ b[i].time, 0, i });
    }
    sort(events.begin(), events.end());

    vector<int> sum(k);
    vector<vector<int>> vct(k);
    vector<fenwick> f(k);
    for (auto o : a) vct[o.type].push_back(o.x);
    for (int i = 0; i < k; i++) {
        sort(vct[i].begin(), vct[i].end());
        vct[i].resize(unique(vct[i].begin(), vct[i].end()) - vct[i].begin());
        f[i] = fenwick(vct[i].size());
    }

    auto lb2 = [&](int tp, int cx) {
        int id = lower_bound(vct[tp].begin(), vct[tp].end(), cx) - vct[tp].begin();
        int left = f[tp].get(id - 1);
        int ans2 = f[tp].upper_bound(left);
        int ans1 = left ? f[tp].upper_bound(left - 1) : -1;
        return make_pair(ans1, ans2);
    };
  

    int empty = k;
    for (auto ev : events) {        
        if (ev.type == +1) {
            int tp = a[ev.id].type;
            int id = lower_bound(vct[tp].begin(), vct[tp].end(), a[ev.id].x) - vct[tp].begin();
            empty -= sum[tp]++ == 0;
            f[tp].add(id, +1);
        }
        if (ev.type == 0) {
            int cur = 0;
            if (empty) cur = INF;
            for (int i = 0; i < k; i++) {
                int ccur = INF;
                auto o = lb2(i, b[ev.id].x);
                if (0 <= o.first && o.first < (int)vct[i].size()) ccur = min(ccur, abs(b[ev.id].x - vct[i][o.first]));
                if (0 <= o.second && o.second < (int)vct[i].size()) ccur = min(ccur, abs(b[ev.id].x - vct[i][o.second]));
                cur = max(cur, ccur);
                if (cur >= INF / 2) break;
            }
            if (cur >= INF / 2) cur = -1;
            ans[ev.id] = cur;
        }
        if (ev.type == -1) {
            int tp = a[ev.id].type;
            int id = lower_bound(vct[tp].begin(), vct[tp].end(), a[ev.id].x) - vct[tp].begin();
            f[tp].add(id, -1);
            empty += --sum[tp] == 0;
        }
    }
    return ans;
}

int main() {
    int n, k, q;
    scanf("%d%d%d", &n, &k, &q);
    vector<Shop> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d", &a[i].x, &a[i].type, &a[i].a, &a[i].b);
        a[i].type--;
    }
    vector<Query> b(q);
    for (int i = 0; i < q; i++) scanf("%d%d", &b[i].x, &b[i].time);

    print(slow(a, k, b));
}