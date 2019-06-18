#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
 
int n, x[505], y[505], a[505], adj[505][505];
 
int q;
 
bool cmp(int a, int b){return adj[a][q] > adj[b][q];}
 
int main(){
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&x[i],&y[i]);
        a[i] = i;
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            adj[i][j] = abs(x[j] - x[i]) + abs(y[j] - y[i]);
        }
    }
    int ret = 1e9;
    for (int i=0; i<n; i++) {
        q = i;
        sort(a,a+n,cmp);
        for (int j=0; j<n; j++) {
            int low = 0;
            for (int k=0; k<n; k++) {
                if(adj[j][a[low]] < adj[j][a[k]]){
                    ret = min(ret,adj[i][j] + adj[j][a[low]] + adj[i][a[k]]);
                    low = k;
                }
            }
        }
    }
    printf("%d",ret);
}