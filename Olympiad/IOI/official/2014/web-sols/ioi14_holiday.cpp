#include"holiday.h"
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long lint;
typedef pair<int, lint> pi;
 
priority_queue<int, vector<int>, greater<int> > pq;
 
lint ret;
int *a, st, dist;
pi value[100005];
 
struct range_tree{
    vector<pi> tree[270000]; // [pos, attraction]
    int lim;
    void init(int n, pi *a){
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=0; i<n; i++){
            int pos = i + lim;
            while(pos){
                tree[pos].push_back(a[i]);
                pos >>= 1;
            }
        }
        for(int i=lim-1; i; i--){
            sort(tree[i].begin(), tree[i].end());
            for(int j=1; j<tree[i].size(); j++){
                tree[i][j].second += tree[i][j-1].second;
            }
        }
    }
    pi count(int nd, int s, int e){
        pi ret(0,0);
        int stp = (int)(lower_bound(tree[nd].begin(), tree[nd].end(), pi(s, -1)) - tree[nd].begin());
        int edp = (int)(lower_bound(tree[nd].begin(), tree[nd].end(), pi(e+1, -1)) - tree[nd].begin());
        ret.first += edp - stp;
        ret.second += (edp ? tree[nd][edp - 1].second : 0) - (stp ? tree[nd][stp - 1].second : 0);
        return ret;
    }
    lint query(int s, int e, int x){
        x++;
        int pos = 1;
        lint ret = 0;
        while(pos <= lim){
            pi t = count(2*pos, s, e);
            if(x <= t.first) pos = 2 * pos;
            else{
                x -= t.first;
                ret += t.second;
                pos = 2 * pos + 1;
            }
        }
        return ret;
    }
}rtree;
 
void divConq(int s, int e, int rs, int re){
    if(s > e) return;
    int m = (s+e)/2;
    lint copt = 0, cres = -1;
    int opt = rs;
    for(int i=rs; i<=re; i++){
        int cnt = dist - (i - m + min(i - st, st - m));
        if(cnt <= 0) break;
        copt = rtree.query(m, i, min(cnt, i - m + 1));
        if(cres < copt){
            cres = copt;
            opt = i;
        }
    }
    ret = max(ret, cres);
    divConq(s,m-1,rs,opt);
    divConq(m+1,e,opt,re);
}
 
long long int findMaxAttraction(int n, int start, int d, int attraction[]) {
    a = attraction;
    for(int i=0; i<n; i++){
        value[i] = pi(i, attraction[i]);
    }
    sort(value, value + n, [&](const pi &a, const pi &b){return a.second > b.second;});
    rtree.init(n,value);
    st = start;
    dist = d;
    divConq(0, start, start, n-1);
    return ret;
}