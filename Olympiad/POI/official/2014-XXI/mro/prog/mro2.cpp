/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Mrowisko                                      *
 *   Autor:                Zbigniew Wojna                                *
 *   Zlozonosc czasowa:    O((n+g) log g)                                *
 *   Zlozonosc pamieciowa: O(n+g)                                        *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define PB push_back
#define MP make_pair
#define X first
#define Y second
#define VAR(v,n) __typeof(n) v = (n)
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORE(i,x) for(VAR(i,(x).begin());i!=(x).end();++i)
#define SIZE(x) (int)((x).size())

typedef long long int lli, LL;
typedef pair<int, int> pii, PII;
typedef pair<lli, lli> pll;
typedef vector<int> vi, VI;
#define INF 1000000005
#define N 1000005

int groups[N];
vi graph[N];
pll range[N];

void dfs(int v, int ojc) {
    int factor = graph[v].size() - 1;
    if(factor == 0) {
        range[v].X = range[ojc].X;
        range[v].Y = range[ojc].Y;
    } else {
        range[v].X = range[ojc].X * factor;
        range[v].Y = range[ojc].Y * factor + factor - 1;
        if(range[v].X > INF) range[v].X = INF;
        if(range[v].Y > INF) range[v].Y = INF;
    }
    FORE(i,graph[v]) if(*i!=ojc) dfs(*i,v);
}

int main() {
    int n,g,k,m1=0,m2=0;
    scanf("%d%d%d",&n, &g, &k);
    REP(i,g) scanf("%d",groups+i);
    REP(i,n-1) {
        int a,b;
        scanf("%d%d",&a,&b);
        if(m1==0) {
            m1=a;
            m2=b;
        }
        graph[a].PB(b);
        graph[b].PB(a);
    }

    range[m1] = MP(k,k);
    dfs(m2,m1);
    pll temp = range[m2];
    range[m2] = MP(k,k);
    dfs(m1,m2);
    range[m2] = temp;

    sort(groups,groups+g);
    lli res = 0;
    FOR(i,1,n)
    if(graph[i].size() == 1)
        res += upper_bound(groups, groups+g, range[i].Y) -
               lower_bound(groups, groups+g, range[i].X);
    res *= k;
    printf("%lld\n",res);


    return 0;
}
