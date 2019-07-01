/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Randka                                           *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n*k)                                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <iostream>
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

int n, k, a, b, temp, graf[MAXN];
int wyn11, wyn12, wyn21, wyn22, max1, max2, min1, min2;
bool vis1[MAXN], vis2[MAXN];
VI path1, path2;

void func(int a, int b, int& w1, int& w2){

    while(!path1.empty()) {vis1[path1.back()] = false; path1.pop_back();}
    while(!path2.empty()) {vis2[path2.back()] = false; path2.pop_back();}

    while(!vis1[a]){
      vis1[a] = true;
      path1.PB(a);
      a = graf[a];
    }
  
    while(b != path1.back() && !vis2[b]){
      vis2[b] = true;
      path2.PB(b);
      b = graf[b];
    }
    path2.PB(b); vis2[b] = true;
    
    if(path1.back() != path2.back()){
      w1 = w2 = -1;
      return;
    }

    while(!path1.empty() && !path2.empty() && 
        path1.back() == path2.back()){
      vis1[path1.back()] = false;
      vis2[path2.back()] = false;
      path1.pop_back();
      path2.pop_back();
    }
    
    w1 = SZ(path1);
    w2 = SZ(path2);
}

int main(){

  // IN
  temp = scanf("%d%d", &n, &k);
  FOR(i,1,n) temp = scanf("%d", &graf[i]);

  // OUT
  FOR(i,1,k) {
    temp = scanf("%d%d", &a, &b);
    
    func(a, b, wyn11, wyn12);
    func(b, a, wyn22, wyn21);
    
    max1 = max(wyn11, wyn12);
    min1 = min(wyn11, wyn12);
    max2 = max(wyn21, wyn22);
    min2 = min(wyn21, wyn22);

    if(max2<max1 || (max1==max2 && min2<min1) || 
        (max1==max2 && min1==min2 && wyn11 < wyn12)){
      wyn11 = wyn21; 
      wyn12 = wyn22;
    }

    printf("%d %d\n", wyn11, wyn12);
  }

  return 0;
}
