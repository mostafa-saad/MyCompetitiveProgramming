/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Stacja (STA)                                              *
 *   Plik:     stachk.cpp                                                *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Program weryfikujacy poprawnosc wyjscia wygenerowanego    *
 *             przez program zawodnika, format:                          *
 *             ./stachk.e in out_zawodnika out_wzorcowy                  *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

FILE *wej, *zaw, *wzo;

#define MAX_N 1000000
#define INFTY 100000000

int n;
vector<int> t[MAX_N];
int d[MAX_N];
queue<int> kol;

void bfs(int v) {
    for(int i=0; i<n; i++) d[i]=INFTY;
    d[v]=0;
    kol=queue<int>();
    kol.push(v);
    while (!kol.empty()) {
        int w=kol.front();
        kol.pop();
        for(int i=0; i<(int)t[w].size(); i++)
          if (d[t[w][i]]==INFTY) {
              d[t[w][i]] = d[w] + 1;
              kol.push(t[w][i]);
            }
    }
}


int main(int argc, char **argv) {
  if (argc !=4) {
    printf("Sposob uzycia: %s input rozw_zawodnika rozw_wzorcowe\n",argv[0]);
    return 0;
  }

  wej = fopen(argv[1], "r");
  zaw = fopen(argv[2], "r");
  wzo = fopen(argv[3], "r");

  /* Wejscie */
  fscanf(wej, "%d", &n);
  int a,b;
  for(int i=0; i<n-1; i++) {
    fscanf(wej,"%d%d",&a,&b);
    a--; b--;
    t[a].push_back(b);
    t[b].push_back(a);
  }
  
  int v_wzo, v_zaw;
  /* Wyjscie wzorcowe */
  fscanf(wzo,"%d",&v_wzo);

  /* Wyjscie zawodnika */
  fscanf(zaw, "%d", &v_zaw);
  if (v_zaw<1 || v_zaw>n)  {
    printf("Wierzcholki sa numerowane od 1 do %d.\n", n);
    fclose(wej);
    fclose(zaw);
    fclose(wzo);
    return 1;
  }

  char st[3];
  if (fscanf(zaw,"%s",st)>0) {
    printf("Smieci na koncu pliku: %c.\n", st[0]);
    fclose(wej);
    fclose(zaw);
    fclose(wzo);
    return 1;
  }

  /* Wyznaczenie jakosci wyjsc */
  bfs(v_wzo-1);
  long long wyn=0LL;
  for(int i=0; i<n; i++) wyn+=d[i];

  bfs(v_zaw-1);
  long long akt=0LL;
  for(int i=0; i<n; i++) akt+=d[i];

  /* Porownanie jakosci wyjsc */
  if (akt>wyn) {
    puts("Wyjscie zawodnika lepsze niz wzorcowe (ZLE!!!).");
    fclose(wej);
    fclose(zaw);
    fclose(wzo);
    return 1;
  } else if (akt<wyn) {
    puts("Wyjscie nie jest optymalne.");
    fclose(wej);
    fclose(zaw);
    fclose(wzo);
    return 1;
  } else {
    puts("OK");
    fclose(wej);
    fclose(zaw);
    fclose(wzo);
  }
  return 0;
}
