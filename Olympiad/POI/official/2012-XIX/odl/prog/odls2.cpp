/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Odleglosc                                        *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n * n * lg(n))                                 *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Dla kazdej wartosci przegladamy cala liste       *
 *                      wartosci z wejscia i znajdujemy najblizsza,      *
 *                      odleglosc obliczamy jako suma wykladnikow        *
 *                      nww(a,b)/nwd(a,b)                                *
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
#define X first
#define Y second
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

int n, a, fact[MAXN], Vmax, ind;
vector<int> Vlist;

int nwd(int a, int b) {return (b == 0) ? a : nwd(b, a % b); }

int exp(int a){
  int ret = 0;
  while(a!=1) {a/=fact[a]; ret++;}
  return ret;
}

int main(){

  int temp = scanf("%d", &n);
  REP(i,n){
    temp = scanf("%d", &a);
    Vlist.PB(a);
    Vmax = max(Vmax,a);
  }
  
  FOR(i,2,Vmax) fact[i] = i;
  for(int i = 2; i * i <= Vmax; i++) 
    if(fact[i] == i)
      for(int j = i * i; j <= Vmax; j += i)
        if(fact[j] == j) 
          fact[j] = i;

  FORE(i,Vlist){
    int minD = INF;
    FORE(j,Vlist) if(i != j){
      int d = nwd(*i,*j), e1 = exp(*i/d), e2 = exp(*j/d);
      if(minD > e1 + e2){
        minD = e1 + e2;
        ind = j - Vlist.begin() + 1;
      }
    }
    printf("%d\n", ind);
  }

  return 0;
}
