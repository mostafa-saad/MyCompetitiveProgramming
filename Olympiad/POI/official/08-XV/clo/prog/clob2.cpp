/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clob2.cpp                                                 *
 *   Autor:    Adam Iwanicki                                             *
 *   Opis:     Rozwiazanie niepoprawne, ktore w takcie wczytywania       *
 *             krawedzi przypisuje ja do wolnego jeszcze wierzcholka.    *
 *             Zlozonosc O(n+m).                                         *
 *                                                                       *
 *************************************************************************/

#include<cstdio>

const int MAXN = 100000;

int vertices[MAXN];

int main()
{
  int n,m;
  scanf("%d %d", &n, &m );
  for(int i=0; i<n; ++i) {
    vertices[i] = -1;
  }
  for(int i=0; i<m; ++i) {
    int a,b;
    scanf("%d %d", &a, &b);
    --a, --b;
    if( -1 == vertices[a] ) {
      vertices[a] = b;
    } else if( -1 == vertices[b] ) {
      vertices[b] = a;
    }
  }
  bool isPossible = true;
  for(int i=0; i<n; ++i) {
    if( -1 == vertices[i] ) {
      isPossible = false;
      break;
    }
  }
  if( isPossible ) {
    printf("TAK\n");
    for(int i=0; i<n; ++i) {
      printf("%d\n", vertices[i]+1);
    }
  } else {
    printf("NIE\n");
  }
}
