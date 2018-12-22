#include <cstdio>
#include <algorithm>
using namespace std;

struct pravokutnik
{
    int x1, x2, y1, y2;
    pravokutnik() {}
    pravokutnik( int x, int y, int p )
    {
        x1 = x - p;
        x2 = x + p;
        y1 = y - p;
        y2 = y + p;
    }
};

int main()
{
    int n;
    scanf("%d",&n);

    int x, y, p;
    scanf("%d%d%d", &x, &y, &p);

    pravokutnik S( x, y, p);
    long long rjesenje = 0;

    for(int i=1; i<n; ++i)
    {
        scanf("%d%d%d", &x, &y, &p);
        pravokutnik A( x, y, p );

        int D = max( max(A.x1 - S.x2, S.x1 - A.x2),
                     max(A.y1 - S.y2, S.y1 - A.y2) );
        if( D < 0 ) D = 0;

        rjesenje += D;

        S.x1 -= D;
        S.x2 += D;
        S.y1 -= D;
        S.y2 += D;

        pravokutnik presjek;
        presjek.x1 = max( S.x1, A.x1 );
        presjek.x2 = min( S.x2, A.x2 );
        presjek.y1 = max( S.y1, A.y1 );
        presjek.y2 = min( S.y2, A.y2 );

        S = presjek;
    }
    printf("%lld\n", rjesenje);
}
