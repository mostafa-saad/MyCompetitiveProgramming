/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SZK (Szko³y)                                   *
 *   Plik:                szkb2.cpp                                      *
 *   Autor:               Pawe³ Parys                                    *
 *   Opis:                Algorytm zachlanny, wybiera szkole o najwyzszym*
 *                        koszcie zamiany, a potem stara sie umiescic ja *
 *                        jak najblizej jej docelowej pozycji            *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

#define REP(a,n) for (int a=0; a<(n); ++a)
#define FOR(a,l,h) for (int a=(l); a<=(h); ++a)

using namespace std;

#define SIZE 200
#define INF 1000000000

int N;

struct School
{
    int cur, low, high, score;
    void read()
    {
        scanf("%d%d%d%d", &cur, &low, &high, &score);
        --cur; --low; --high;
    }
} schools[SIZE];

bool score_cmp(const School &a, const School &b)
{
    return a.score>b.score;
}

bool used[SIZE];

inline int cost(int s, int p)
{
    return abs(schools[s].cur-p)*schools[s].score;
}

int main()
{
    scanf("%d", &N);
    REP(a,N)
    {
        schools[a].read();
        used[a] = false;
    }
    sort(schools, schools+N, score_cmp);
    int k = 0;
    REP(s, N)
    {
        int bv = INF, bn = -1;
        FOR(p, schools[s].low, schools[s].high)
            if (!used[p] && cost(s, p)<bv)
                bv = cost(s, bn = p);
        if (bv==INF)
        {
            printf("NIE\n");
            return 0;
        }
        used[bn] = true;
        k += bv;
    }
    printf("%d\n", k);
}
