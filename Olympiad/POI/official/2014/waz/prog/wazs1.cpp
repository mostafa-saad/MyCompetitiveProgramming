/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Waz                                           *
 *   Autor:                Jakub Radoszewski                             *
 *   Zlozonosc czasowa:    O(4^(3n))                                     *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wolne                             *
 *                                                                       *
 *************************************************************************/

//#include<iostream>
#include<cstdio>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<string>
#include<list>
#include<deque>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<utility>
#include<sstream>
#include<cstring>
#include<numeric>
using namespace std;

#define FOR(I,A,B) for(int I=(A);I<=(B);I++)
#define FORD(I,A,B) for(int I=(A);I>=(B);I--)
#define REP(I,N) for(int I=0;I<(N);I++)
#define ALL(X) (X).begin(),(X).end()
#define PB push_back
#define MP make_pair
#define FI first
#define SE second
#define INFTY 100000000
#define VAR(V,init) __typeof(init) V=(init)
#define FORE(I,C) for(VAR(I,(C).begin());I!=(C).end();I++)
#define SIZE(x) ((int)(x).size())

typedef vector<int> VI;
typedef pair<int,int> PII;
typedef long long ll;
typedef vector<string> VS;

#define M 1010

int n;
int t[3][M];
bool koniec;

int x[]= {0,0,-1,1};
int y[]= {-1,1,0,0};
inline bool ins(int g,int h) {
    return g>=0 && g<h;
}

void wypisz()
{
    REP(i,3)
    {
        REP(j,n-1) printf("%d ",t[i][j]);
        printf("%d\n",t[i][n-1]);
    }
}

void doit(int a,int b,int p)
{
    if (koniec) return;
    if (p>3*n)
    {
        koniec=true;
        return;
    }
    if (t[a][b] && t[a][b]!=p) return;
    bool zero=(!t[a][b]);
    t[a][b]=p;
    REP(i,4)
    {
        int a1=a+x[i],b1=b+y[i];
        if (ins(a1,3) && ins(b1,n))
        {
            doit(a1,b1,p+1);
            if (koniec) return;
        }
    }
    if (zero) t[a][b]=0;
}

int main()
{
    scanf("%d",&n);
    REP(i,3) REP(j,n) scanf("%d",t[i]+j);
    koniec=false;
    REP(i,3) REP(j,n) doit(i,j,1);
    if (koniec)
    {
        wypisz();
    } else puts("NIE");
    return 0;
}
