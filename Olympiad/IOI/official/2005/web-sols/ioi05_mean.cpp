#include <cstdio>
#include <algorithm>
using namespace std;
 
int main(){
    int n;
    bool sw = 0;
    long long lo = -1e18, hi = 1e18, piv = 0;
    scanf("%d",&n);
    while (~scanf("%d",&n)) {
        if(sw) lo = max(lo,piv - n);
        else hi = min(hi,n - piv);
        piv = -piv + 2 * n;
        sw ^= 1;
    }
    printf("%lld",max(hi-lo+1,0ll));
}
