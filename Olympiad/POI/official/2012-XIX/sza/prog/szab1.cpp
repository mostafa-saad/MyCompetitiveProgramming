/*************************************************************************
*                                                                       *
*                    XIX Olimpiada Informatyczna                        *
*                                                                       *
*   Zadanie:           Szatnia                                          *
*   Autor:             Michal Zgliczynski                               *
*   Zlozonosc czasowa: O(p*(n po 4))                                    *
*   Opis:              Rozwiazanie badajace maksymalnie 4 elementy      *
*                                                                       *
*************************************************************************/

#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1000, MAXP = 1000000, MAXK = 100000;
const int inf = 2100000000; // musi byc wieksze id max(m_i + s_i)

struct plaszcz{
  int c, tp, tz;
};

plaszcz plaszcze[MAXN];
bool F[MAXK];
int n,sum;
vector<int> uzyteczne;
bool ok;
int m,k,s;

void gogo(int pos, int suma, int il){
  if(suma == k) ok = 1;
  if(ok || pos == (int)uzyteczne.size() || suma > k || il == 4) return ;
  gogo(pos+1,suma,il);
  gogo(pos+1,suma + plaszcze[uzyteczne[pos]].c,il+1);
}

void solveSingleCaseBrute(){
  cin >> m >> k >> s;
  if(k > sum) cout << "NIE\n";
  uzyteczne.clear();
  for(int i=0;i<n;i++)
    if(plaszcze[i].tp <= m && plaszcze[i].tz > m+s){
      uzyteczne.push_back(i);
    }
  ok = 0;
  gogo(0,0,0);
  cout << (ok ? "TAK" : "NIE") << "\n";
}

void wczytajPlaszcze(){
  sum = 0;
  cin >> n;
  for(int i=0;i<n;i++){
    cin >> plaszcze[i].c >> plaszcze[i].tp >> plaszcze[i].tz;
    sum += plaszcze[i].c;
  }
  sum = min(sum, MAXK);
}

int main(){
  ios_base::sync_with_stdio(0);
  wczytajPlaszcze();
  int p;
  cin >> p;
  while(p--)
    solveSingleCaseBrute();
  return 0;
}
