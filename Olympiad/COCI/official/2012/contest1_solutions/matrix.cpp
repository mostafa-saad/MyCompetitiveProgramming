#include<cstdio>
using namespace std;

inline int max( int a, int b ) { return a>b?a:b; }

int main()
{
    int n; scanf("%d", &n);
    int m[n][n];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            scanf("%d", &m[i][j] );
    int best = 0;
    // kvadrati neparne duljine
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            int a = m[i][j];
            int b = m[i][j];
            for(int k=1; ; k++)
            {
                if( i-k < 0 || j-k < 0 || i+k >= n || j+k >= n )
                    break;
                a += m[i-k][j-k] + m[i+k][j+k];
                b += m[i-k][j+k] + m[i+k][j-k];
                best = max( best, a-b );
            }
        }
    // kvadrati parne duljine
    for(int i=0; i<n-1; i++)
        for(int j=0; j<n-1; j++)
        {
            int a = 0;
            int b = 0;
            int r1 = i; int r2 = i+1;
            int s1 = j; int s2 = j+1;
            for(int k=1; ; k++)
            {
                a += m[r1][s1] + m[r2][s2];
                b += m[r1][s2] + m[r2][s1];
                best = max(best, a-b);
                r1--; s1--; r2++; s2++;
                if( r1 < 0 || s1 < 0 || r2 >= n || s2 >= n )
                    break;
            }
        }
    printf("%d\n", best);
    return 0;
}
