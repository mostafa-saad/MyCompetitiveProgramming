#include<cstdio>
using namespace std;

int main()
{
    int n, m; scanf("%d%d", &n, &m);
    int j; scanf("%d", &j);

    int lo = 1;
    int hi = m;

    int sol = 0;

    while(j--)
    {
        int x; scanf("%d", &x);
        if( lo <= x && hi >= x ) continue;
        if( x < lo )
        {
            sol += lo-x;
            hi -= (lo-x);
            lo = x;
        }
        else
        {
            sol += x-hi;
            lo += (x-hi);
            hi = x;
        }
    }

    printf("%d\n", sol);

    return 0;
}
