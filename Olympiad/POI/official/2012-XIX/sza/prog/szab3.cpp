/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Szatnia                                          *
 *   Autor:             Michal Zgliczynski                               *
 *   Zlozonosc czasowa: O(n^2*MaxK + p)                                  *
 *   Opis:              Rozwiazanie dziala tylko dla rownych s_j         *
 *                                                                       *
 *************************************************************************/

#include <iostream>
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
    if(tp != a.tp) return tp < a.tp;
    return tz < a.tz;
  }
};
pytanie pytania[MAXP];
plaszcz plaszcze[MAXN];
int konce[MAXN];
bool F[MAXN][MAXK+1];
bool mozliwe[MAXP];
int n,p,sum,s;

void wczytajPlaszcze(){
  sum = 0;
  cin >> n;
  for(int i=0;i<n;i++){
    cin >> plaszcze[i].c >> plaszcze[i].tp >> plaszcze[i].tz;
    konce[i] = plaszcze[i].tz;
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
  s = pytania[0].s; // jedno i takie samo dla wszytkich pytan
}

void wczytaj(){
  wczytajPlaszcze();
  wczytajPytania();
}

void wloz_przedmiot(int nrDynamik, plaszcz a){
  for(int i = sum; i>=a.c;i--)
    F[nrDynamik][i] |= F[nrDynamik][i - a.c];
}

void policz(){
  sort(plaszcze, plaszcze + n);
  sort(pytania, pytania + p);
  sort(konce, konce + n);
  int itPlaszcze =0, itPytania=0;
  int odp = 0;
  for(int i=0;i<n;i++)
    F[i][0] = 1;
  while(odp < n && itPytania != p){
    if(konce[odp]-s <= pytania[itPytania].m) odp++; // szukam odpowiedniego konca
    else{
      if(itPlaszcze < n && plaszcze[itPlaszcze].tp <= pytania[itPytania].m){
        for(int i=odp; i < n ; i++)
          if(konce[i] > plaszcze[itPlaszcze].tz) break;
          else wloz_przedmiot(i,plaszcze[itPlaszcze]);
        itPlaszcze++;
      }
      else{
        mozliwe[pytania[itPytania].id] = F[odp][pytania[itPytania].k];
        itPytania++;
      }
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
