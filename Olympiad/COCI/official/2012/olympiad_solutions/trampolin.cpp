#include <cstdio>
using namespace std;

inline int max( int x, int y ) { return x>y?x:y; }

const int NN = 1000005;

int h[NN], lijevo[NN], desno[NN], maks[NN];
char t[NN];

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    --k;

    for(int i=0; i<n; i++) scanf("%d", h+i);
    scanf("%s", t);

    // svima izracunaj koliko maksimalno mogu lijevo.
    // sve koji lijevo mogu do trampolina, pretvori u trampoline.
    for(int i=1; i<n; ++i)
    {
        if( h[i] < h[i-1] ) continue;
        if( t[i-1] == 'T' ) t[i] = 'T';
        lijevo[i] = 1 + lijevo[i-1];
    }

    // svima izracunaj koliko maksimalno mogu desno.
    // sve koji desno mogu do trampolina, pretvori u trampoline.
    for(int i=n-2; i>=0; --i)
    {
        if( h[i] < h[i+1] ) continue;
        if( t[i+1] == 'T' ) t[i] = 'T';
        desno[i] = 1 + desno[i+1];
    }

    // izbroji trampoline i nadji najbolji ne-trampolin
    int T = 0, best = 0;
    for(int i=0; i<n; i++)
    {
        if( t[i] == 'T' ) ++T;
        else best = max( best, 1 + max(lijevo[i], desno[i]) );
    }

    if( t[k] == 'T' ) printf("%d\n", T + best);

    // ako pak ne mogu do trampolina...
    else
    {
        int l = k, d = k;
        while( l > 0 && h[l-1] == h[k] ) l--;
        while( d < n-1 && h[d+1] == h[k] ) d++;
        printf("%d\n", d - l + 1 + max( lijevo[l], desno[d] ) );
    }

    return 0;
}
