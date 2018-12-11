/*
 * Author: Geunwoo Bae(functionx)
 * Time Complexity: O(N^3)
 */
#include<stdio.h>
#include<algorithm>
#include<vector>
#define mod 1000000007
using namespace std;
 
typedef long long lld;
 
struct qry {
    int ix;
    lld x, pm;
    bool operator< (const qry& c) const {
        return x<c.x;
    }
}que[11010];
 
int n, chk[5050], act, qcn;
lld dy[5050], inv[5050];
 
void convolution(vector<lld>& x, vector<lld>& y, const int sz){
    int i, j;
    for(i=sz-1; i>=0; i--){
        lld sum=0;
        for(j=0; j<=i; j++){
            sum+=x[j]*y[i-j];
            sum%=mod;
        }
        x[i]=sum;
    }
}
 
lld pw(lld a, lld b){
    if(b<=0)return 1;
    lld g=pw(a,b/2);
    g=(g*g)%mod;
    if(b%2)g=(g*a)%mod;
    return g;
}
 
int main(){
    int i;
    lld pv;
    scanf("%d", &n);
    for(i=0; i<n; i++){
        lld s, e;
        scanf("%lld%lld", &s, &e);
        que[qcn].ix=i, que[qcn].x=s, que[qcn++].pm=1;
        que[qcn].ix=i, que[qcn].x=e+1, que[qcn++].pm=-1;
    }
    for(i=1; i<=n; i++)inv[i]=pw(i, mod-2);
    sort(que, que+qcn);
     
    pv=0;
    for(i=0; i<qcn; i++){
        if(pv<que[i].x && act){
            lld psum=-1, sum=0, mul=1;
            int j, ccn=0;
            vector <lld> p, q;
            for(j=0; j<n; j++){
                if(chk[j]){
                    lld arg = sum-psum+mod;
                    while(arg>=mod)arg-=mod;
                    mul *= (que[i].x-pv+ccn)*inv[ccn+1]%mod;
                    mul %= mod;
                    p.push_back(arg);
                    q.push_back(mul);
                    psum=sum;
                    ccn++;
                }
                sum += dy[j];
                if(sum >= mod)sum -= mod;
            }
            convolution(p, q, ccn);
            for(j=ccn=0; j<n; j++){
                if(chk[j]){
                    dy[j] += p[ccn];
                    if(dy[j] >= mod)dy[j] -= mod;
                    ccn++;
                }
            }
        }
/*      printf("%lld ~ %lld:\n", pv, que[i].x-1);
        for(int j=0; j<n; j++)printf("%lld ", dy[j]);
        puts("");*/
        pv = que[i].x;
        chk[que[i].ix] += que[i].pm, act += que[i].pm;
    }
     
    lld sum=0;
    for(i=0; i<n; i++){
        sum += dy[i];
        if(sum >= mod)sum -= mod;
    }
    printf("%lld", sum);
    return 0;
}