#include <bits/stdc++.h>
using namespace std;
const int INF = (int)1.01e9;

void print(vector<int> v) {
    for (int x : v) printf("%d\n", x);
}

struct Segtree {
    int n, N;
    vector<int> t;

    Segtree(int _n) {
        n = _n;
        N = 1;
        while (N < n) N <<= 1;
        t.assign(2 * N, INF);
    }

    void upd(int x, int y) {
        x += N;
        t[x] = y;
        while (x > 1) {
            x >>= 1;
            t[x] = min(t[x * 2], t[x * 2 + 1]);
        }
    }

    int get(int l, int r) {
        int ans = INF;
        l += N; r += N;
        while (l <= r) {
            if (l & 1) ans = min(ans, t[l]);
            if (!(r & 1)) ans = min(ans, t[r]);
            l = (l + 1) >> 1;
            r = (r - 1) >> 1;
        }
        return ans;
    }
};

struct Shop {
    int x, type, a, b;
};

struct Query {
    int x, time;
};

vector<int> fast(vector<Shop> a, int k, vector<Query> b) {
    int n = a.size(), m = b.size();
    vector<int> ans(m, 0);
    for (auto &s : a) {
        s.a = s.a * 3;
        s.b = s.b * 3 + 2;
    }
    for (auto &o : b) o.time = o.time * 3 + 1;

    sort(a.begin(), a.end(), [&](const Shop &x, const Shop &y) {
        return x.type < y.type;
    });


    struct Event {
        int time, type, x;
        bool operator< (const Event &e) const {
            return time < e.time;
        }
    };

    struct Update {
        int t1, t2, x1, x2, val;
    };

    vector<Update> vct[2];
    vct[0].reserve(3 * n + k + 10);
    vct[1].reserve(3 * n + k + 10);

    auto addUpdate = [&](int t1, int t2, int l, int r) {
        if (t1 >= t2) return;
        int mid = l + (r - l) / 2;
        vct[0].push_back({ t1, t2, l, mid, l });
        vct[1].push_back({ t1, t2, -r, -(r - (r - l) / 2), -r });
    };

    int ci = 0;
    for (int c = 0; c < k; c++) {
        static multiset<pair<int, int>> st;
        st.clear();
        st.insert({ -INF, -1 });
        st.insert({ +INF, -1 });

        static vector<Event> events;
        events.clear();
        while (ci < n && a[ci].type == c) {
            auto o = a[ci++];
            events.push_back({ o.a, +1, o.x });
            events.push_back({ o.b, -1, o.x });
        }
        sort(events.begin(), events.end());

        for (auto ev : events) {
            if (ev.type == +1) {
                auto it = st.lower_bound({ ev.x, -1 });
                int rightX = it->first;
                int nTime = ev.time;
                if (rightX == ev.x) nTime = it->second;
                it--;
                int leftX = it->first;
                addUpdate(it->second, ev.time, leftX, rightX);
                st.erase(it);
                st.insert({ leftX, ev.time });
                st.insert({ ev.x, nTime });
            }
            else {
                auto it = st.lower_bound({ ev.x, -1 });
                int midX = it->first, midT = it->second;
                st.erase(it);
                it = st.lower_bound({ ev.x, -1 });
                addUpdate(midT, ev.time, midX, it->first);
                it--;
                int leftX = it->first;
                addUpdate(it->second, ev.time, leftX, midX);
                st.erase(it);
                st.insert({ leftX, ev.time });
            }
        }
        assert(st.size() == 2);
        addUpdate(st.begin()->second, INF, -INF, +INF);
    }

    vector<int> perB(m);
    iota(perB.begin(), perB.end(), 0);
    sort(perB.begin(), perB.end(), [&](int i, int j) {
        return b[i].x < b[j].x;
    });
    struct CEvent {
        int time, type, id;
        bool operator< (const CEvent &rhs) const {
            return time < rhs.time;
        }
    };
    vector<CEvent> events;
    events.reserve(m + vct[0].size() * 2);
    for (int i = 0; i < (int)vct[0].size(); i++) {
        events.push_back({ vct[0][i].t1, 1, i });
        events.push_back({ vct[0][i].t2, 2, i });
    }
    for (int i = 0; i < m; i++) events.push_back({ b[i].time, 0, i });
    sort(events.begin(), events.end());
    Segtree tr(vct[0].size());

    for (int ii = 0; ii < 2; ii++) {
        static vector<pair<int, int>> vv;
        vv.clear();
        for (int i = 0; i < (int)vct[ii].size(); i++) vv.push_back({ vct[ii][i].x2, i });

        sort(vv.begin(), vv.end());
        vector<int> lb1(vct[ii].size());
        for (int i = 0; i < (int)vv.size(); i++) lb1[vv[i].second] = i;
        vector<int> lb2(m);
        int ci = 0;
        for (int i = 0; i < m; i++) {
            while (ci < (int)vv.size() && vv[ci].first < b[perB[i]].x) ci++;
            lb2[perB[i]] = ci;
        }

        for (auto ev : events) {
            if (ev.type == 0) {
                int id = lb2[ev.id];
                ans[ev.id] = max(ans[ev.id], b[ev.id].x - tr.get(id, tr.n - 1));
            }
            if (ev.type == 1) {
                int id = lb1[ev.id];
                tr.upd(id, vct[ii][ev.id].x1);
            }
            if (ev.type == 2) {
                int id = lb1[ev.id];
                tr.upd(id, INF);
            }
        }

        for (auto &o : b) o.x *= -1;
        reverse(perB.begin(), perB.end());
    }

    for (int &x : ans) if (x >= INF / 2) x = -1;
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

    print(fast(a, k, b));
}