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
    vector<multiset<int>> st(k);

    int empty = k;
    for (auto ev : events) {        
        if (ev.type == +1) {
            int tp = a[ev.id].type;
            st[tp].insert(a[ev.id].x);
            empty -= sum[tp]++ == 0;
        }
        if (ev.type == 0) {
            int cur = 0;
            if (empty) cur = INF;
            for (int i = 0; i < k; i++) {
                int ccur = INF;
                auto it = st[i].lower_bound(b[ev.id].x);
                if (it != st[i].end()) ccur = min(ccur, abs(*it - b[ev.id].x));
                if (it != st[i].begin()) {
                    it--;
                    ccur = min(ccur, abs(*it - b[ev.id].x));
                }
                cur = max(cur, ccur);
                if (cur >= INF / 2) break;
            }
            if (cur >= INF / 2) cur = -1;
            ans[ev.id] = cur;
        }
        if (ev.type == -1) {
            int tp = a[ev.id].type;
            st[a[ev.id].type].erase(st[a[ev.id].type].find(a[ev.id].x));
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