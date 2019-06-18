#include <cstdio>
#include <algorithm>
using namespace std;
 
struct bit{
    int tree[131073], lim;
    void add(int x, int v){
        while(x <= lim){
            tree[x] += v;
            x += x & -x;
        }
    }
    int lbnd(int x){
        int p = 0;
        for(int i=lim/2; i; i >>= 1){
            if(tree[p+i] < x){
                x -= tree[p+i];
                p += i;
            }
        }
        return ++p;
    }
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=1; i<=n; i++) add(i,1);
    }
}bit;
struct rmq{
    int tree[265000], lim;
    void init(int n, int* a){
        for(lim = 1; lim <= n; lim <<= 1);
        for(int i=0; i<n; i++){
            tree[lim + i + 1] = a[i];
        }
        for(int i=lim-1; i; i--){
            tree[i] = max(tree[2*i],tree[2*i+1]);
        }
    }
    int q(int s, int e){
        int ret = 0;
        s += lim;
        e += lim;
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
 
int dx[100005];
 
int GetBestPosition(int N, int C, int R, int *K, int *S, int *E){
    for (int i=0; i<C; i++) {
        S[i]++;
        E[i]++;
    }
    bit.init(N);
    rmq.init(N-1,K);
    for (int i=0; i<C; i++) {
        int st = bit.lbnd(S[i]);
        int ed = bit.lbnd(E[i] + 1) - 1;
        for (int j=E[i]; j>S[i]; j--) {
            bit.add(bit.lbnd(j),-1);
        }
        S[i] = st;
        E[i] = min(ed,N)-1;
        if(rmq.q(S[i],E[i]) < R){
            dx[S[i]]++;
            dx[E[i]+1]--;
        }
    }
    for (int i=1; i<=N-1; i++) {
        dx[i] += dx[i-1];
    }
    return (int)(max_element(dx+1,dx+N) - dx - 1);
}