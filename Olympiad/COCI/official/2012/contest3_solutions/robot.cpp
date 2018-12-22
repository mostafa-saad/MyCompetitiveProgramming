#include<cstdio>
using namespace std;

const int milijun = 1000000;
int kolx[2*milijun+5], koly[2*milijun+5];
char buff[300003];

inline int abs(int x) { if (x > 0) return x; return -x; }

int main()
{
    int n, m; scanf("%d%d", &n, &m);
    long long curr = 0;
    for(int i=0; i<n; i++)
    {
        int x, y; scanf("%d%d", &x, &y);
        curr += abs(x) + abs(y);
        kolx[x+milijun]++;
        koly[y+milijun]++;
    }
    for(int i=1; i<2*milijun; i++) kolx[i] = kolx[i-1] + kolx[i];
    for(int i=1; i<2*milijun; i++) koly[i] = koly[i-1] + koly[i];
    scanf("%s", buff);
    int x = 0;
    int y = 0;
    for(int i=0; i<m; i++)
    {
        int dalje, blize;
        if( buff[i] == 'S' ) { dalje = koly[y+milijun]; blize = n - dalje; y++; }
        if( buff[i] == 'J' ) { blize = koly[y-1+milijun]; dalje = n - blize; y--; }
        if( buff[i] == 'I' ) { dalje = kolx[x+milijun]; blize = n - dalje; x++; }
        if( buff[i] == 'Z' ) { blize = kolx[x-1+milijun]; dalje = n - blize; x--; }
        curr += dalje - blize;
        printf("%lld\n", curr);
    }
    return 0;
}
