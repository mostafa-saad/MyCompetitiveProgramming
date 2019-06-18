#include <cstdio>
 
int n,s,t[10005],g[10005],dp[10005];
int la[10005], lb[10005], piv, sz;
 
double cross(int p, int q){return (double)(lb[q]-lb[p])/(la[p]-la[q]);}
 
void insert(int p, int q){
    la[sz] = p;
    lb[sz] = q;
    while (sz>1 && cross(sz-2,sz-1) > cross(sz-1,sz)) {
        la[sz-1] = la[sz];
        lb[sz-1] = lb[sz];
        sz--;
    }
    sz++;
}
 
int query(int x){
    while(piv+1 < sz && cross(piv,piv+1) < x) piv++;
    return la[piv] * x + lb[piv];
}
 
int main(){
    int x,y;
    scanf("%d %d",&n,&s);
    for (int i=1; i<=n; i++) {
        scanf("%d %d",&x,&y);
        t[i] = t[i-1] + x;
        g[i] = g[i-1] + y;
    }
    insert(s + t[n], 0);
    for (int i=n; i>=1; i--) {
        dp[i] = query(g[n] - g[i-1]) - t[i-1] * (g[n] - g[i-1]);
        insert(s + t[i-1] , dp[i]);
    }
    printf("%d",dp[1]);
}