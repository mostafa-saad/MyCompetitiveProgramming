/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Szatnia                                          *
 *   Autor:             Michal Zgliczynski                               *
 *   Zlozonosc czasowa: O(nlogn + plogp + n*maxK)                        *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1000, MAXP = 1000000, MAXK = 100000;
const int inf = 2100000000; // musi byc wieksze od max(m_i + s_i)
struct pytanie{
  int m,k,s;
  int id; // numer zapytania
  bool operator<(const pytanie &a) const{
    return m < a.m;
  }
};

struct plaszcz{
  int c, tp, tz;
  bool operator<(const plaszcz &a) const{
    return tp < a.tp;
  }
};

pytanie pytania[MAXP];
bool mozliwe[MAXP];
plaszcz plaszcze[MAXN];
int F[MAXK + 1];
int n,p,sum;

void wczytajPlaszcze(){
  sum = 0;
  cin >> n;
  for(int i=0;i<n;i++){
    cin >> plaszcze[i].c >> plaszcze[i].tp >> plaszcze[i].tz;
    sum += plaszcze[i].c;
  }
  sum = min(sum, MAXK);
}

void wczytajPytania(){
  cin >> p;
  for(int i=0;i<p;i++){
    cin >> pytania[i].m >> pytania[i].k >> pytania[i].s;
    pytania[i].id = i;
  }
}

void wczytaj(){
  wczytajPlaszcze();
  wczytajPytania();
}

void policz(){
  sort(plaszcze,plaszcze + n);
  sort(pytania,pytania + p);
  int itPlaszcze = 0;
  int itPytania = 0;
  F[0] = inf;
  while(itPytania != p){
    if(itPlaszcze < n && plaszcze[itPlaszcze].tp <= pytania[itPytania].m){
      for(int i = sum ; i>= plaszcze[itPlaszcze].c ; i--)
        F[i] = max(F[i], min(F[i - plaszcze[itPlaszcze].c] , plaszcze[itPlaszcze].tz));
      itPlaszcze++;
    }
    else{
      mozliwe[pytania[itPytania].id] = (F[pytania[itPytania].k] > pytania[itPytania].m + pytania[itPytania].s); // F[k_i] > m_i + s_i
      itPytania++;
    }
  }
  for(int i=0;i<p;i++)
    cout << (mozliwe[i] ? "TAK" : "NIE") << endl;
}

int main(){
  ios_base::sync_with_stdio(0);
  wczytaj();
  policz();
  return 0;
}
