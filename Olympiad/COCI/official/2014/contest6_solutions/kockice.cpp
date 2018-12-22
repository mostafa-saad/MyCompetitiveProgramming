#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#define MAXN 300001
using namespace std;

typedef long long llint;

llint a[MAXN], b[MAXN];
int n;

llint f(llint x){
    llint ret = 0;
    for (int i=0; i<n; i++){
        llint height = x + abs(n/2 - i);
        ret += abs(height - a[i]);
        ret += abs(height - b[i]);
    }

    return ret;
}

int main(void){
    scanf ("%d", &n);
    for (int i=0; i<n; i++) scanf ("%lld", &a[i]);
    for (int i=0; i<n; i++) scanf ("%lld", &b[i]);

    llint lo = 0, hi = 0; for (int i=0; i<n; i++) hi = max(hi, max(a[i], b[i]));
    while(lo < hi){
        llint mid = (lo + hi ) / 2;
        if (f(mid) < f(mid+1)) hi = mid;
        else                   lo = mid + 1;
    }

    printf ("%lld\n", f(lo));

    return 0;
}
