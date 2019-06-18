#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;
 
int* res;
 
struct segtree{
    pi tree[4200000];
    void upload(int op, int p, int v){
        if(op == 1){
            tree[p].first = max(tree[p].first,v);
            tree[p].second = max(tree[p].second,v);
        }
        else{
            tree[p].first = min(tree[p].first,v);
            tree[p].second = min(tree[p].second,v);
        }
    }
    void insert(int s, int e, int p, int ps, int pe, int v, int op){
        if(pe < s || e < ps) return;
        if(s <= ps && pe <= e){
            upload(op,p,v);
            res[s] = tree[p].first;
        }
        else{
            upload(1,2*p,tree[p].first);
            upload(2,2*p,tree[p].second);
            upload(1,2*p+1,tree[p].first);
            upload(2,2*p+1,tree[p].second);
            tree[p].first = 0;
            tree[p].second = 1e5 + 5;
            int pm = (ps+pe)/2;
            insert(s,e,2*p,ps,pm,v,op);
            insert(s,e,2*p+1,pm+1,pe,v,op);
        }
    }
}seg;
 
void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
    res = finalHeight;
    for (int i=0; i<k; i++) {
        seg.insert(left[i],right[i],1,0,n-1,height[i],op[i]);
    }
    for (int i=0; i<n; i++) {
        seg.insert(i,i,1,0,n-1,0,1);
    }
}