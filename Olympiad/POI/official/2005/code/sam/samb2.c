/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SAM (Samochodziki)                             *
 *   Plik:                samb2.c                                        *
 *   Autor:               Tomasz Malesiñski <tmal@mimuw.edu.pl>          *
 *   Opis:                Rozwi±zanie niepoprawne zadania Samochodziki   *
 *                        Gdy trzeba od³o¿yæ jaki¶ samochód, bierze      *
 *                        64 losowe z pod³ogi i odk³ada ten spo¶ród nich,*
 *                        który najd³u¿ej nie bêdzie u¿ywany.            *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SEQ_LEN 500000
#define MAX_CARS 100000

int n_cars, max_on_floor, seq_len;
int seq[MAX_SEQ_LEN];

int car_on_floor[MAX_CARS];
int cars_on_floor[MAX_CARS];
int on_floor;

struct node {
  struct node *next;
  int t;
} nodes[MAX_SEQ_LEN];
struct node *head[MAX_CARS];

void read_data(void)
{
  int i;
  scanf("%d%d%d", &n_cars, &max_on_floor, &seq_len);
  for (i = 0; i < seq_len; i++) {
    int a;
    scanf("%d", &a);
    seq[i] = a - 1;
  }
}

int key(int c)
{
  return head[c] ? head[c]->t : seq_len;
}

void build_lists(void)
{
  int t;
  struct node *n = nodes;

  for (t = seq_len - 1; t >= 0; t--) {
    int c = seq[t];
    n->t = t;
    n->next = head[c];
    head[c] = n;
    n++;
  }
}

int solve(void)
{
  int res, t;

  build_lists();
  on_floor = 0;
  res = 0;
  for (t = 0; t < seq_len; t++) {
    int c = seq[t];
    if (!car_on_floor[c]) {
      if (on_floor == max_on_floor) {
        int i, max_i, max_t;
        max_t = -1;
        for (i = 0; i < 64; i++) {
          int c1 = rand() % on_floor;
          if (key(cars_on_floor[c1]) > max_t) {
            max_t = key(cars_on_floor[c1]);
            max_i = c1;
          }
        }
        car_on_floor[cars_on_floor[max_i]] = 0;
        cars_on_floor[max_i] = c;
      } else
        cars_on_floor[on_floor++] = c;

      car_on_floor[c] = 1;
      res++;
    }
    head[c] = head[c]->next;
  }
  return res;
}

int main(void)
{
  read_data();
  printf("%d\n", solve());
  return 0;
}
