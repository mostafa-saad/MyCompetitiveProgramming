#include "horses.h"
#include <algorithm>
#include <set>
using namespace std;
const int mod = 1e9 + 7;
typedef long long lint;
typedef pair<int,int> pi;
  
struct rmq{
    pi tree[1050000];
    int lim;
    void init(int n, int *a){
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=0; i<n; i++){
            tree[i + lim] = pi(a[i], i);
        }
        for(int i=lim-1; i; i--){
            tree[i] = max(tree[2*i], tree[2*i+1]);
        }
    }
    void upd(int x, int v){
        x += lim;
        tree[x] = pi(v, x - lim);
        while(x > 1){
            x >>= 1;
            tree[x] = max(tree[2*x], tree[2*x+1]);
        }
    }
    pi q(int s, int e){
        s += lim;
        e += lim;
        pi ret(0,0);
        while(s < e){
            if(s%2 == 1) ret = max(ret,tree[s++]);
            if(e%2 == 0) ret = max(ret,tree[e--]);
            s >>= 1;
            e >>= 1;
        }
        if(s == e) ret = max(ret,tree[s]);
        return ret;
    }
}rmq;
  
struct gob{
    lint tree[1050000], lim;
    void init(int n, int *a){
        for(lim = 1; lim <= n; lim <<= 1);
        fill(tree, tree + 2 * lim + 1, 1);
        for(int i=0; i<n; i++){
            tree[i + lim] = a[i];
        }
        for(int i=lim-1; i; i--){
            tree[i] = tree[2*i] * tree[2*i+1] % mod;
        }
    }
    void upd(int x, int v){
        x += lim;
        tree[x] = v;
        while(x > 1){
            x >>= 1;
            tree[x] = tree[2*x] * tree[2*x+1] % mod;
        }
    }
    int q(int s, int e){
        s += lim;
        e += lim;
        lint ret = 1;
        while(s < e){
            if(s%2 == 1) ret *= tree[s++], ret %= mod;
            if(e%2 == 0) ret *= tree[e--], ret %= mod;
            s >>= 1;
            e >>= 1;
        }
        if(s == e) ret *= tree[s], ret %= mod;
        return ret;
    }
}gob;
  
int n, x[500005], y[500005];
  
set<int> s;
  
int solve(){
    auto ite = --s.end();
    auto its = --s.end();
    its--;
    lint ret = -1;
    int retp = n;
    for(int i=0; i<32 && ite != s.begin(); i++){
        pi t = rmq.q(*its, *ite - 1);
        if(ret < t.first){
            retp = t.second;
            ret = t.first;
        }
        ret *= x[*its];
        if(ret > 2e9 || its == s.begin()) break;
        its--;
        ite--;
    }
    return 1ll * gob.q(0, retp) * y[retp] % mod;
}
  
int init(int N, int X[], int Y[]) {
    n = N;
    gob.init(N, X);
    rmq.init(N, Y);
    for(int i=0; i<N; i++){
        x[i] = X[i], y[i] = Y[i];
        if(X[i] != 1) s.insert(i);
    }
    s.insert(0);
    s.insert(N);
    return solve();
}
 
int updateX(int pos, int val) {
    if(x[pos] != 1){
        s.erase(pos);
        s.insert(0);
    }
    x[pos] = val;
    gob.upd(pos, val);
    if(x[pos] != 1){
        s.insert(pos);
    }
    return solve();
}
  
int updateY(int pos, int val) {
    rmq.upd(pos, val);
    y[pos] = val;
    return solve();
}