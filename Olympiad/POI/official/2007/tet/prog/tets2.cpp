/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Tetris attack (TET)                                        *}
{*   Plik:    tets2.cpp                                                  *}
{*   Autor:   Jakub Radoszewski                                          *}
{*   Opis:    Rozwiazanie za wolne. Zlozonosc: O(n^2), w kazdym kroku    *}
{*            usuwamy dwa najblizsze klocki                              *}
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

#define MAX_N 50000

int n;
list<int> t;
int p1[MAX_N+1],p2[MAX_N+1];
int tab[1000000],licz;
bool c[MAX_N+1];

int main()
{
  scanf("%d",&n);
  REP(i,2*n) { int a; scanf("%d",&a); t.PB(a); }
  REP(i,n+1) p1[i]=p2[i]=-1,c[i]=1;
  list<int>::iterator it,it1;
  it=t.begin();
  REP(i,2*n) { if (p1[*it]==-1) p1[*it]=i; else p2[*it]=i; it++; }
  int m=0,l=2*n;
  while (!t.empty())
  {
    int x=3*MAX_N,x0=0;
    FOR(i,1,n) if (c[i])
    {
      if (p2[i]-p1[i]<x)
      {
        x=p2[i]-p1[i];
        x0=i;
      }
    }
    m+=x-1;
    it=t.end(); it--;
    int i=l-1;
    while (i!=p2[x0])
    {
      if (p1[*it]==i) p1[*it]-=2; else p2[*it]-=2;
      it--; i--;
    }
    it1=it; it1--; t.erase(it); i--;
    it=it1;
    while (i!=p1[x0])
    {
      if (p1[*it]==i) p1[*it]--; else p2[*it]--;
      it--; i--;
    }
    t.erase(it);
    FOR(i,p1[x0],p2[x0]-2) tab[licz++]=i+1;
    c[x0]=0;
    l-=2;
  }
  printf("%d\n",m);
  REP(i,m) printf("%d\n",tab[i]);
  return 0;
}
