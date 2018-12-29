/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kamyki (KAM)                                              *
 *   Plik:     kams1.cpp                                                 *
 *   Autor:    Szymon Wrzyszcz                                           *
 *   Opis:     Rozwiazanie wykladnicze bez spamietywania                 *
 *                                                                       *
 *                                                                       *
 *************************************************************************/
#include <cstdio>

const int MAXN = 1000; // max liczba kupek kamieni

int n; // liczba kupek kamieni

// sprawdza czy nie ma juz zadnych kamieni
int koniec(int *v) {
  for (int i=0; i<n; i++)
    if (v[i] > 0)
      return 0;
  return 1;
}

// zwraca 1 gdy uklad v jest wygrywajacy, 0 wpp
int wygra(int *v) {
  if (koniec(v))
    return 0;
  for (int i=0; i<n; i++) {
    int k = (i==0)?(v[0]):(v[i]-v[i-1]);
    while (k >= 1) {
      v[i] -= k;
      if (!wygra(v)) {
	v[i] += k;
	return 1;
      }
      v[i] += k;
      k--;
    }
  }
  return 0;
}

int main() {
  int u, v[MAXN];
  scanf("%d", &u);
  while (u--) {
    scanf("%d", &n);
    for (int i=0; i<n; i++)
      scanf("%d", &v[i]);
    puts(wygra(v)?"TAK":"NIE");
  }
  return 0;
}
