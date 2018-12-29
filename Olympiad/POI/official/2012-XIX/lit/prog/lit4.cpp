/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Litery                                           *
 *   Autor:             Jakub Radoszewski                                *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                      Zliczamy inwersje metoda "dziel i zwyciezaj"     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
using namespace std;

#define MAXN 1000005   
int n, temp;
vector<int> tab_u[255], tab_w[255];
char u[MAXN], w[MAXN];

int p[MAXN], pom[MAXN];

long long inwersje(int x, int y){
  if (x == y) return 0ll;
  int i1 = 0, i2 = 0;
  long long wynik = 0;
  int z = (x + y) / 2;
  int *ciag = p;
  int *ciag1 = pom + x;
  int *ciag2 = pom + z + 1;
  for (int i = x; i <= y; ++i)
    if (ciag[i] <= z){
      wynik += i2;
      ciag1[i1++] = ciag[i];
    } else{
      ciag2[i2++] = ciag[i];
    }
  for (int i = x; i <= y; ++i) p[i] = pom[i];
  return wynik + inwersje(x, z) + inwersje(z + 1, y);
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

  temp = printf("%lld\n", inwersje(0, n - 1));

  return 0;
}
