#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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
    int x, t, a, b;
};

struct Query {
    int x, t;
};

vector<int> fast(vector<Shop> a, int k, vector<Query> b) {
    int n = a.size(), m = b.size();
    vector<int> ans(m, 0);
    for (auto &s : a) {
        s.a = s.a * 3;
        s.b = s.b * 3 + 2;
    }
    for (auto &o : b) o.t = o.t * 3 + 1;

    sort(a.begin(), a.end(), [&](const Shop &x, const Shop &y) {
        if (x.t != y.t) return x.t < y.t;
        return x.x < y.x;
    });

    struct Event {
        int time, type, id, x;
        bool operator< (const Event &e) const {
            if (time != e.time) return time < e.time;
            return type > e.type;
        }
    };

    struct Update {
        int t1, t2, x1, x2, val;
    };

    vector<Update> vct[2];

    auto addUpdate = [&](int t1, int t2, int l, int r) {
        if (t1 >= t2) return;
        int mid = l + (r - l) / 2;
        vct[0].push_back({ t1, t2, l, mid, l });
        if (mid < r) vct[1].push_back({ t1, t2, -r, -(mid + 1), -r });
    };

    int ci = 0;
    for (int c = 0; c < k; c++) {
        static multiset<pair<int, int>> st;
        st.clear();
        st.insert({ -INF, -1 });
        st.insert({ +INF, -1 });

        static vector<Event> events;
        events.clear();
        while (ci < n && a[ci].t == c) {
            auto o = a[ci++];
            events.push_back({ o.a, +1, o.t, o.x });
            events.push_back({ o.b, -1, o.t, o.x });
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

    for (int ii = 0; ii < 2; ii++) {
        struct CEvent {
            int t, type, id;
            bool operator< (const CEvent &rhs) const {
                return t < rhs.t;
            }
        };
        static vector<pair<int, int>> vv;
        vv.clear();
        static vector<CEvent> events;
        events.clear();
        for (int i = 0; i < (int)vct[ii].size(); i++) {
            vv.push_back({ vct[ii][i].x2, i });
            events.push_back({ vct[ii][i].t1, 1, i });
            events.push_back({ vct[ii][i].t2, 2, i });
        }
        for (int i = 0; i < m; i++) events.push_back({ b[i].t, 0, i });

        sort(vv.begin(), vv.end());
        Segtree tr(vv.size());
        sort(events.begin(), events.end());

        for (auto ev : events) {
            if (ev.type == 0) {
                int id = lower_bound(vv.begin(), vv.end(), make_pair(b[ev.id].x, -1)) - vv.begin();
                ans[ev.id] = max(ans[ev.id], b[ev.id].x - tr.get(id, tr.n - 1));
            }
            if (ev.type == 1) {
                int id = lower_bound(vv.begin(), vv.end(), make_pair(vct[ii][ev.id].x2, ev.id)) - vv.begin();
                tr.upd(id, vct[ii][ev.id].x1);
            }
            if (ev.type == 2) {
                int id = lower_bound(vv.begin(), vv.end(), make_pair(vct[ii][ev.id].x2, ev.id)) - vv.begin();
                tr.upd(id, INF);
            }
        }

        for (auto &o : b) o.x *= -1;
    }

    for (int &x : ans) if (x >= INF / 2) x = -1;
    return ans;
}

int main() {
    int n, k, q;
    scanf("%d%d%d", &n, &k, &q);
    vector<Shop> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d%d", &a[i].x, &a[i].t, &a[i].a, &a[i].b);
        a[i].t--;
    }
    vector<Query> b(q);
    for (int i = 0; i < q; i++) scanf("%d%d", &b[i].x, &b[i].t);

    print(fast(a, k, b));
}