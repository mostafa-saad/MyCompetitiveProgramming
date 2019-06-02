/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Nim z utrudnieniem                                 *
 *   Autor programu:       Pawel Parys                                        *
 *   Zlozonosc czasowa:    O(m*d)                                             *
 *   Opis:                 Rozwiazanie niepoprawne bez odjecia jeden od wyniku*
 *****************************************************************************/


#include <cstdio>
#include <algorithm>

using namespace std;

#define REP(a,n) for (int a = 0; a<(n); ++a)

///////////////////

#define MOD (1000*1000*1000+7)
#define MAXN 500000
#define MAXVAL (1<<20) // >1.000.000

int N, D, stosy[MAXN];
int tab[MAXVAL][10]; // [v][d] - na ile sposobow mozna uzyskac xor v przy liczbie usunietych stosow przystajacej do d
int cursize = 1; // potega dwojki wieksza niz ostatnie niezerowe pole tablicy

int main() {
  scanf("%d%d", &N, &D);
  REP(a, N)
    scanf("%d", stosy+a);
  sort(stosy, stosy+N);
  tab[0][0] = 1; // pozostale komorki tablicy sa zainicjowane na 0
  REP(a, N) {
    REP(v, cursize) {
      int v2 = v^stosy[a];
      if (v2>v) {
        int pom[2][10];
        REP(d, D) {
          pom[0][d] = (tab[v2][d]+tab[v][(d+D-1)%D])%MOD;
          pom[1][d] = (tab[v][d]+tab[v2][(d+D-1)%D])%MOD;
        }
        REP(d, D) {
          tab[v][d] = pom[0][d];
          tab[v2][d] = pom[1][d];
        }
      }
    }
    while (cursize<=stosy[a])
      cursize *= 2;
  }
//!!!!  if (N%D==0) // odejmujemy 1 sposob - wszystkie stosy puste
//!!!!    tab[0][0] = (tab[0][0]+MOD-1)%MOD;
  printf("%d\n", tab[0][0]);
}
