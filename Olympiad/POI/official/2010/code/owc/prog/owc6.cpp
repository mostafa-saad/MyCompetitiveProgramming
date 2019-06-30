/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Owce (OWC)                                                *
 *   Plik:     owc6.cpp                                                  *
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

D eps = 1e-8;
#define M 613
#define N 20013

bool czy[M][M];
int x[M],y[M],p[N],q[N],t[M][M];
pair<PII,int> tt[M+N];

bool lt(const pair<PII,int> &a, const pair<PII,int> &b)
{
    int w ;
    if((w = a.X.X * b.X.Y - a.X.Y * b.X.X) != 0)
        return w < 0;
    return a.Y < b.Y;
}
 
bool ltt(const PII &a, const PII &b)
{
    return a.X * b.Y < a.Y * b.X;
}

int main()
{
    int n,k,m;
    scanf("%d %d %d",&n,&k,&m);
    REP(i,n) scanf("%d %d",&x[i],&y[i]);
    REP(i,k) scanf("%d %d",&p[i],&q[i]);
    REP(i,n)
    {
        int w = 0;
        REP(j,n) if(i!=j) tt[w++] = MP(MP(y[j]-y[i],x[j]-x[i]), j+1);
        REP(j,k) tt[w++] = MP(MP(q[j] - y[i], p[j] - x[i]), 0);
        sort(tt, tt+w, lt);
        int s = 0;
        REP(j,w) if(!tt[j].Y) s++;
        else czy[i][tt[j].Y - 1] = ( (s%2==0) && ( !j || ltt(tt[j-1].X,tt[j].X) ) );
    }
//    REP(i,n) { REP(j,n) printf("%d",czy[i][j]); printf("\n");}
    REP(a,n-1) t[a][a+1] = 1;
    REP(a,n-2) t[a][a+2] = 1;
    FOR(d,3,n-1)  REP(a,n-d) 
    {
        t[a][a+d] = czy[a+1][a+d] * t[a+1][a+d];
        FOR(i,a+2,a+d-1) t[a][a+d] += czy[a][i] * czy[a+d][i] * t[a][i] * t[i][a+d] % m;
        t[a][a+d] %= m;
  //      printf("%d:%d  ",a,t[a][a+d]);
    } 
//    printf("\n"); }
    printf("%d\n",t[0][n-1]);
    return 0;
}
