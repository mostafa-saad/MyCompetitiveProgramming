/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Antysymetria (ANT)                                        *
 *   Plik:     ant4.cpp                                                  *
 *   Autor:    Tomasz Kulczynski                                         *
 *   Opis:     Rozwiazanie weryfikujace.                                 *
 *                                                                       *
 *************************************************************************/ 

#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <numeric>
#include <cmath>
#include <cstdlib>
using namespace std;

#define X first
#define Y second
#define MP make_pair
#define PB push_back
typedef long long ll;
typedef double D;
typedef long double ld;
typedef vector<int> VI;
typedef pair<int,int> PII;
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(VAR(i,a);i<=(b);++i)
#define FORD(i,a,b) for(VAR(i,a);i>=(b);--i)
#define FORE(a,b) for(VAR(a,(b).begin());a!=(b).end();++a)
#define VAR(a,b) __typeof(b) a=(b)
#define SIZE(a) ((int)((a).size()))
#define ALL(x) (x).begin(),(x).end()
#define CLR(x,a) memset(x,a,sizeof(x))
int cond = 1;
#define db(x) {if(cond){cerr << __LINE__ << " " << #x << " " << x << endl; } }
#define dbv(x) {if(cond){cerr << __LINE__ << " " << #x << ": "; FORE(__i,x) cerr << *__i << " "; cerr << endl;} }

#define M 501013
#define N 19

int t[N][M], tt[N][M];
vector<pair<ll,int> > u;

bool por(int d,int a,int b)
{
    int x = 0, y = N-1, s;
    while(x<y)
    {
        s = (x+y+1)/2;
        if((1<<s) <= d) x = s;
        else y = s - 1;
    }
    return t[x][a] == tt[x][b] && t[x][a+d-(1<<x)] == tt[x][b+d-(1<<x)];
}

char s[M];
#define inf ((ll)1e8)

int main()
{
    int n;
    ll ret = 0;
    scanf("%d %s",&n,s);
    REP(i,n) t[0][i] = s[i]-'0', tt[0][n-1-i] = '1' - s[i];
    FOR(j,1,N-1) 
    {
        u.clear();
        int p = (1<<(j-1));
        REP(i,n+1-p-p)
        {
            u.PB(MP(t[j-1][i] * inf + t[j-1][i+p], i+1));
            u.PB(MP(tt[j-1][i] * inf + tt[j-1][i+p], -i));
        }
        sort(ALL(u));
        int l = 0;
        ll pop = u.begin()->X;
        FORE(i,u)
        {
            if(i->X != pop) l++;
            pop = i->X;
            if(i->Y > 0)
                t[j][i->Y-1] = l;
            else
                tt[j][-(i->Y)] = l;
        }
    }
    REP(i,n-1)
    {
        int a = 0, b = min(i+1,n-i-1), ss;
        while(a<b)
        {
            ss=(a+b+1)/2;
            if(por(ss, i+1-ss, n-1-i-ss)) a=ss;
            else b = ss-1;
        }
        ret += a;
    }
    printf("%lld\n",ret);
    return 0;
}
