/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Szatnia                                          *
 *   Autor:             Michal Zgliczynski                               *
 *   Zlozonosc czasowa: O(p*n*MaxK)                                      *
 *   Opis:              Rozwiazanie nieoptymalne                         *
 *                                                                       *
 *************************************************************************/

#include <iostream>
using namespace std;

const int MAXN = 1000, MAXP = 1000000, MAXK = 100000;
const int inf = 2100000000; // musi byc wieksze id max(m_i + s_i)

struct plaszcz{
  int c, tp, tz;
};

plaszcz plaszcze[MAXN];
bool F[MAXK];
int n,sum;

void solveSingleCase(){
  int m,k,s;
  cin >> m >> k >> s;
  if(k > sum){ cout << "NIE\n"; return ; }
  for(int i=0;i<=k;i++)
    F[i] = 0;
  F[0] = 1;
  for(int i=0;i<n;i++)
    if(plaszcze[i].tp <= m && plaszcze[i].tz > m+s)
      for(int j=k;j>=plaszcze[i].c;j--)
        F[j] |= F[j - plaszcze[i].c];
  cout << (F[k] ? "TAK" : "NIE") << "\n";
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
    solveSingleCase();
  return 0;
}
