typedef long long lint;
 
int r;
lint sum[100005];
 
int ck(int n, int piv, lint lim){
    int s,e,m;
    lint r;
    for (int i=1; i<=n-piv+1; i++) {
        s = i;
        e = i + piv - 1;
        m = (s+e)/2;
        r = (sum[e] - sum[m]) - (sum[m-piv%2] - sum[s-1]);
        if(r <= lim) return 1;
    }
    return 0;
}
 
int besthub(int R, int L, int* X, lint B){
    for (int i=1; i<=R; i++) {
        sum[i] = sum[i-1] + X[i-1];
    }
    int s = 0, e = R;
    while (s != e) {
        int m = (s+e+1)/2;
        if(ck(R,m,B)) s = m;
        else e = m-1;
    }
    return s;
}