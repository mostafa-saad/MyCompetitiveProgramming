/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Chomiki (CHO)                                             *
 *   Plik:     cho3.cpp                                                  *
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

#define M 213
#define N 101013

char buf[N];
string s[M];
int p[N];
ll t[M][M], e[M][M], w[M], inf = (1LL<<60);

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    REP(i,n)
    {
        scanf("%s",buf);
        s[i] = buf;
        w[i] = s[i].size();
    }
    REP(i,n)
    {
        int j = 0;
        p[0] = -1;
        FOR(k,2,w[i]) 
        {
            while(j>=0 && s[i][k-1] != s[i][j]) j = p[j];
            j++;
            p[k] = j;
        }
        REP(z,n)
        {
            j = 0;
            REP(k,w[z]) 
            {
                while(j>=0 && s[i][j] != s[z][k]) j = p[j];
                j++;
            }
            if(j == w[i]) j = p[j];
            t[z][i] = w[i] - j;
        }
    }
    m--;
    while(m)
    {
        if(m % 2)
        {
            REP(i,n) 
            {
                e[0][i] = inf;
                REP(j,n) e[0][i] = min(e[0][i], w[j] + t[j][i]);
            }
            REP(i,n) w[i] = e[0][i];
        }
        m /= 2;
        REP(i,n) REP(j,n)
        {
            e[i][j] = inf;
            REP(k,n) e[i][j] = min(e[i][j], t[i][k] + t[k][j]);
        }
        REP(i,n) REP(j,n) t[i][j] = e[i][j];
    }
    ll ret = inf;
    REP(i,n) ret = min(ret, w[i]);
    printf("%lld\n",ret);
    return 0;
}
