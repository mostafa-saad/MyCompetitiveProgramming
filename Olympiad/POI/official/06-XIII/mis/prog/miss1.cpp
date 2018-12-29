/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MIS (Misie)                                    *
 *   Plik:                miss1.cpp                                      *
 *   Autor:               Szymon Acedañski                               *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Brutalny backtracking.                         *
 *                                                                       *
 *************************************************************************/

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

#define A1 0
#define A2 1
#define B1 2
#define B2 3

#define MODULO 1000000

int bt(int a1, int a2, int b1, int b2, int i, int j)
{
    if (a1 < 0 || a2 < 0 || b1 < 0 || b2 < 0) return 0;
    if (a1 == 0 && a2 == 0 && b1 == 0 && b2 == 0) return 1;
    int sum = 0;
    REP(k,4) 
        if (!((((i&1) == (j&1)) && ((j&1) == (k&1))) || (((i&2) == (j&2)) && ((j&2) == (k&2)))))
            sum += bt(a1 - (k==A1), a2 - (k==A2), b1 - (k==B1), b2 - (k==B2), j, k);
    return sum % MODULO;
}

int main()
{
    INT(a1); INT(a2); INT(b1); INT(b2);
    if (a1 + a2 + b1 + b2 == 1) {
        printf("1\n");
        return 0;
    }
    int sum = 0;
    REP(i,4) REP(j,4)
        sum += bt(a1 - (i==A1) - (j==A1),
                  a2 - (i==A2) - (j==A2),
                  b1 - (i==B1) - (j==B1),
                  b2 - (i==B2) - (j==B2), i, j);
    printf("%d\n", sum % MODULO);
    return 0;
}

