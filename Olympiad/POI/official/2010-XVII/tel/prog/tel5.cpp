/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Teleporty (TEL)                               *
 *   Plik:                 tel5.cpp                                      *
 *   Autor:                Tomasz Kulczyński                             *
 *   Opis:                 Rozwiazanie weryfikujące.                     *
 *   Zlozonosc czasowa:    O(n + m)                                      *
 *   Zlozonosc pamieciowa: O(n + m)                                      *
 *   Kodowanie znaków:     UTF-8                                         *
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

#define M 40013

vector<int> v[M];
int e[M];

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    REP(i,m) 
    {
        int a,b;
        scanf("%d %d",&a,&b);
        a--,b--;
        v[a].PB(b);
        v[b].PB(a);
    }
    int a = v[0].size(), b = 0, c = 0, d = v[1].size();
    e[0] = e[1] = 1;
    FORE(i,v[0]) e[*i] = 1;
    FORE(i,v[1]) e[*i] = 1;
    FORE(i,v[0]) FORE(j,v[*i]) if(!e[*j]) e[*j] = 1, b++;
    FORE(i,v[1]) FORE(j,v[*i]) if(!e[*j]) e[*j] = 1, c++;
    if(a<d)
    {
        swap(a,d);
        swap(b,c);
    }
    b += n-2-a-b-c-d;
    printf("%d\n",a*(a+1)/2 + b*(b-1)/2 + c*(c-1)/2 + d*(d+1)/2 + a*b + b*c + c*d - m);
    return 0;
}
