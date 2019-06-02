/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Nim z utrudnieniem                                 *
 *   Autor programu:       Pawel Parys                                        *
 *   Zlozonosc czasowa:    O(m*d)                                             *
 *   Opis:                 Rozwiazanie nieoptymalne pamieciowo                *
 *                         tablica 2x wieksza niz w rozwiazaniu wzorcowem     *
 *                         nie miesci sie w limicie pamieci                   *
 *****************************************************************************/

#include <cstdio>
#include <algorithm>

using namespace std;

#define REP(a,n) for (int a = 0; a<(n); ++a)

///////////////////

#define MOD (1000*1000*1000+7)
#define MAXN 500000

int N, D, stosy[MAXN];
int *tablica;
int maxsize = 1; // potega dwojki wieksza niz wszystkie rozmiary stosow
int cursize = 1; // potega dwojki wieksza niz ostatnie niezerowe pole tablicy

#define tab(k, v, d) tablica[(k)*maxsize*D+(v)*D+(d)] // tab(k, v, d) = na ile sposobow mozna uzyskac xor v przy liczbie usunietych stosow przystajacej do d

int main() {
  scanf("%d%d", &N, &D);
  int maxsize = 1;
  REP(a, N) {
    scanf("%d", stosy+a);
    while (maxsize<=stosy[a])
      maxsize *= 2;
  }
  tablica = new int[(N+1)*maxsize*D];
//  sort(stosy, stosy+N); --- bez sortowania, wczesnie pojawiaja sie duze stosy
  tab(0, 0, 0) = 1; // pozostale komorki tablicy sa zainicjowane na 0
  REP(a, N) {
    while (cursize<=stosy[a])
      cursize *= 2;
    REP(v, cursize)
      REP(d, D)
        tab(a+1, v, d) = (tab(a, v^stosy[a], d)+tab(a, v, (d+D-1)%D))%MOD;
  }
  if (N%D==0) // odejmujemy 1 sposob - wszystkie stosy puste
    tab(N, 0, 0) = (tab(N, 0, 0)+MOD-1)%MOD;
  printf("%d\n", tab(N, 0, 0));
}
