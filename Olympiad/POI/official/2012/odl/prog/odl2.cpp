/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Odleglosc                                        *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n*lglg(n))                                     *
 *   Opis:              Rozwiazanie wzorcowe, BFS z wielu zrodel         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <queue>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <list>
#include <stack>
using namespace std;
#define PB push_back
#define MP make_pair
#define source1 first
#define source2 second
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
#define FORE(i,x) for(__typeof((x).begin()) i=(x).begin();i != (x).end();++i)
#define present(c,x) ((c).find(x) != (c).end()) 
#define cpresent(c,x) (find(all(c),x) != (c).end())
#define SZ(x) int((x).size()) 
#define ALL(x) (x).begin(),(x).end()
#define CLR(x,w) memset((x),w,sizeof (x))
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef long long int lli;
typedef vector<lli> vl;
typedef pair<lli, lli> pll;
typedef vector<pll> vll;

#define MAXN 1000005   
#define INF 1000000000

pii tab[MAXN];
int n, a, fact[MAXN], perm[MAXN], Vmax, licznik, ans[MAXN];
bool odw[MAXN];
queue<int> Q;
vector<int> Plist, Vlist;

bool mark(int x, int y){
  
  if(tab[y].source1 == 0){
    tab[y].source1 = tab[x].source1;
    return true;
  }

  if(tab[y].source2 == 0){
    if(tab[x].source1 != tab[y].source1){
      tab[y].source2 = tab[x].source1;
      if(tab[y].source1 == y) licznik++;
      return true;
    }
    if(tab[x].source2 != 0 && odw[x]){
      tab[y].source2 = tab[x].source2;
      if(tab[y].source1 == y) licznik++;
      return true;
    }
  }

  return false;
}

int main(){
  
  int temp = scanf("%d", &n);
  REP(i,n){
    temp = scanf("%d", &a);
    Vlist.PB(a);
    Vmax = max(Vmax,a);
    if(perm[a]==0){
      perm[a] = i+1;
      tab[a].source1 = a;
      Q.push(a);
    }else{
      ans[i+1] = perm[a];
      if(ans[perm[a]] == 0)
        ans[perm[a]] = i+1;
    }
  }
  
  FOR(i,2,Vmax) fact[i] = i;
  for(int i = 2; i * i <= Vmax; i++) 
    if(fact[i] == i)
      for(int j = i * i; j <= Vmax; j += i)
        if(fact[j] == j) 
          fact[j] = i;
  FOR(i,2,Vmax) if(fact[i]==i) Plist.PB(i);

  while(!Q.empty() && licznik < n){
    a = Q.front(); Q.pop();
    
    int cur = a, div = INF;
    while(cur != 1){
      if(fact[cur] != div) if(mark(a,a/fact[cur])) Q.push(a/fact[cur]);
      div = fact[cur];
      cur /= div;
    }

    FORE(i,Plist) 
      if(a * *i > Vmax) break;
      else if(mark(a,a**i)) Q.push(a**i);
    
    odw[a] = true;
  }

  REP(i, int(Vlist.size()))
    if(ans[i+1]) printf("%d\n", ans[i+1]);  
    else printf("%d\n", perm[tab[Vlist[i]].source2]);  

  return 0;
}
