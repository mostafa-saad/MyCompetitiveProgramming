/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Odleglosc                                        *
 *   Autor:             Tomasz Idziaszek                                 *
 *   Zlozonosc czasowa: O(n*lglg(n))                                     *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define REP(i,n) for(int i=0;i<(n);++i)
#define FORE(i,c) for(__typeof((c).begin())i=(c).begin();i!=(c).end();++i)

const int N = 1000000, infty = 1000000000;
int num,a[N],numer[N+1],drugi_numer[N+1];
int n,dp[N+1];
vector<int> adj[N+1];

void buduj_graf() {
   n = *max_element(a,a+num);
   for(int i=2; i*i<=n; ++i)
      if (dp[i] == 0)
         for(int j=i; j<=n; j+=i) dp[j] = i;
   for(int i=2; i<=n; ++i)
      if (dp[i] == 0) dp[i] = i;
   for(int i=2; i<=n; ++i) {
      int j = i;
      do {
         int p = dp[j];
         while (j % p == 0) j /= p;
         adj[i].push_back(i / p);
         adj[i / p].push_back(i);
      } while (j > 1);
   }
   n++;
}

int ds[N+1],ms[N+1];
queue<int> q;
int dsv[N+1],msv[N+1];

void pierwsza_faza() {
   REP(i,n) ds[i] = infty;
   REP(i,n) if (numer[i] != 0) {
      ds[i] = 0;
      ms[i] = i;
      q.push(i);
   }
   while (!q.empty()) {
      int v = q.front();
      q.pop();
      FORE(i,adj[v]) {
         if (ds[*i] == infty) {
            ds[*i] = ds[v] + 1;
            ms[*i] = ms[v];
            q.push(*i);
         }
         else if (ds[v]+1 == ds[*i] && numer[ms[v]] < numer[ms[*i]])
            ms[*i] = ms[v];
      }
   }
}

void druga_faza() {
   REP(i,n) dsv[i] = infty;
   REP(i,n) FORE(j,adj[i]) {
      int v = ms[i];
      int w = ms[*j];
      if (v != w) {
         int d = ds[i] + 1 + ds[*j];
         if (d < dsv[v] || (d == dsv[v] && numer[w] < numer[msv[v]])) {
            dsv[v] = d;
            msv[v] = w;
         }
      }
   }
}

int main() {
   scanf("%d",&num);
   REP(i,num) {
      scanf("%d",&a[i]);
      if (numer[a[i]] == 0) numer[a[i]] = i+1;
      else if (drugi_numer[a[i]] == 0) drugi_numer[a[i]] = i+1;
   }
   buduj_graf();
   pierwsza_faza();
   druga_faza();

   REP(i,num)
      if (drugi_numer[a[i]] != 0)
         printf("%d\n", numer[a[i]] != i+1 ? numer[a[i]] : drugi_numer[a[i]]);
      else
         printf("%d\n",numer[ msv[ a[i] ] ]);
}
