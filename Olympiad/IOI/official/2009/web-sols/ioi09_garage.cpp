#include <cstdio>
#include <queue>
using namespace std;
queue<int> q;
  
int n,m;
int r[105], c[2005], v[105], ccar[105];
  
int main(){
    scanf("%d %d",&n,&m);
    for (int i=1; i<=n; i++) {
        scanf("%d",&r[i]);
    }
    for (int i=1; i<=m; i++) {
        scanf("%d",&c[i]);
    }
    long long res = 0;
    for (int i=0; i<2*m; i++) {
        int t;
        int parked = 0;
        scanf("%d",&t);
        if(t > 0){
            for (int j=1; j<=n; j++) {
                if(!v[j]){
                    v[j] = 1;
                    ccar[j] = t;
                    res += c[t] * r[j];
                    parked = 1;
                    break;
                }
            }
            if(!parked){
                q.push(t);
            }
        }
        else{
            t = -t;
            for (int j=1; j<=n; j++) {
                if(ccar[j] == t){
                    v[j] = 0;
                    ccar[j] = 0;
                    if(!q.empty()){
                        v[j] = 1;
                        ccar[j] = q.front();
                        res += c[q.front()] * r[j];
                        q.pop();
                    }
                    break;
                }
            }
        }
    }
    printf("%lld",res);
}
