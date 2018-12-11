/*
 * Author: Geunwoo Bae(functionx)
 * Time Complexity: O(N^2 lg N)
 */
#include<stdio.h>
#include<cmath>
#include<complex>
#include<algorithm>
#include<vector>
#define mod 1000000007
using namespace std;
 
typedef long long lld;
typedef complex<double> base;
 
struct qry {
    int ix;
    lld x, pm;
    bool operator< (const qry& c) const {
        return x<c.x;
    }
}que[11010];
 
int n, chk[5050], act, qcn;
lld dy[5050], inv[5050];
 
void fft(vector <base> &a, bool invert){
    int n = a.size();
    for(int i=1,j=0; i<n; i++){
        int bit = n>>1;
        for(; j>=bit; bit>>=1)j -= bit;
        j += bit;
        if(i<j)swap(a[i], a[j]);
    }
    for(int len=2; len<=n; len<<=1){
        double ang = 2*M_PI/len*(invert?-1:1);
        base wlen(cos(ang), sin(ang));
        for(int i=0; i<n; i+=len){
            base w(1);
            for(int j=0; j<len/2; j++){
                base u=a[i+j], v=a[i+j+len/2]*w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= wlen;
            }
        }
    }
    if(invert){
        for(int i=0; i<n; i++)a[i] /= n;
    }
}
 
void convolution(vector<lld>& x, vector<lld>& y, const int sz){
    vector<base> fa1, fa2, fb1, fb2;
    int n, i;
    for(n=1; n<sz; n<<=1);
    for(i=0; i<n; i++){
        fa1.push_back(0), fa2.push_back(0);
        fb1.push_back(0), fb2.push_back(0);
    }
    for(i=0; i<sz; i++){
        fa1.push_back(x[i]/30000), fa2.push_back(x[i]%30000);
        fb1.push_back(y[i]/30000), fb2.push_back(y[i]%30000);
    }
    n<<=1;
    fa1.resize(n), fa2.resize(n);
    fb1.resize(n), fb2.resize(n);
    fft(fa1, 0), fft(fa2, 0);
    fft(fb1, 0), fft(fb2, 0);
    for(i=0; i<n; i++){
        base a1b1 = fa1[i]*fb1[i], a1b2 = fa1[i]*fb2[i];
        base a2b1 = fa2[i]*fb1[i], a2b2 = fa2[i]*fb2[i];
        fa1[i] = a1b1, fa2[i] = a1b2, fb1[i] = a2b1, fb2[i] = a2b2;
    }
    fft(fa1, 1), fft(fa2, 1);
    fft(fb1, 1), fft(fb2, 1);
    for(i=0; i<sz; i++){
        lld a1b1, a1b2, a2b1, a2b2;
        a1b1 = lld(fa1[i].real() + (fa1[i].real()>0 ? 0.5:-0.5)), a1b1%=mod;
        a1b2 = lld(fa2[i].real() + (fa2[i].real()>0 ? 0.5:-0.5)), a1b2%=mod;
        a2b1 = lld(fb1[i].real() + (fb1[i].real()>0 ? 0.5:-0.5)), a2b1%=mod;
        a2b2 = lld(fb2[i].real() + (fb2[i].real()>0 ? 0.5:-0.5)), a2b2%=mod;
        x[i] = (a1b1*900000000ll + (a1b2+a2b1)*30000ll + a2b2)%mod;
    }
}
 
/*
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
}*/
 
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