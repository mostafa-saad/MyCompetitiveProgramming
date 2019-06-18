#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int a[255][255],n,m,t,k;
int x[255][255],y[255][255];
int p[255], q[255], r[255], s[255];

int f(int p, int q, int r, int s){
    return a[r][s] - a[p-1][s] - a[r][q-1] + a[p-1][q-1];
}

void solve_1(int p, int q){
    int left_border = 1;
    int res = 1e9;
    for (int i=p; i; i--) {
        while (f(i,left_border+1,p,q) >= k) left_border++;
        if(f(i,left_border,p,q) >= k) res = min(res,(q - left_border + p - i + 2)*2);
    }
    x[p][q] = res;
}

void solve_2(int p, int q){
    int right_border = m;
    int res = 1e9;
    for (int i=p; i<=n; i++) {
        while (f(p,q,i,right_border-1) >= k) right_border--;
        if(f(p,q,i,right_border) >= k) res = min(res,(right_border - q + i - p + 2)*2);
    }
    y[p][q] = res;
}

int main(){
    memset(x,63,sizeof(x));
    memset(y,63,sizeof(y));
    memset(r,63,sizeof(r));
    memset(s,63,sizeof(s));
    scanf("%d %d %d %d",&n,&m,&t,&k);
    for (int i=0; i<t; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        a[x][y]++;
    }
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
        }
    }
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            solve_1(i,j);
            solve_2(i,j);
        }
    }
    for (int i=1; i<=n; i++) {
        p[i] = *min_element(x[i]+1,x[i]+m+1);
        q[i] = *min_element(y[i]+1,y[i]+m+1);
        for (int j=1; j<=m; j++) {
            r[j] = min(r[j],x[i][j]);
            s[j] = min(s[j],y[i][j]);
        }
    }
    for (int i=2; i<=n; i++) {
        p[i] = min(p[i],p[i-1]);
    }
    for (int i=n-1; i; i--) {
        q[i] = min(q[i],q[i+1]);
    }
    for (int i=2; i<=m; i++) {
        r[i] = min(r[i],r[i-1]);
    }
    for (int i=m-1; i; i--) {
        s[i] = min(s[i],s[i+1]);
    }
    
    int res = 1e9;
    for (int i=1; i<n; i++) {
        res = min(res,p[i] + q[i+1]);
    }
    for (int i=1; i<m; i++) {
        res = min(res,r[i] + s[i+1]);
    }
    if(res >= 1e9) puts("NO");
    else printf("%d",res);
}
