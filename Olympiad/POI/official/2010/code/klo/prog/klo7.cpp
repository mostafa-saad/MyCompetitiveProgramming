/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Klocki (KLO)                                              *
 *   Plik:     klo7.cpp                                                  *
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

#define M 1001013

int a[M],r[M];
ll s[M];

int main()
{
    int n,m,k;
    scanf("%d %d",&n,&m);
    REP(i,n) scanf("%d",&a[i]);
    REP(o,m)
    {
        scanf("%d",&k);
        int d = 0, ret = 0, ile = 0;
        ll ss = 0, x = 0;
        REP(i,n)
        {
            ile++;
            x += a[i] - k;
            ss += a[i] - k;
            if(x >= 0) 
            {
                int A = 0, B = d, C;
                while(A<B)
                {
                    C = (A+B)/2;
                    if(s[C] <= ss) 
                        B = C;
                    else
                        A = C+1;
                }
                ret = max(ret, i+1 - r[A]);
            }
            else 
            {
                s[d+1] = x + s[d];
                r[d+1] = ile + r[d];
                d++;
                ile = 0;
                x = 0;
            }
        }
        printf("%d ",ret);
    }
    puts("");
    return 0;
}
