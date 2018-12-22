#include<cstdio>
using namespace std;

int a[1000003];

#define max(a,b) a>b?a:b

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    int maks = 0;
    for(int i=0; i<n; i++)
    {
        scanf("%d", a+i);
        maks = max( maks, a[i] );
    }
    int lo = 0, hi = maks;
    while( lo < hi )
    {
        int mid = (lo+hi+1)/2;
        long long sijece = 0;
        for(int i=0; i<n; i++)
            sijece += max( 0, a[i] - mid );
        if( sijece < m ) hi = mid-1;
        else lo = mid;
    }
    printf("%d\n", lo);
}
