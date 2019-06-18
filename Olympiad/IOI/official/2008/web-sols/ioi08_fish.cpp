#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
using namespace std;
typedef pair<int,int> pi;

int f,n,m;
vector<int> fish[500005];
int idx[500005];
int ridx[500005];

priority_queue<pi> del;

bool cmp(int a, int b){
    return fish[a].back() > fish[b].back();
}

struct idx{
    int tree[1050000], lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=0; i<2*lim; i++) tree[i] = 1;
    }
    void add(int x, int v){
        x += lim;
        tree[x] = v;
        while(x > 1){
            x >>= 1;
            tree[x] = tree[2*x] * tree[2*x+1] % m;
        }
    }
    int q(int s, int e){
        s += lim; e += lim;
        int r = 1;
        while(s < e){
            if(s%2 == 1) r = r * tree[s++] % m;
            if(e%2 == 0) r = r * tree[e--] % m;
            s >>= 1;
            e >>= 1;
        }
        if(s == e) r  = r * tree[s] % m;
        return r;
    }
}tree;

int t(int x, int y){
    return (int)(upper_bound(fish[y].begin(),fish[y].end(),fish[x].back()/2) - fish[y].begin());
}

int pt[500005];

void solve(){
    int res = 0;
    for (int i=1; i<=n; i++) {
        pt[i] = (int)fish[i].size();
    }
    for (int i=1; i<=n; i++) {
        tree.add(i,pt[idx[i]]%m + 1);
    }
    for (int i=1; i<=n; i++) {
        int lookup = fish[idx[i]].back() / 2;
        while (!del.empty()) {
            if(del.top().first > lookup){
                pt[del.top().second]--;
                tree.add(ridx[del.top().second],pt[del.top().second]%m + 1);
                del.pop();
            }
            else break;
        }
        int cnt = pt[idx[i]];
        int cnt2 = tree.q(i+1,n);
        int s = 1, e = i;
        while (s < e) {
            int m = (s+e)/2;
            if(t(idx[m],idx[i]) == cnt){
                e = m;
            }
            else s = m+1;
        }
        int cnt3 = tree.q(s,i-1);
        cnt %= m;
        res += cnt * cnt2 % m + cnt2 * cnt3 % m;
        res %= m;
    }
    printf("%d",res);
}

int main(){
    scanf("%d %d %d",&f,&n,&m);
    for (int i=0; i<f; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        del.push(pi(x,y));
        fish[y].push_back(x);
    }
    for (int i=1; i<=n; i++) {
        idx[i] = i;
        sort(fish[i].begin(),fish[i].end());
    }
    tree.init(n);
    sort(idx+1,idx+n+1,cmp);
    for (int i=1; i<=n; i++) {
        ridx[idx[i]] = i;
    }
    solve();
}

