#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
typedef pair<int,int> pi;
int b,n,d,m;
int x[100005], y[100005], z[100005];

void calc1(){
    for (int i=0; i<n; i++) {
        scanf("%d",&x[i]);
    }
    sort(x,x+n);
    long long res = 0;
    for (int i=0; i<n; i++) {
        res += upper_bound(x,x+n,x[i]+d) - lower_bound(x,x+n,x[i]-d);
    }
    printf("%lld",(res-n)/2);
}

struct ln{
    int type; // 1 = adder, 2 = deleter, 3 = lines
    int xpy;
    int xmy;
    int line_s, line_e;
}ele[300005];

bool operator<(ln a, ln b){return a.xpy < b.xpy;}
struct bit{
    int tree[265000],lim;
    void init(int n){
        n += 2;
        for(lim = 1; lim <= n; lim <<= 1);
    }
    void add(int x, int v){
        x += 2;
        while(x <= lim){
            tree[x] += v;
            x += x & -x;
        }
    }
    int sum(int x){
        x += 2;
        int r = 0;
        while(x){
            r += tree[x];
            x -= x & -x;
        }
        return r;
    }
}bit;

void calc2(){
    for (int i=0; i<n; i++) {
        scanf("%d %d",&x[i],&y[i]);
        for (int j=0; j<3; j++) {
            ele[3*i+j].type = j+1;
        }
        ele[3*i].xpy = x[i]+y[i]-d;
        ele[3*i+1].xpy = x[i]+y[i]+d;
        ele[3*i+2].xpy = x[i]+y[i];
        ele[3*i].xmy = ele[3*i+1].xmy = x[i]-y[i]+m;
        ele[3*i+2].line_s = x[i]-y[i]-d+m;
        ele[3*i+2].line_e = x[i]-y[i]+d+m;
    }
    sort(ele,ele+3*n);
    bit.init(2*m);
    long long res = 0;
    for (int i=0; i<3*n;) {
        int e = i;
        while (ele[i].xpy == ele[e].xpy) e++;
        for (int j=i; j<e; j++) {
            if(ele[j].type == 1){
                bit.add(ele[j].xmy,1);
            }
        }
        for (int j=i; j<e; j++) {
            if(ele[j].type == 3){
                res += bit.sum(min(2*m,ele[j].line_e)) - bit.sum(max(0,ele[j].line_s-1));
            }
        }
        for (int j=i; j<e; j++) {
            if(ele[j].type == 2){
                bit.add(ele[j].xmy,-1);
            }
        }
        i = e;
    }
    res -= n;
    res /= 2;
    printf("%lld",res);
}

int pan[80][160][160];

void calc3(){
    for (int i=0; i<n; i++) {
        scanf("%d %d %d",&x[i],&y[i],&z[i]);
        pan[z[i]][x[i]+y[i]][x[i]-y[i]+80]++;
    }
    for (int i=0; i<=75; i++) {
        for (int j=1; j<160; j++) {
            for (int k=1; k<160; k++) {
                pan[i][j][k] += pan[i][j-1][k] + pan[i][j][k-1] - pan[i][j-1][k-1];
            }
        }
    }
    long long res = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<=75; j++) {
            int dist = d - abs(j - z[i]);
            if(dist < 0) continue;
            res += pan[j][min(x[i] + y[i] + dist,159)][min(x[i] - y[i] + 80 + dist,159)]
            - pan[j][min(x[i] + y[i] + dist,159)][max(x[i] - y[i] + 80 - dist - 1,0)]
            - pan[j][max(x[i] + y[i] - dist - 1,0)][min(x[i] - y[i] + 80 + dist,159)]
            + pan[j][max(x[i] + y[i] - dist - 1,0)][max(x[i] - y[i] + 80 - dist - 1,0)];
        }
    }
    printf("%lld",(res-n)/2);
}

int main(){
    scanf("%d %d %d %d",&b,&n,&d,&m);
    if(b == 1) calc1();
    else if(b == 2) calc2();
    else calc3();
}
