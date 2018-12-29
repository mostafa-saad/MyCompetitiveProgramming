/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Nim z utrudnieniem                                 *
 *   Autor programu:       Pawel Parys                                        *
 *   Zlozonosc czasowa:    O(2^n)                                             *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                                                                            *
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
int wynik = 0;

void probuj(int nr, int xorsuma, int ile_us, bool czy_zostal) {
  if (nr==N) {
    if (xorsuma==0 && ile_us%D==0 && czy_zostal)
      ++wynik;
    return;
  }
  probuj(nr+1, xorsuma, ile_us+1, czy_zostal); // usuwam
  probuj(nr+1, xorsuma^stosy[nr], ile_us, 1); // zostawiam
}

int main() {
  scanf("%d%d", &N, &D);
  REP(a, N)
    scanf("%d", stosy+a);
  probuj(0, 0, 0, 0);
  printf("%d\n", wynik);
}
