/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Pieczec                                            *
 *   Autor programu:       Jakub Radoszewski                                  *
 *   Zlozonosc czasowa:    O(n*m)                                             *
 *   Zlozonosc pamieciowa: O(n*m)                                             *
 *   Opis:                 rozwiazanie wzorcowe                               *
 *****************************************************************************/


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

const int N=1010;

int n,m,a,b;
char tekst[N][N], wzorzec[N][N];
vector<PII> wz;

inline bool ins(int g,int h) { return g>=0 && g<h; }

int main()
{
  int q;
  scanf("%d",&q);
  while (q--) {
  wz.clear();
  scanf("%d%d%d%d",&n,&m,&a,&b);
  REP(i,n) scanf("%s",tekst[i]);
  REP(i,a) scanf("%s",wzorzec[i]);
  PII p=MP(-1,-1);
  REP(i,a) REP(j,b) if (wzorzec[i][j]=='x')
  {
    if (p==MP(-1,-1)) p=MP(i,j);
    wz.PB(MP(i-p.FI,j-p.SE));
  }
  int wyn=0;
  REP(i,n)
  {
    if (wyn<0) break;
    REP(j,m) if (tekst[i][j]=='x')
    {
      if (wyn<0) break;
      REP(k,SIZE(wz))
      {
        int x=i+wz[k].FI,y=j+wz[k].SE;
        if (!ins(x,n) || !ins(y,m) || tekst[x][y]!='x')
        {
          wyn=-INFTY; break;
        }
        tekst[x][y]='.';
      }
      ++wyn;
    }
  }
  if (wyn<0) printf("NIE\n"); else printf("TAK\n");
  }
  return 0;
}
