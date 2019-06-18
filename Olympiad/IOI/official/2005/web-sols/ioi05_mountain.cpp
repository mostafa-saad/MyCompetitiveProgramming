#include <cstdio>
#include <algorithm>
using namespace std;
 
int n;
 
struct seg{
    long long sum[6000005], psum[6000005], lazy[6000005];
    bool lazysw[6000005];
    int ptl[6000005], ptr[6000005], sz;
    void init(){ sz = 1; }
    void lazydown(int p, int s, int e){
        if(!lazysw[p]) return;
        lazysw[p] = 0;
        if(s == e) return;
        int m = (s+e)/2;
        lazysw[ptl[p]] = 1;
        lazysw[ptr[p]] = 1;
        lazy[ptl[p]] = lazy[p];
        lazy[ptr[p]] = lazy[p];
        sum[ptl[p]] = lazy[p] * (m - s + 1);
        sum[ptr[p]] = lazy[p] * (e - m);
        psum[ptl[p]] = max(sum[ptl[p]],0ll);
        psum[ptr[p]] = max(sum[ptr[p]],0ll);
    }
    void add_node(int p){
        if(!ptl[p]) ptl[p] = ++sz;
        if(!ptr[p]) ptr[p] = ++sz;
    }
    void insert(int s, int e, int x, int ps, int pe, int p){
        if(pe < s || e < ps) return;
        if(s <= ps && pe <= e){
            lazysw[p] = 1;
            lazy[p] = x;
            sum[p] = 1ll * (pe - ps + 1) * x;
            psum[p] = max(sum[p],0ll);
            return;
        }
        int pm = (ps+pe)/2;
        add_node(p);
        lazydown(p,ps,pe);
        insert(s,e,x,ps,pm,ptl[p]);
        insert(s,e,x,pm+1,pe,ptr[p]);
        sum[p] = sum[ptl[p]] + sum[ptr[p]];
        psum[p] = max(psum[ptl[p]],sum[ptl[p]] + psum[ptr[p]]);
    }
    int query(long long x, int ps, int pe, int p){
        if(ps == pe) return ps;
        int pm = (ps+pe)/2;
        add_node(p);
        lazydown(p,ps,pe);
        if(psum[ptl[p]] > x){
            return query(x,ps,pm,ptl[p]);
        }
        else{
            return query(x-sum[ptl[p]],pm+1,pe,ptr[p]);
        }
    }
}seg;
 
int main(){
    seg.init();
    scanf("%d\n",&n);
    while (1) {
        char str[105];
        scanf("%s ",str);
        if(str[0] == 'E'){
            break;
        }
        if(str[0] == 'Q'){
            int p;
            scanf("%d",&p);
            if(seg.psum[1] <= p) printf("%d\n",n);
            else printf("%d\n",seg.query(p,1,n,1)-1);
        }
        if(str[0] == 'I'){
            int p,q,r;
            scanf("%d %d %d",&p,&q,&r);
            seg.insert(p,q,r,1,n,1);
        }
    }
}
