#include <cstdio>
#include <algorithm>
#include <queue>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
typedef pair<int,double> pi2;
 
struct pt{int q,s,i;}a[500005];
bool cmp(pt a, pt b){return a.s * b.q == b.s * a.q ? (a.q < b.q) : (a.s * b.q < b.s * a.q);}
 
priority_queue<int> pq;
priority_queue<pi> pq2;
 
int n;
long long w;
 
int main(){
    scanf("%d %lld",&n,&w);
    for (int i=1; i<=n; i++) {
        scanf("%d %d",&a[i].s,&a[i].q);
        a[i].i = i;
    }
    sort(a+1,a+n+1,cmp);
    pi2 maxv(0,-1e18);
    int maxt = 0;
    long long t = 0;
    for (int i=1; i<=n; i++) {
        pq.push(a[i].q);
        t += a[i].q;
        while (t * a[i].s > w * a[i].q) {
            t -= pq.top();
            pq.pop();
        }
        if(pi2((int)pq.size(),-1.0 * t * a[i].s / a[i].q) > maxv){
            maxv = pi2((int)pq.size(),-1.0 * t * a[i].s / a[i].q);
            maxt = i;
        }
    }
    printf("%d\n",maxv.first);
    t = 0;
    for (int i=1; i<=maxt; i++) {
        pq2.push(pi(a[i].q,a[i].i));
        t += a[i].q;
        while (t * a[i].s > w * a[i].q) {
            t -= pq2.top().first;
            pq2.pop();
        }
    }
    while (!pq2.empty()) {
        printf("%d\n",pq2.top().second);
        pq2.pop();
    }
}
