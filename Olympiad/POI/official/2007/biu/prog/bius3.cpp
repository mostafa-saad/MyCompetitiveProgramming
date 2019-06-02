/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Biura (BIU)                                                *}
{*   Plik:    bius3.cpp                                                  *}
{*   Autor:   Tomasz Idziaszek                                           *}
{*   Opis:    Rozwiazanie weryfikacyjne, brutalnie wyznaczajace spojne   *}
{*            skladowe grafu dopelnieniowego, korzystajac tez z          *}
{*            find&union. Czas dzialania: O(n^2 log*n)                   *}
{*                                                                       *}
{*************************************************************************/
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)

const int N=100100;
int n,m,fu[N],ile[N],wyn,a,b;
vector<int> adj[N];

int find(int x) { return fu[x] < 0 ? x : fu[x] = find(fu[x]); }
void unionnow(int x, int y) {
   x=find(x), y=find(y);
   if (x==y) return;
   fu[x]+=fu[y];
   fu[y]=x;
}

int main() {
   scanf("%d%d",&n,&m);
   REP(i,m) {
      scanf("%d%d",&a,&b);
      --a; --b;
      adj[a].push_back(b);
      adj[b].push_back(a);
   }
   REP(i,n) sort(adj[i].begin(),adj[i].end());
   REP(i,n) fu[i]=-1;
   REP(i,n) {
      int j=0,p=0;
      while (j<n && p<int(adj[i].size())) {
   if (j==adj[i][p]) ++p,++j;
   else if (j<adj[i][p]) unionnow(j,i), ++j;
   else ++p;
      }
      while (j<n) unionnow(j,i), ++j;
   }
   REP(i,n) ile[find(i)]++;
   sort(ile,ile+n);
   REP(i,n) if (ile[i]) ++wyn;
   printf("%d\n",wyn);
   REP(i,n) if (ile[i]) printf("%d ",ile[i]);
   puts("");
}
