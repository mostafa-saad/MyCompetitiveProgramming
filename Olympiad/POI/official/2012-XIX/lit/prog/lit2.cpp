/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Litery                                           *
 *   Autor:             Jakub Radoszewski                                *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                      Zliczamy inwersje przez Mergesort                *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
using namespace std;

#define MAXN 1000005   
long long wynik;
int n, temp;
vector<int> tab_u[255], tab_w[255];
char u[MAXN], w[MAXN];

int p[MAXN], ciag[MAXN];

void merge(int a, int c, int b){
  int k1 = c - a + 1, k2 = b - c;
  int i1 = 0, i2 = 0;
  int *ciag1 = p + a;
  int *ciag2 = p + c + 1;
  while (i1 < k1 || i2 < k2){
    if (i1 >= k1){
      ciag[i1 + i2] = ciag2[i2++];
    } else if (i2 >= k2){
      wynik += i2;
      ciag[i1 + i2] = ciag1[i1++];
    } else if (ciag1[i1] < ciag2[i2]){
      wynik += i2;
      ciag[i1 + i2] = ciag1[i1++];
    } else{
      ciag[i1 + i2] = ciag2[i2++];
    }
  }
  for (int i = a; i <= b; ++i) p[i] = ciag[i - a];
}

void mergesort(int a, int b){
  if (a == b) return;
  int c = (a + b) / 2;
  mergesort(a, c);
  mergesort(c + 1, b);
  merge(a, c, b);
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

  mergesort(0, n - 1);

  temp = printf("%lld\n", wynik);

  return 0;
}
