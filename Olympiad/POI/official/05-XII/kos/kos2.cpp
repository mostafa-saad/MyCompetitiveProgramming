/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KOS (Kosci)                                    *
 *   Plik:                kos2.cpp                                       *
 *   Autor:               Piotr Stañczyk (stanczyk@mimuw.edu.pl)         *
 *   Opis:                Rozwiazanie alternatywne                       *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <algorithm>
#define list_for_each(pos, head) for (pos = (head)->next; pos != (head); pos = pos->next)
#define INIT_LIST_HEAD(ptr) (ptr)->next = (ptr); (ptr)->prev = (ptr);
#define list_entry(ptr, type, member) ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))
#define VertexNr(v) ((vertex*) v - graf)
#define MAXSIZE 10001

using namespace std;

struct vertex;
struct list_head {
  list_head *next, *prev;
};

struct edge {
  list_head kraw;               // Lista dwukierunkowa krawedzi
  vertex *beg, *end;            // Wierzcholek stanowiacy poczatek / koniec krawedzi 
  bool rotated;
};

struct vertex {
  list_head st_list;            // Lista wierzcholkow o tym samym stopniu
  list_head kraw;               // Lista krawedzi dla wierzcholka
  int stopien;                  // Stopien wychodzacy wierzcholka
  bool visited;                 // Czy wierzcholek byl odpowiedzony przez BFS
};

inline bool list_empty(list_head * head)
{
  return head->next == head;
}

vertex graf[MAXSIZE];

inline void list_add(list_head * new_el, list_head * head)
{
  if (new_el->next != new_el || new_el->prev != new_el)
    exit(1);
  new_el->next = head->next;
  new_el->prev = head;
  head->next->prev = new_el;
  head->next = new_el;
}

static inline void list_del(list_head * entry)
{
  if (entry->next == entry || entry->prev == entry)
    exit(1);
  entry->next->prev = entry->prev;
  entry->prev->next = entry->next;
  entry->next = entry;
  entry->prev = entry;
}

edge kraw[MAXSIZE];
list_head stopien[MAXSIZE];     // Lista list wierzcholkow o okreslonym stopniu

int gr, roz, actmax;
int kp, kk;
vertex *kolejka[MAXSIZE];
vertex *source[MAXSIZE];
edge *parent[MAXSIZE];

void Polacz(int p, int k, int nr)
{
  graf[p].stopien++;
  kraw[nr].beg = &graf[p];
  kraw[nr].end = &graf[k];
  kraw[nr].rotated = false;
  list_add(&kraw[nr].kraw, &graf[p].kraw);
}

bool Zmniejsz()
{
  bool zmiana = false;
  list_head *it;
  kp = -1;
  while (kk--)
    kolejka[kk]->visited = false;
  kk++;
  list_for_each(it, &stopien[actmax]) {
    source[kk] = (vertex *) it;
    source[kk]->visited = true;
    parent[VertexNr(it)] = NULL;
    kolejka[kk++] = (vertex *) it;
  }
  while ((++kp) < kk)
    if (source[kp]->stopien == actmax) {
      list_for_each(it, &(kolejka[kp]->kraw)) {
        if (!(((edge *) it)->end->visited)) {
          kolejka[kk] = ((edge *) it)->end;
          kolejka[kk]->visited = true;
          parent[VertexNr(kolejka[kk])] = (edge *) it;
          source[kk++] = source[kp];
          if (kolejka[kk - 1]->stopien < actmax - 1) {
            zmiana = true;
            list_del(&kolejka[kk - 1]->st_list);
            list_del(&source[kp]->st_list);
            kolejka[kk - 1]->stopien++;
            source[kp]->stopien--;
            list_add(&kolejka[kk - 1]->st_list,
                     &stopien[kolejka[kk - 1]->stopien]);
            list_add(&source[kp]->st_list, &stopien[source[kp]->stopien]);
            for (edge * k = (edge *) it; k; k = parent[VertexNr(k->end)]) {
              list_del(&k->kraw);
              swap(k->beg, k->end);
              k->rotated = !k->rotated;
              list_add(&k->kraw, &k->beg->kraw);
            }
            break;
          }
        }
      }
    }
  return zmiana;
}

int main()
{
  scanf("%d %d", &gr, &roz);
  for (int x = 1; x <= gr; x++) {
    INIT_LIST_HEAD(&graf[x].kraw);
    INIT_LIST_HEAD(&graf[x].st_list);
    graf[x].stopien = 0;
    graf[x].visited = false;
  }
  for (int x = 0; x < MAXSIZE; x++) {
    INIT_LIST_HEAD(&stopien[x]);
    INIT_LIST_HEAD(&kraw[x].kraw);
  }
  int p, k;
  for (int x = 0; x < roz; x++) {
    scanf("%d %d", &p, &k);
    Polacz(p, k, x);
  }
  for (int x = 1; x <= gr; x++)
    list_add(&graf[x].st_list, &stopien[graf[x].stopien]);

  actmax = MAXSIZE - 1;
  kk = 0;
  while (true) {
    if (list_empty(&stopien[actmax]))
      actmax--;
    else if (!Zmniejsz())
      break;
  }
  printf("%d\n", actmax);
  for (int x = 0; x < roz; x++)
    kraw[x].rotated ? printf("0\n") : printf("1\n");
  return 0;
}
