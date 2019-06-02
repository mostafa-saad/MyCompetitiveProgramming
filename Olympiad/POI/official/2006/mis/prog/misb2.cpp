/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MIS (Misie)                                    *
 *   Plik:                misb2.cpp                                      *
 *   Autor:               Szymon Acedañski                               *
 *   Opis:                Rozwiazanie niepoprawne.                       *
 *                        Rozwiazanie dynamiczne, robi pelnego dynamika, *
 *                        ale alokuje tylko tyle pamieci, ile naprawde   *
 *                        bedzie trzeba.                                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

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

int na1, na2, nb1, nb2;
int* t;

void inittabl()
{
    t = new int[na1*na2*nb1*nb2*16];
}

static inline int& ref(int a1, int a2, int b1, int b2, int x, int y)
{
    return t[y + 4*(x + 4*(b2 + nb2*(b1 + nb1*(a2 + na2*a1))))];
}

static inline int T(int a1, int a2, int b1, int b2, int x, int y)
{
    if (a1 < 0 || a2 < 0 || b1 < 0 || b2 < 0) return 0;
    return ref(a1,a2,b1,b2,x,y);
}

void calc(int a1, int a2, int b1, int b2)
{
    REP(i,4) REP(j,4) {
        REP(k,4)
            if (!((((i&1) == (j&1)) && ((j&1) == (k&1))) || (((i&2) == (j&2)) && ((j&2) == (k&2))))) {
                ref(a1, a2, b1, b2, i, j) =
                    ( ref(a1, a2, b1, b2, i, j) +
                    T(a1 - (j==A1), a2 - (j==A2), b1 - (j==B1), b2 - (j==B2), k, i) )
                    % MODULO;
            }
    }
}

int main()
{
    INT(a1); INT(a2); INT(b1); INT(b2);
    if (a1 + a2 + b1 + b2 == 1) {
        printf("1\n");
        return 0;
    }

    na1 = a1+1; na2 = a2+1; nb1 = b1+1; nb2 = b2+1;
    inittabl();
    REP(i,4) REP(j,4)
        ref((i==A1) + (j==A1), (i==A2) + (j==A2), (i==B1) + (j==B1), (i==B2) + (j==B2), i, j) = 1;
    
    REP(i,a1+1) REP(j,a2+1) REP(k,b1+1) REP(l,b2+1)
        calc(i,j,k,l);
    int sum = 0;
    REP(i,4) REP(j,4)
        sum += T(a1,a2,b1,b2,i,j);
    printf("%d\n", sum % MODULO);
    return 0;
}
