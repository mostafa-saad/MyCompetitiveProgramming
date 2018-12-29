/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Litery                                           *
 *   Autor:             Jakub Radoszewski                                *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                      Zliczamy inwersje metoda "parzyste-nieparzyste"  *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
using namespace std;

#define MAXN 1000005   
int n, temp;
vector<int> tab_u[255], tab_w[255];
char u[MAXN], w[MAXN];

int p[MAXN], Nieparzyste[MAXN + 1];

long long inwersje(){
  long long wynik = 0;
  int ile_zer = 0;
  while (ile_zer < n){
    for (int i = 0; i <= n; ++i) Nieparzyste[i] = 0;
    ile_zer = 0;
    for (int i = 0; i < n; ++i){
      if (p[i] % 2) ++Nieparzyste[p[i]];
      else wynik += Nieparzyste[p[i] + 1];
      p[i] /= 2;
      if (!p[i]) ++ile_zer;
    }
  }
  return wynik;
}

int main(){
  temp = scanf("%d", &n);
  temp = scanf("%s", u);
  for (int i = n - 1; i >= 0; --i)
    tab_u[int(u[i])].push_back(i);
  temp = scanf("%s", w);
  for (int i = n - 1; i >= 0; --i)
    tab_w[int(w[i])].push_back(i);

  for (int ch = 'A'; ch <= 'Z'; ++ch)
    for (int i = 0; i < (int)tab_u[ch].size(); ++i)
      p[tab_u[ch][i]] = tab_w[ch][i];

  temp = printf("%lld\n", inwersje());

  return 0;
}
