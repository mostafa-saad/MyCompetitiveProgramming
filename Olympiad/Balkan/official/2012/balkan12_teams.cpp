#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int,int> pi;
typedef long long lint;
 
struct query{int ac, sc, idx;};
 
int n, q;
pi a[300005];
query qry[300005];
 
vector<int> v;
int stv[300005];
lint ret[300005];
 
struct node{
    lint val;
    int cnt;
};
 
node operator+(node a, node b){
    return (node){a.val + b.val, a.cnt + b.cnt};
}
 
bool operator<(node a, node b){
    if(a.val != b.val) return a.val < b.val;
    return a.cnt > b.cnt;
}
 
bool operator>(node a, node b){
    return !(a < b);
}
 
struct node2{
    node x, l, r, lr;
};
 
node2 nadd(node2 a, node2 b){
    node2 c;
    c.x = max(a.r + b.x, a.x + b.l);
    c.l = max(a.lr + b.x, a.l + b.l);
    c.r = max(a.r + b.r, a.x + b.lr);
    c.lr = max(a.lr + b.r, a.l + b.lr);
    c.l = max(c.l, c.lr);
    c.r = max(c.r, c.lr);
    c.x = max(c.x, max(c.l, c.r));
    return c;
}
 
struct seg{
    node2 tree[1050000];
    void add(int pos, int ps, int pe, int p, int val){
        if(ps == pe){
            tree[p].x = {v[val],1};
            return;
        }
        int pm = (ps + pe) / 2;
        if(pos <= pm) add(pos,ps,pm,2*p,val);
        else add(pos,pm+1,pe,2*p+1,val);
        tree[p] = nadd(tree[2*p], tree[2*p+1]);
    }
    lint query(int p, int ps, int pe, int k, node2 n){
        if(ps == pe){
            if(nadd(tree[p], n).x.cnt > k) return n.x.val;
            return nadd(tree[p], n).x.val;
        }
        node2 t = nadd(tree[2*p+1], n);
        int pm = (ps + pe) / 2;
        if(t.x.cnt > k){
            return query(2*p+1, pm+1, pe, k, n);
        }
        else{
            return query(2*p, ps, pm, k, t);
        }
    }
}seg;
 
bool cmp(query a, query b){return a.ac < b.ac;}
 
int main(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d %d",&a[i].first,&a[i].second);
        v.push_back(a[i].second);
    }
    sort(v.begin(), v.end());
    for(int i=0; i<n; i++){
        a[i].second = (int)(lower_bound(v.begin(), v.end(), a[i].second) - v.begin());
    }
    sort(a,a+n);
    scanf("%d",&q);
    for(int i=0; i<q; i++){
        scanf("%d %d",&qry[i].ac, &qry[i].sc);
        qry[i].idx = i;
    }
    sort(qry,qry+q,cmp);
    int p = 0;
    for(int i=0; i<q; i++){
        while(p < n && a[p].first <= qry[i].ac){
            seg.add(a[p].second,0,n-1,1,a[p].second);
            p++;
        }
        node2 t;
        t.x = t.l = t.r = t.lr = {0,0};
        ret[qry[i].idx] = seg.query(1,0,n-1,qry[i].sc,t);
    }
    for(int i=0; i<q; i++){
        printf("%lld\n",ret[i]);
    }
}