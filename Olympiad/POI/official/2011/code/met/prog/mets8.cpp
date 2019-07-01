/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Meteory                                          *
 *   Autor:             Blazej Osinski                                   *
 *   Zlozonosc czasowa: O(n * k * lg(k))                                 *
 *   Opis:              Rozwiazanie powolne - dla kazdego panstwa        *
 *                      przegladamy wszystkie opady, wyszukujac          *
 *                      binarnie liczbe "obdarowanych" stacji            *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;

int __abc;
#define scanf __abc=scanf

const int N = 300007;

struct Zapytanie
{
  int l, r, a;
} zap[N];

static const int INF = 1000000000;

int n, m, pot[N], z, odp[N];
// Stacje posiadane przez konkretne panstwa.
vector<int> stacje[N]; 

// Funkcja zwraca liczbe stacji państwa nr pomiędzy l i r (wiadomo, że l <= r).
int inline przeciecie(int nr, int l, int r){
  return (--upper_bound(stacje[nr].begin(), stacje[nr].end(), r))-lower_bound(stacje[nr].begin(), stacje[nr].end(), l)+1;
}

int main()
{
  // Wczytywanie danych. 
  scanf("%d %d", &n, &m);
  for(int i = 0; i < m; i++){
    scanf("%d", &z);
    z--;
    stacje[z].push_back(i);
  }
  for(int i = 0; i < n; i++)
    scanf("%d", &pot[i]);
  
  // Wczytywanie zapytań.
  scanf("%d", &z);
  for(int i = 0; i < z; i++){
    scanf("%d %d %d", &zap[i].l, &zap[i].r, &zap[i].a);
    zap[i].l--;
    zap[i].r--;
  }

  // Dla każdego państwa obliczamy wielkość kolejnych opadów.
  for(int i = 0; i < n; i++){
    int zostalo = pot[i]; 
    odp[i] = z;
    for(int j = 0; j < z; j++){
      int wp = 0; // wielkość przecięcia
      if(zap[j].l <= zap[j].r){
        wp = przeciecie(i, zap[j].l, zap[j].r);
      }
      else{
        wp = przeciecie(i, 0, zap[j].r) + przeciecie(i, zap[j].l, m-1);
      }
      // Dzielenie by uniknąć stosowania long longów
      if (wp >= (zostalo + zap[j].a - 1) / zap[j].a){
        odp[i] = j;
        break;
      }
      zostalo -= zap[j].a * wp;
    }
  }

  // Wypisanie wyniku.
  for(int i = 0; i < n; i++){
    if(odp[i] < z)
      printf("%d\n", odp[i]+1);
    else
      printf("NIE\n");
  }
  return 0;
}
