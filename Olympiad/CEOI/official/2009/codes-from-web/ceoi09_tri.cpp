#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
  
int ccw(pi a, pi b, pi c){
    int dx1 = b.first - a.first;
    int dy1 = b.second - a.second;
    int dx2 = c.first - a.first;
    int dy2 = c.second - a.second;
    lint tmp = 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
    if(tmp > 0) return 1;
    if(tmp == 0) return 0;
    return -1;
}
  
struct seg{
    vector<pi> tree[270000];
    int lim;
    void init(int n, pi *a){
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=0; i<n; i++){
            tree[i+lim].push_back(a[i]);
            int p = i + lim;
            while(p > 1){
                p >>= 1;
                tree[p].push_back(a[i]);
            }
        }
        for(int i=1; i<2*lim; i++){
            vector<pi> tstk;
            for(auto &j : tree[i]){
                while(tstk.size() >= 2 && ccw(tstk[tstk.size()-2], tstk.back(), j) >= 0){
                    tstk.pop_back();
                }
                tstk.push_back(j);
            }
            tree[i] = tstk;
        }
    }   
    bool inside(int p, pi st, pi ed){
        if(tree[p].empty()) return 0;
        auto func = [&](pi x){
            int a = -ed.second + st.second;
            int b = ed.first - st.first;
            return 1ll * a * x.first + 1ll * b * x.second;
        };
        int s = 0, e = tree[p].size() - 1;
        while(s != e){
            int m = (s+e)/2;
            if(func(tree[p][m]) >= func(tree[p][m+1])) e = m;
            else s = m+1;
        }
        return ccw(st, ed, tree[p][s]) > 0;
    }
    bool query(int s, int e, pi st, pi ed){
        s += lim;
        e += lim;
        while(s < e){
            if(s%2 == 1 && inside(s++, st, ed)) return 1;
            if(e%2 == 0 && inside(e--, st, ed)) return 1;
            s >>= 1;
            e >>= 1;
        }
        if(s == e && inside(s, st, ed)) return 1;
        return 0;
    }
}seg;
  
int n, q;
pi a[100005];
  
int main(){
    scanf("%d %d",&n,&q);
    for(int i=0; i<n; i++){
        scanf("%d %d",&a[i].first, &a[i].second);
    }
    auto cmp = [&](const pi &a, const pi &b){
        int t = ccw(pi(0, 0), a, b);
        if(t == 0) return a.first < b.first;
        return t > 0;
    };
    sort(a, a+n, cmp);
    seg.init(n, a);
    while(q--){
        pi st, ed;
        scanf("%d %d %d %d",&st.first, &st.second, &ed.first, &ed.second);
        if(ccw(pi(0, 0), st, ed) < 0){
            swap(st, ed);
        }
        int ps = lower_bound(a, a+n, st, cmp) - a;
        int pe = upper_bound(a, a+n, ed, cmp) - a - 1;
        puts(seg.query(ps, pe, st, ed) ? "Y" : "N");
    }
}