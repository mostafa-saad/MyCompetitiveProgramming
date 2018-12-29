/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Arkanoid                                           *
 *   Autor programu:       Jakub Radoszewski                                  *
 *   Zlozonosc czasowa:    O(n + m + k log k)                                 *
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
#include<cassert>
using namespace std;

#define FOR(I,A,B) for(int I=(A);I<=(B);I++)
#define FORD(I,A,B) for(int I=(A);I>=(B);I--)
#define REP(I,N) for(int I=0;I<(N);I++)
#define ALL(X) (X).begin(),(X).end()
#define PB push_back
#define MP make_pair
#define FI first
#define SE second
#define X first
#define Y second
#define INFTY 100000000
#define VAR(V,init) __typeof(init) V=(init)
#define FORE(I,C) for(VAR(I,(C).begin());I!=(C).end();I++)
#define SIZE(x) ((int)(x).size())

typedef vector<int> VI;
typedef pair<int,int> PII;
typedef long long ll;
typedef vector<string> VS;
typedef vector<PII> VPII;

int m,n,k;

set<ll> wierzcholki;
map<ll,PII> wspolrzedne_klocka;

VPII pola(PII klocek)
{
  vector<PII> t;
  int x=klocek.X,y=klocek.Y;
  
  t.PB(MP((2*x+1), (2*y)));
  t.PB(MP((2*x+2), (2*y+1)));

  t.PB(MP(4*m-(2*x+1), (2*y)));
  t.PB(MP(4*m-(2*x), (2*y+1)));

  t.PB(MP((2*x+1), 4*n-(2*y+2)));
  t.PB(MP((2*x+2), 4*n-(2*y+1)));

  t.PB(MP(4*m-(2*x+1), 4*n-(2*y+2)));
  t.PB(MP(4*m-(2*x), 4*n-(2*y+1)));

  REP(i,SIZE(t)) if ((t[i].X+t[i].Y)%4!=m%4)
  {
    swap(t[i],t.back());
    t.pop_back();
    --i;
  }
  return t;
}

/* Rozszerzony Euklides.
 * Dla a i b podaje (p,q,d) takie, ze ap+bq=d. */
void euclid(int a, int b, ll &p, ll &q, int &d)
{
  if (!b) { p=1; q=0; d=a; } else
  {
    ll p1,q1; int d1;
    euclid(b,a%b,p1,q1,d1);
    d=d1;
    p=q1; q=p1-q1*(a/b);
  }
}

ll revmod_m_n,revmod_n_m;

inline ll numer(PII p)
{
  int a=((m-p.X)%(4*m)+4*m)%(4*m), b=p.Y%(4*n);
  ll chtwor=((ll)a*n*revmod_n_m + (ll)b*m*revmod_m_n)%((ll)m*n);
  if (chtwor<0LL) chtwor+=(ll)m*n;
  REP(z,4)
  {
    if (chtwor%(4*m)==a && chtwor%(4*n)==b) return chtwor;
    chtwor+=(ll)m*n;
  }
  return chtwor;
}

void zmien_wierzcholki(PII p,bool wstaw)
{
  VPII t=pola(p);
  REP(j,SIZE(t))
  {
    ll nr = numer(t[j]);
    //if (wstaw) printf("%d %d: %lld\n",t[j].FI,t[j].SE,nr);
    if (nr<0) continue;
    if (wstaw)
    {
      wierzcholki.insert(nr);
      wspolrzedne_klocka[nr]=p;
    } else
    {
      wierzcholki.erase(nr);
      wspolrzedne_klocka.erase(nr);
    }
  }
}

int main()
{
  scanf("%d%d%d",&m,&n,&k);
  int nwd;
  euclid(m,n,revmod_m_n,revmod_n_m,nwd);
  revmod_m_n%=n; revmod_n_m%=m;
  REP(i,k)
  {
    int x,y;
    scanf("%d%d",&x,&y);
    --x; --y;
    zmien_wierzcholki(MP(x,y),true);
  }
  ll akt=0,wyn=0;
  while (k--)
  {
    // przemieszczenie pileczki
    set<ll>::iterator it=wierzcholki.lower_bound(akt);
    if (it==wierzcholki.end())
    {
      it=wierzcholki.begin();
      wyn+=4LL*(ll)m*n;
    }
    ll nowy=*it;
    wyn+=nowy-akt;

    // usuniecie wierzcholkow klocka
    zmien_wierzcholki(wspolrzedne_klocka[nowy],false);

    // odbicie do wlasciwej cwiartki
    int x=((m-nowy)%(4*m)+4*m)%(4*m), y=nowy%(4*n);
    if (x%2) y=4*n-y; else x=4*m-x;
    akt=numer(MP(x,y));
  }
  printf("%lld\n",wyn);
  return 0;
}
