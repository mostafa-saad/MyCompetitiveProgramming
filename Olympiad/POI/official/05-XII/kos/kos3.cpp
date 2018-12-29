/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KOS (Kosci)                                    *
 *   Plik:                kos3.cpp                                       *
 *   Autor:               Piotr Stañczyk (stanczyk@mimuw.edu.pl)         *
 *   Opis:                Rozwiazanie alternatywne                       *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <vector>
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define VAR(v,i) __typeof(i) v=(i)
#define MAXSIZE 10001

using namespace std;

struct edge {
  int end;                      // Koniec krawedzi (numer wierzcholka)
  bool active;
  int dr;                       // Numer krawedzi w przeciwnym kierunku
};

struct vertex {
  vector < edge > kr;
  int stopien;
};
vector < vertex > graf;

int gr, roz, actmax;
int ilew[MAXSIZE];
bool visited[MAXSIZE];
int kolejka[MAXSIZE];
int kp, kk;
int source[MAXSIZE];
edge *parent[MAXSIZE];
int krawpocz[MAXSIZE];
int krawpoz[MAXSIZE];

void Polacz(int p, int k, int nr)
{
  edge kr;
  krawpocz[nr] = p;
  krawpoz[nr] = graf[p].kr.size();
  kr.end = k;
  kr.active = true;
  kr.dr = graf[k].kr.size();
  graf[p].kr.push_back(kr);
  ilew[graf[p].stopien++]--;
  ilew[graf[p].stopien]++;
  kr.end = p;
  kr.active = false;
  kr.dr = graf[p].kr.size() - 1;
  graf[k].kr.push_back(kr);
}

bool Zmniejsz()
{
  bool zmiana = false;
  kp = -1;
  kk = 0;
  for (int x = 1; x <= gr; x++)
    visited[x] = false;
  for (int x = 1; x <= gr; x++)
    if (graf[x].stopien == actmax) {
      visited[x] = true;
      kolejka[kk] = x;
      parent[x] = 0;
      source[kk] = x;
      kk++;
    }
  while ((++kp) < kk)
    if (graf[source[kp]].stopien == actmax) {
      FOREACH(it, graf[kolejka[kp]].kr) {
        if (it->active && !visited[it->end]) {
          visited[it->end] = true;
          kolejka[kk] = it->end;
          parent[it->end] = &(*it);
          source[kk] = source[kp];
          kk++;
          if (graf[source[kp]].stopien == actmax
              && graf[it->end].stopien < actmax - 1) {
            zmiana = true;
            ilew[graf[it->end].stopien++]--;
            ilew[graf[it->end].stopien]++;
            ilew[graf[source[kp]].stopien--]--;
            ilew[graf[source[kp]].stopien]++;
            for (edge * k = parent[it->end]; k;
                 k = parent[graf[k->end].kr[k->dr].end]) {
              k->active = !k->active;
              graf[k->end].kr[k->dr].active =
                  !graf[k->end].kr[k->dr].active;
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
  graf.resize(gr + 1);
  for (int x = 0; x <= gr; x++)
    graf[x].stopien = 0;
  ilew[0] = gr;
  int p, k;
  for (int x = 0; x < roz; x++) {
    scanf("%d %d", &p, &k);
    Polacz(p, k, x);
  }
  actmax = 10000;
  while (true) {
    if (ilew[actmax] == 0)
      actmax--;
    else if (!Zmniejsz())
      break;
  }
  printf("%d\n", actmax);
  for (int x = 0; x < roz; x++)
    (graf[krawpocz[x]].kr[krawpoz[x]].
     active) ? printf("1\n") : printf("0\n");
  return 0;
}
