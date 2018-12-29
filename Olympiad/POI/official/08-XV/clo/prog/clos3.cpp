/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clos3.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie oparte o szukanie skojarzenia, jednak robi to *
 *             na tyle sprytnie, ze sie miesci w limitach. Istnieje      *
 *             podejrzenie, ze dla tych grafow ma zlozonosc O(n*log n).  *
 *                                                                       *
 *************************************************************************/
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
#define FOREACH(I,C) for(VAR(I,(C).begin());I!=(C).end();I++)

typedef vector<int> VI;
typedef pair<int,int> PII;
typedef long long ll;
typedef vector<string> VS;

ll nwd(ll a,ll b) { return !b?a:nwd(b,a%b); }
inline int CEIL(int a,int b) { return a%b ? a/b+1 : a/b; }
template <class T> inline T sqr(const T&a) { return a*a; }

VS parse(string s)
{
  string a;
  VS wyn;
  REP(i,(int)s.size())
    if (s[i]!=' ') a+=s[i];
    else if (!a.empty()) { wyn.PB(a); a=""; }
  if (!a.empty()) wyn.PB(a);
  return wyn;
}

int toi(char ch) { return int(ch)-int('0'); }

int chg(char ch) { return int(ch)-int('a'); }

/* Najliczniejsze skojarzenie w grafie dwudzielnym.
 * Zlozonosc: O(VE), ale w praktyce _bardzo_ szybkie. */


/* Wierzcholki 0..(n1-1) | n1..(n1+n2-1) */
#define MAXN 310000

int n1,n2;
VI t[MAXN];

bool c[2*MAXN];
int skoj[2*MAXN]; /* Tablica skojarzen */

/* Pokrycie wierzcholkowe - wrzucamy wierzcholki incydentne z jakimikolwiek
 * wierzcholkami nieskojarzonymi i jakkolwiek uzupelniamy, dodajac z kazdej
 * skojarzonej pary jeden wierzcholek. */

bool dfs(int v)
{
  c[v]=true;
  REP(i,(int)t[v].size())
  {
    int x=t[v][i];
    if (skoj[x]==-1 || (!c[skoj[x]] && dfs(skoj[x])))
    {
      skoj[v]=x; skoj[x]=v;
      return true;
    }
  }
  return false;
}

void kojarz()
{
  REP(i,n1+n2) skoj[i]=-1;
  bool dasie=true;
  while (dasie)
  {
    dasie=false;
    REP(i,n1) c[i]=false;
    REP(i,n1) if (skoj[i]==-1 && !c[i]) dasie|=dfs(i);
  }
}


vector<PII> kraw;

int main()
{
  int n,m,a,b;
  scanf("%d%d",&n,&m);
  kraw.resize(m);
  n1=n; n2=m;
  REP(i,m)
  {
    scanf("%d%d",&a,&b);
    a--; b--;
    kraw[i]=MP(a,b);
    t[a].PB(n+i);
    t[b].PB(n+i);
  }
  kojarz();
  bool ok=1;
  REP(i,n) if (skoj[i]==-1) ok=0;
  if (!ok) { puts("NIE"); return 0; }
  puts("TAK");
  REP(i,n)
  {
    int j=skoj[i]-n;
    if (kraw[j].FI!=i) printf("%d\n",kraw[j].FI+1);
    else printf("%d\n",kraw[j].SE+1);
  }
  return 0;
}
