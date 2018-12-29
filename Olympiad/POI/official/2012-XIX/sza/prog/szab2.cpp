/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Szatnia                                          *
 *   Autor:             Michal Zgliczynski                               *
 *   Zlozonosc czasowa: O(n(log n + MaxK) + p log p)                     *
 *   Opis:              Rozwiazanie dziala tylko dla rownych a_i         *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1000, MAXP = 1000000, MAXK = 100000;
const int inf = 2100000000; 

struct pytanie{
  int m,k,s;
  int id; // numer zapytania
  bool operator<(const pytanie &a) const{
    return m+s > a.m+a.s;
  }
};

struct plaszcz{
  int c, tp, tz;
  bool operator<(const plaszcz &a) const{
    return tz > a.tz;
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
  sort(plaszcze, plaszcze + n);
  sort(pytania, pytania + p);
  int itPlaszcze = 0;
  int itPytania = 0;
  F[0] = 1;
  while(itPytania != p){
    if(itPlaszcze == n || pytania[itPytania].m + pytania[itPytania].s >= plaszcze[itPlaszcze].tz){
      //cout << "mam pytanie : m,k,s : " << pytania[itPytania].m << ' ' << pytania[itPytania].k << ' ' << pytania[itPytania].s << endl;
      if(pytania[itPytania].m < plaszcze[0].tp) // przypadek jezeli poczatek wlamania ma sie zdarzyc przed wszystkimi plaszczami
        mozliwe[pytania[itPytania].id] = 0;
      else
        mozliwe[pytania[itPytania].id] = F[pytania[itPytania].k];
      itPytania++;
    }
    else{
      //cout << "mam przedmiot : c,tp,tz: " << plaszcze[itPlaszcze].c << ' ' << plaszcze[itPlaszcze].tp << ' ' << plaszcze[itPlaszcze].tz << endl;
      for(int i = sum; i>=plaszcze[itPlaszcze].c;i--)
        F[i] |= F[i - plaszcze[itPlaszcze].c];
      itPlaszcze++;
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
