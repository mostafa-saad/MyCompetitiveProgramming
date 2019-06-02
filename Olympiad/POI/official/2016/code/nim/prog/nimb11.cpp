/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Nim z utrudnieniem                                 *
 *   Autor programu:       Pawel Parys                                        *
 *   Zlozonosc czasowa:    O(max(a_i)*log(max(a_i))*d)                        *
 *   Opis:                 Rozwiazanie dla d <= 2                             *
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
bool tab[MAXVAL][10]; // [v][d] - czy mozna uzyskac xor v przy liczbie stosow pozostalej w grze przystajacej do d
    // UWAGA - tutaj d to liczba stosow pozostalych, a nie usunietych (w przeciwienstwie do pozostalych programow)
int cursize = 1; // potega dwojki wieksza niz ostatnie niezerowe pole tablicy

int main() {
  scanf("%d%d", &N, &D);
  REP(a, N)
    scanf("%d", stosy+a);
//!!!  sort(stosy, stosy+N); - nie sortujemy (z sortowaniem byloby szybciej)
  tab[0][0] = 1; // pozostale komorki tablicy sa zainicjowane na 0
  int mnoznik = 1;
  REP(a, N) {
    if (tab[stosy[a]][1%D])
      mnoznik = mnoznik*2%MOD;
    else
      REP(v, cursize)
        REP(d, D)
          if (tab[v][d])
            tab[v^stosy[a]][(d+1)%D] = 1;
    while (cursize<=stosy[a])
      cursize *= 2;
  }
  if (!tab[0][N%D])
    mnoznik = 0;
  if (N%D==0) // odejmujemy 1 sposob - wszystkie stosy puste
    mnoznik = (mnoznik+MOD-1)%MOD;
  printf("%d\n", mnoznik);
}
