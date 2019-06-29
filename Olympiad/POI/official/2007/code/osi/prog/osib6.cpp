/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Osie (OSI)                                                 *}
{*   Plik:    osib6.cpp                                                  *}
{*   Autor:   Szymon Acedanski                                           *}
{*   Opis:    Rozwiązanie niepoprawne (prawie poprawne). Haszujemy       *}
{*            wszystkie półwielokąty.                                    *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int i=0; i<(n); ++i)
#define REPD(i,n) for(int i=(n)-1; i>=0; --i)
#define FOR(i,a,b) for(int i=(a); i<=(b); ++i)
#define FORD(i,a,b) for(int i=(a); i>=(b); --i)
#define VAR(v,n) __typeof(n) v = n
#define FORE(i,v) for(VAR(i, (v).begin()); i!=(v).end(); ++i)
#define ALL(v) (v).begin(), (v).end()
#define PB push_back
#define MP(a,b) make_pair(a,b)
#define _INT(a) scanf("%d", &a)
#define INT(a) int a; _INT(a)
#define _VINT(v,n) do { (v).resize((n)); REP(i,(n)) { INT(j); (v)[i]=j; } } while(0)
#define VINT(v,n) vector<int> v; _VINT(v,n)
#define CHAR(a) char foo_##a[2]; scanf("%s", foo_##a); char a = foo_##a[0]

#define fprintf(...)

typedef vector<int> VI;
typedef long long hash_t;

VI X;
VI Y;
vector<hash_t> hv, hvr;
vector<hash_t> H1, H2;
int L;

#define HASH_V1  0x24736473LL
#define HASH_V2  0x35468382LL
#define HASH_MUL 0x1234567bLL
#define HASH_MOD 0x7fffffffLL

int det(int x0, int y0, int x1, int y1)
{
    return x0*y1-y0*x1;
}

static inline long long mod2(long long a, long long b)
{
    a %= b;
    if (a < 0) a += b;
    return a;
}

static inline int mod(int a)
{
    a %= L;
    if (a < 0) a += L;
    return a;
}

hash_t hash_vertex(int i)
{
    int px = X[mod(i-1)];
    int py = Y[mod(i-1)];

    int x = X[i];
    int y = Y[i];

    int nx = X[mod(i+1)];
    int ny = Y[mod(i+1)];

    int l1 = (x-px)*(x-px) + (y-py)*(y-py);
    int l2 = (x-nx)*(x-nx) + (y-ny)*(y-ny);
    int angle = det(x-px, y-py, nx-x, ny-y);

    return (l1*HASH_V1 + l2*HASH_V2 + angle) % HASH_MOD;

}

hash_t hash_vertex_rev(int i)
{
    int px = X[mod(i+1)];
    int py = Y[mod(i+1)];

    int x = X[i];
    int y = Y[i];

    int nx = X[mod(i-1)];
    int ny = Y[mod(i-1)];

    int l1 = (x-px)*(x-px) + (y-py)*(y-py);
    int l2 = (x-nx)*(x-nx) + (y-ny)*(y-ny);
    int angle = det(nx-x, ny-y, x-px, y-py);

    return (l1*HASH_V1 + l2*HASH_V2 + angle) % HASH_MOD;
}

int main()
{
    INT(nt);
    REP(t, nt) {
        INT(n);
        X.resize(2*n);
        Y.resize(2*n);
        int xp, yp;
        L = 0;
        REP(i, n) {
            INT(x); INT(y); x*=2; y*=2;

            if (i) {
                X[L] = (x+xp)/2;
                Y[L] = (y+yp)/2;
                L++;
            }

            X[L] = x;
            Y[L] = y;
            L++;

            xp = x; yp = y;
        }

        X[L] = (xp+X[0])/2;
        Y[L] = (yp+Y[0])/2;
        L++;

        int hl = L/2;

        REP(i, L) fprintf(stderr, "%4d %4d 0x%08llx 0x%08llx\n", X[i], Y[i], hash_vertex(i), hash_vertex_rev(i));
        fprintf(stderr, "\n");

        hash_t top_factor = 1;
        hash_t h1 = 0, h2 = 0;
        REP(i,hl) top_factor = (top_factor * HASH_MUL) % HASH_MOD;

        hv.resize(L);
        hvr.resize(L);
        REP(i,L) {
            hv[i] = hash_vertex(i);
            hvr[i] = hash_vertex_rev(i);
        }

        REP(k,hl) {
            int i = mod(-hl+k);
            int j = mod(-i);

            h1 = (h1*HASH_MUL) % HASH_MOD;
            h1 = (h1+hv[i]) % HASH_MOD;
            fprintf(stderr, "h1[%2d] = 0x%08llx  ", i, h1);

            h2 = (h2*HASH_MUL) % HASH_MOD;
            h2 = (h2+hvr[j]) % HASH_MOD;
            fprintf(stderr, "h2[%2d] = 0x%08llx\n", j, h2);
        }

        fprintf(stderr, "\n");
        H1.resize(L);
        H2.resize(L);

        REP(i,L) {
            h1 = (h1*HASH_MUL) % HASH_MOD;
            h1 = (h1+hv[i]) % HASH_MOD;
            H1[i] = h1;
            fprintf(stderr, "H1[%2d] = 0x%08llx  ", i, h1);
            hash_t tf = (hv[mod(i-hl)]*top_factor) % HASH_MOD;
            h1 = mod2(h1-tf, HASH_MOD);

            int j = mod(-i);
            h2 = (h2*HASH_MUL) % HASH_MOD;
            h2 = (h2+hvr[j]) % HASH_MOD;
            H2[j] = h2;
            fprintf(stderr, "H2[%2d] = 0x%08llx\n", j, h2);
            tf = (hvr[mod(j+hl)]*top_factor) % HASH_MOD;
            h2 = mod2(h2-tf, HASH_MOD);
        }

        int ret = 0;
        REP(i,L) if (H1[i] == H2[i]) ret++;
        printf("%d\n", ret/2);
    }
    return 0;
}

