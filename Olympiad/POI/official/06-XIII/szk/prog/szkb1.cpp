/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SZK (Szko³y)                                   *
 *   Plik:                szkb1.cpp                                      *
 *   Autor:               Pawe³ Parys                                    *
 *   Opis:                Algorytm zachlanny, najpierw znajduje dowolne  *
 *                        przypisanie numerow, a nastepnie jesli znajdzie*
 *                        jakas zamiane, ktora spowoduje obnizenie kosztu*
 *                        wykona ja                                      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <set>

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

class high_cmp
{
public:
    bool operator()(int a, int b)
    {
        if (schools[a].high==schools[b].high)
            return a<b;
        return schools[a].high<schools[b].high;
    }
};

bool low_cmp(const School &a, const School &b)
{
    return a.low<b.low;
}

int sch_match[SIZE], pos_match[SIZE];

bool find_any()
{
    sort(schools, schools+N, low_cmp);
    set<int, high_cmp> sch;
    int sa = 0;
    REP(p, N)
    {
        while (sa<N && schools[sa].low==p)
            sch.insert(sa++);
        if (sch.empty())
            return false;
        int ss = *sch.begin();
        if (p>schools[ss].high)
            return false;
        sch.erase(ss);
        sch_match[ss] = p;
        pos_match[p] = ss;
    }
    return true;
}

inline int cost(int s, int p)
{
    return abs(schools[s].cur-p)*schools[s].score;
}

void small_changes()
{
    int ch = 1;
    while (ch)
    {
        ch = 0;
        REP(s1, N)
        {
        int p1 = sch_match[s1];
        if (p1==schools[s1].cur)
            continue;
        int dir = (p1<schools[s1].cur)?1:-1;
        int p2 = p1+dir;
        int s2 = pos_match[p2];
        if (p1<schools[s2].low || p1>schools[s2].high || 
            cost(s1,p1)+cost(s2,p2)<=cost(s1,p2)+cost(s2,p1))
            continue;
        ch = 1;
        sch_match[s1] = p2;
        sch_match[s2] = p1;
        pos_match[p1] = s2;
        pos_match[p2] = s1;
        --s1;
        }
    }
}

bool big_change(int &s1_s)
{
    for (int s1 = s1_s;;)
    {
        int p1 = sch_match[s1];
        if (p1==schools[s1].cur)
            goto next;
        FOR(p2, schools[s1].low, schools[s1].high)
        {
            int s2 = pos_match[p2];
            if (s1==s2 || p1<schools[s2].low || p1>schools[s2].high || 
                cost(s1,p1)+cost(s2,p2)<=cost(s1,p2)+cost(s2,p1))
                continue;
            sch_match[s1] = p2;
            sch_match[s2] = p1;
            pos_match[p1] = s2;
            pos_match[p2] = s1;
            s1_s = s1;
            return true;
        }
        next:
        s1 = (s1+1)%N;
        if (s1 == s1_s) break;
    }
    return false;
}

int main()
{
    scanf("%d", &N);
    REP(a,N)
        schools[a].read();
    if (!find_any())
    {
        printf("NIE\n");
        return 0;
    }
    int bcs = 0;
    do small_changes(); while (big_change(bcs));
    int k = 0;
    REP(a, N)
        k += cost(a, sch_match[a]);
    printf("%d\n", k);
}
