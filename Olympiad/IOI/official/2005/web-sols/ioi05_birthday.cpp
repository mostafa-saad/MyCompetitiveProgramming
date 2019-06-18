#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
 
int a[1000005],n;
int b[1000005];
 
int sol(){
    int len = 0, c = 0;
    for (int j=0; j<n; j++) {
        if(b[j] == 0) c++;
        else c = 0;
        len = max(len,c);
    }
    int nn = 0;
    for (int j=0; j<n; j++) {
        if(b[j]) break;
        nn++;
    }
    for (int j=n-1; j>=0; j--) {
        if(b[j]) break;
        nn++;
    }
    len = max(len,nn);
    return (n-len)/2;
}
int main(){
    int t;
    scanf("%d",&n);
    for (int i=0; i<n; i++) {
        scanf("%d",&t);
        a[t-1] = i;
    }
    for (int i=0; i<n; i++) {
        b[(a[i] - i + n) % n] ++;
    }
    int res1 = sol();
    memset(b,0,sizeof(b));
    for (int i=0; i<n; i++) {
        b[(a[n-1-i] - i + n) % n] ++;
    }
    res1 = min(res1,sol());
    printf("%d",res1);
}
