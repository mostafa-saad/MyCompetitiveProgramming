/*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Szpiedzy                                       *
 *   Plik:                szp.c                                          *
 *   Autor:               Tomasz Malesiñski                              *
 *************************************************************************/

#include <stdio.h>

#define MAX_SPIES 1000000

/* liczba szpiegow */
int N;
/* kogo sledzi */
int Trace[MAX_SPIES];
/* czy jest juz skojarzony */
char M[MAX_SPIES];
/* ilu go sledzi */
int Deg[MAX_SPIES];
/* kolejka szpiegow, ktorych nikt nie sledzi */
int Q[MAX_SPIES];
int QH, QT;

void ReadData(void)
{
  int i, a;
  scanf("%d", &N);
  for (i = 0; i < N; i++) {
    scanf("%d", &a);
    Trace[i] = a - 1;
  }
}

int main(void)
{
  int i, s, t, r;
  ReadData();

  /* policz, ilu szpiegow sledzi kazdego szpiega */
  for (i = 0; i < N; i++) Deg[Trace[i]]++;
  /* wrzuc do kolejki szpiegow, ktorych nikt nie sledzi */
  for (i = 0; i < N; i++)
    if (!Deg[i]) Q[QH++] = i;

  r = 0;
  while (QT < QH) {
    /* wez kolejnego szpiega, ktorego nikt nie sledzi */
    s = Q[QT++];
    /* jesli szpieg sledzony przez niego nie jest jeszcze w skojarzeniu
     * to dodaj ich do skojarzenia i sprawdz, czy sledzony przez sledzonego
     * jest teraz nie sledzony przez nikogo */
    if (!M[Trace[s]]) {
      r++;
      M[s] = M[Trace[s]] = 1;
      t = Trace[Trace[s]];
      if (!M[t] && --Deg[t] == 0) Q[QH++] = t;
    }
  }

  /* nie ma szpiegow, ktorych nikt nie sledzi -- zostaly cykle */
  for (i = 0; i < N; i++)
    if (!M[i]) {
      s = i;
      while (!M[s] && !M[Trace[s]]) {
	r++;
	M[s] = M[Trace[s]] = 1;
	s = Trace[Trace[s]];
      }
    }

  printf("%d\n", r);
  return 0;
}
