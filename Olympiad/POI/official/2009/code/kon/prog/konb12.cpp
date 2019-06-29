/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Konduktor (KON)                                           *
 *   Plik:     konb12.cpp                                                *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Bierzemy k najwiekszych, ale po kazdym kroku usuwamy      *
 *             wszystkie przedzialy, ktore zahaczaja o dany element.     *
 *             Aby wszystko bylo O(n^4), robimy to na drzewie przedzial. *
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

int los(int m)
{
  return (int)((double)m*(rand()/(RAND_MAX+1.0)));
}


#define MX 600

int n,k;
int x[MX][MX];
VI wyn;


/* Drzewo przedzialowe. */
int drz[4*MX];
int ile;

inline void insert(int a,int b,int w)
{
  int va=ile+a,vb=ile+b;
  drz[va]+=w;
  if (va!=vb) drz[vb]+=w;
  while (va/2!=vb/2)
  {
    if (va%2==0) drz[va+1]+=w;
    if (vb%2==1) drz[vb-1]+=w;
    va/=2; vb/=2;
  }
}

inline int zapyt(int u)
{
  int v=u+ile;
  int w=drz[v];
  while (v!=1)
  {
    v/=2;
    w+=drz[v];
  }
  return w;
}



bool bylo[MX];

int main()
{
  scanf("%d%d",&n,&k);
  REP(i,n) FOR(j,i+1,n-1) scanf("%d",x[i]+j);
  ile=1;
  while (ile<n-1) ile*=2;
  while (k--)
  {
    REP(i,2*ile) drz[i]=0;
    REP(i,n) FOR(j,i+1,n-1) if (x[i][j]) insert(i,j-1,x[i][j]);
    int best=-1,bi=-1,u;
    REP(i,n-1) if (!bylo[i] && (u=zapyt(i))>best) { best=u; bi=i; }
    bylo[bi]=true;
    wyn.PB(bi+1);
    REP(i,n) FOR(j,i+1,n-1) if (bi>=i && bi<j) x[i][j]=0;
  }
  sort(ALL(wyn));
  REP(i,SIZE(wyn)) { printf("%d",wyn[i]); if (i<SIZE(wyn)-1) putchar(' '); else puts(""); }
  return 0;
}
