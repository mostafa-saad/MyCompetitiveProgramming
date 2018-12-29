/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Randka                                           *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O((n+k)*log(n))                                  *
 *   Opis:              Rozwiazanie bledne                               *
 *                      Niepoprawne zalozenie, ze para zawsze moze sie   *
 *                      spotkac                                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define PB push_back
#define REP(i,n) for(int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
#define FORE(i,x) for(__typeof((x).begin()) i=(x).begin();i != (x).end();++i)
#define SZ(x) int((x).size()) 
typedef vector<int> vi, VI;
#define MAXN 500005
#define MAXP 20

int graf[MAXN], symbol[MAXN], dlg[MAXN], nr[MAXN], l[MAXN][MAXP], gleb[MAXN];
int n, k, a, b, c, i, j, dlg1, dlg2, temp, cyklInd, wyn1, wyn2;
bool vis[MAXN];
VI topo, kraw[MAXN];

void DFS(int v){
  vis[v] = true;
  if(!vis[graf[v]]) DFS(graf[v]);
  topo.PB(v);
}

void linkuj(int x,int o){
  gleb[x]=gleb[o]+1;
  l[x][0]=o;
  FOR(i,1,MAXP-1) l[x][i]=l[l[x][i-1]][i-1];
  FORE(i,kraw[x]) if(*i != o && symbol[*i] > 0) linkuj(*i,x);
}

int LCA(int a,int b){
  if(gleb[a]<gleb[b]) swap(a,b);
  FORD(p,MAXP-1,0) 
    if(gleb[a]-(1<<p) >= gleb[b]) 
      a=l[a][p];
  FORD(p,MAXP-1,0) 
    if(l[a][p] != l[b][p])
      {a=l[a][p]; b=l[b][p];}
  return a==b?a:l[a][0];
}

int main(){

  // IN
  temp = scanf("%d%d", &n, &k);
  FOR(i,1,n) { temp = scanf("%d", &graf[i]); kraw[graf[i]].PB(i);}

  // Sortowanie topologiczne
  FOR(i,1,n) if(!vis[i]) DFS(i);

  // wyznaczanie reprezentantow cykli i drzew
  // numeracja wierzcholkow na cyklu i ich dlugosci
  REP(i,n) {
    if(!symbol[graf[topo[i]]]){
      cyklInd = symbol[topo[i]] = -graf[topo[i]];
      nr[topo[i]] = j = 1;
      while(topo[i]!=-cyklInd){
        i++; j++;
        symbol[topo[i]] = cyklInd;
        nr[topo[i]] = j;
      }
      dlg[-cyklInd] = j;
      continue;
    }
    if(symbol[graf[topo[i]]] < 0) symbol[topo[i]] = graf[topo[i]];
    else symbol[topo[i]] = symbol[graf[topo[i]]];
  }
  
  // wyznaczenie tablicy LCA dla wierzcholkow
  FOR(i,1,n) if(symbol[i]<0) linkuj(i,i);

  // OUT
  FOR(i,1,k) {
    temp = scanf("%d%d", &a, &b);
    wyn1 = wyn2 = 0;
    
    // na jednym poddrzewie
    if(symbol[a] == symbol[b] && symbol[a] > 0){
      c = LCA(a,b);
      wyn1 = gleb[a] - gleb[c];
      wyn2 = gleb[b] - gleb[c];
    }
    
    // jeden na drzewie, drugi na innym drzewie lub cyklu osiagalnym z drzewa
    if(symbol[abs(symbol[a])] == symbol[abs(symbol[b])] && symbol[a] != symbol[b]){
      if(symbol[a] > 0) {wyn1 = gleb[a] - 1; a = abs(symbol[a]);}
      if(symbol[b] > 0) {wyn2 = gleb[b] - 1; b = abs(symbol[b]);}
    } 
    
    // oba na cyklu i nie s± tym samym wierzcholkiem
    if(symbol[a] == symbol[b] && symbol[a] < 0 && a != b){
      dlg2 = abs(nr[b] - nr[a]);
      dlg1 = dlg[-symbol[a]] - dlg2;
      if(nr[a] > nr[b]) swap(dlg1, dlg2);

      if(dlg2 + wyn2 < dlg1 + wyn1) wyn2 += dlg2;
      else if(dlg2 + wyn2 > dlg1 + wyn1) wyn1 += dlg1;
      else if(dlg1 < dlg2) wyn1 += dlg1;
      else if(dlg1 > dlg2) wyn2 += dlg2;
      else wyn1 += dlg1;
    }
    
    printf("%d %d\n", wyn1, wyn2);
  }

  return 0;
}
