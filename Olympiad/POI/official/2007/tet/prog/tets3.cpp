/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Tetris attack (TET)                                        *}
{*   Plik:    tets3.cpp                                                  *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Rozwiazanie za wolne. Zlozonosc: O(n^2), kwadratowa        *}
{*            implementacja rozwiazania wzorcowego                       *}
{*                                                                       *}
{*************************************************************************/
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

int toi(char ch) { return int(ch)-int('0'); }

int chg(char ch) { return int(ch)-int('a'); }

#define MAX_N 50000

int n;
int t[2*MAX_N],il;
int p1[MAX_N+1],p2[MAX_N+1];
int tab[1000000],licz;

int main()
{
  scanf("%d",&n);
  il=2*n;
  REP(i,2*n) scanf("%d",&t[i]);
  REP(i,n+1) p1[i]=p2[i]=-1;
  REP(i,2*n) if (p1[t[i]]==-1) p1[t[i]]=i; else p2[t[i]]=i;
  int m=0,pocz=0;
  while (il-pocz)
  {
    int x=3*MAX_N,x0=-1;
    FOR(i,pocz,il-1) if (i==p2[t[i]]) { x0=t[i]; x=p2[t[i]]-p1[t[i]]; break; }
    m+=x-1;
    FORD(i,p2[x0]-1,p1[x0]+1)
    {
      p1[t[i]]++;
      t[i+1]=t[i];
    }
    FORD(i,p1[x0]-1,pocz)
    {
      p1[t[i]]+=2;
      t[i+2]=t[i];
    }
    FOR(i,p1[x0],p2[x0]-2) tab[licz++]=(i+1)-pocz;
    pocz+=2;
  }
  printf("%d\n",m);
  REP(i,licz) printf("%d\n",tab[i]);
  return 0;
}
