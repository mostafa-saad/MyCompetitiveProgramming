/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Meteory                                          *
 *   Autor:             Blazej Osinski                                   *
 *   Zlozonosc czasowa: O(k * m)                                         *
 *   Opis:              Rozwiazanie powolne, silowe, ale                 *
 *                      z optymalizacjami w przypadku malej liczby       *
 *                      panstw i wielu szerokich zapytan                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
using namespace std;

int __abc;
#define scanf __abc=scanf

const int N = 300007;

int n, m, lo;
int pot[N], wl[N], wyn[N], licz[N], klicz[N]; 
/*
   pot[i]  - zapotrzebowanie i-tego pañstwa na meteoryty
   wl[i]   - wla¶ciciel i-tej stacji
   wyn[i]  - odpowied¼ dla i-tego pañstwa
   licz[i] - liczba stacji posiadnych przez i-te pañstwo
*/

// Funkcja symuluje upadek po w meteorytów na pola l..r w ruchu nr.
void zrzuc(int nr, int l, int r, int w){
  for (int i = l; i <= r; i++)
    if (pot[wl[i]] > 0) {
      pot[wl[i]] -= w;
      if (pot[wl[i]] <= 0)
        wyn[wl[i]] = nr;
    }
}

// Zwiêksza a modulo m.
inline void inc(int& a)
{
  a++;
  if (a >= m)
    a = 0;
}

int main()
{
  // Wczytanie danych.
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i++) {
    int a;
    scanf("%d",&a);
    wl[i] = a-1;
    licz[a-1]++;
  }
  for (int i = 0; i < n; i++) {
    scanf("%d",&pot[i]);
  }

  // Wczytywanie i przetwarzanie opadów. 
  scanf("%d", &lo);
  for (int nr = 1; nr <= lo; nr++) {
    int l, r, w, dist;
    scanf("%d %d %d",&l, &r, &w);
    l--;
    r--;
    dist = r - l + 1;
    if (dist < 0)
      dist += m;
    if(dist > n + m - dist){
      // Wyj±tkowo d³ugie zapytanie, op³aca siê zliczyæ w inny sposób.
      for (int i = 0; i < n; i++)
        klicz[i] = licz[i];
      // Zmniejszamy elementy tablicy klicz[] odpowiadaj±ce pañstwom poza przedzia³em l..r.
      int j = r;
      inc(j);
      for (; j != l; inc(j))
        klicz[wl[j]]--;
      for (int i = 0; i < n; i++)
        if (pot[i] > 0){
          if(pot[i]/w <= klicz[i] && pot[i] <= (long long)klicz[i]*(long long)w){
            // ¦rodkowy warunek jest potrzebny bo iloczyn mo¿e przekraczaæ zakres inta.
            pot[i] = 0;
            wyn[i] = nr;
          }
          else
            pot[i] -= klicz[i]*w;
        }
    }
    else{
      // Normalny przypadek.
      if (l <= r)
        zrzuc(nr, l, r, w);
      else {
        zrzuc(nr, 0, r, w);
        zrzuc(nr, l, m-1, w);
      }
    }
  }

  // Wypisanie wyniku.
  for (int i = 0; i < n; i++){
    if(wyn[i] > 0)
      printf("%d\n", wyn[i]);
    else
      printf("NIE\n");
  }
  return 0;
}
