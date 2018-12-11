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
    vector<int> ans;
    for (auto o : b) {
        vector<int> d(k, INF);
        for (auto s : a) {
            if (s.a < o.time && o.time <= s.b) {
                d[s.type] = min(d[s.type], abs(s.x - o.x));
            }
        }
        int cans = *max_element(d.begin(), d.end());
        if (cans == INF) cans = -1;
        ans.push_back(cans);
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