/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Biura (BIU)                                                *}
{*   Plik:    biu4.cpp                                                   *}
{*   Autor:   Tomasz Idziaszek                                           *}
{*   Opis:    Rozwiazanie weryfikacyjne korzystajace ze struktury        *}
{*            find&union, ale wymagajace sortowania krawedzi.            *}
{*            Czas dzialania: O(mlogm)                                   *}
{*                                                                       *}
{*************************************************************************/
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cassert>
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)

const int N=100100;
int n, m;
vector<int> adj[N];

int fu[N], rank[N];
int find(int x) { assert(x>=0 && x<n); return fu[x]<0 ? x : fu[x]=find(fu[x]); }

int next[N+1], prev[N+1];

int visited[N], counter[N];
int unionlist[N];

int main() {
   scanf("%d%d",&n,&m);
   REP(i,m) {
      int a, b;
      scanf("%d%d",&a,&b);
      --a; --b;
      assert(0<=a && a<n);
      assert(0<=b && b<n);
      adj[a].push_back(b);
      adj[b].push_back(a);
   }
   REP(i,n) sort(adj[i].begin(), adj[i].end());

   REP(i,n+1) next[i]=(i+1)%(n+1), prev[i]=(i+n+1-1)%(n+1);
   REP(i,n) fu[i]=-1;
   REP(i,n) rank[i]=0;

   REP(i,n) {
      vector<int>::const_iterator p = adj[i].begin(), kon = adj[i].end();
      int j = 0, visnum = 0, unionnum = 0;
      while (j < i) {
   while (j < i && p != kon) {
      if (*p > j) break;
      else if (*p == j) {
         if (++counter[find(j)] == 1)
      visited[visnum++] = find(j);
         j = next[j];
         assert(0<=j && j<=n);
         ++p;
      }
      else {
         if (++counter[find(*p)] == 1)
      visited[visnum++] = find(*p);
         ++p;
      }
   }
   if (j >= i) break;
   unionlist[unionnum++] = j;
         j = next[j];
   assert(0<=j && j<=n);
      }
      while (p != kon && *p < j) {
   if (++counter[find(*p)] == 1)
      visited[visnum++] = find(*p);
   ++p;
      }
      REP(k,visnum) if (counter[visited[k]] < -fu[visited[k]])
   unionlist[unionnum++] = visited[k];
      REP(k,visnum) counter[visited[k]]=0;
      assert(unionnum <= n);
      assert(visnum <= n);
      REP(k,unionnum) {
   int J = find(unionlist[k]), I = find(i);
   if (I<J) swap(I,J);
   if (I!=J) {
      if (rank[I] > rank[J]) {
         fu[I] += fu[J];
         fu[J] = I;
      }
      else {
         fu[J] += fu[I];
         fu[I] = J;
         if (rank[I] == rank[J]) rank[J]++;
      }
      next[prev[I]] = next[I];
      prev[next[I]] = prev[I];
   }
      }
   }
   REP(i,n) assert(counter[i]==0);
   REP(i,n) counter[find(i)]++;
   sort(counter, counter+n);
   int answer = 0;
   REP(i,n) if (counter[i]) ++answer;
   printf("%d\n", answer);
   REP(i,n) if (counter[i]) printf("%d ", counter[i]);
   puts("");
}
