/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PAL (Palindromy)                               *
 *   Plik:                pals8.c                                        *
 *   Autor:               Adam Iwanicki                                  *
 *   Opis:                Rozwiazanie wzorcowe polegajace wykorzystaniu  *
 *                        w rozwiazaniu drzew TRIE, jednak do stwierdzan *
 *                        czy pozostaly fragment slowa jest palindromem  *
 *                        uzywa preprocessingu opartego na algorytmie    *
 *                        KMP, jednak o zbyt duzym zapotrzebowaniu na    *
 *                        pamiec                                         *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX 2000001
#define ALPHA 26
#define WSK(X) (X-'a')

struct Wezel {
  struct Wezel *nast[ALPHA];
  int czyKoniec;              // czy dany wezel jest koncowy
};

char slowa[MAX];
int poczatki[MAX],dlugosci[MAX],kolejnosc[MAX],n;
int palindromy[MAX], p[MAX];
long long int wynik=0;
struct Wezel root;

void posortuj() {
  int i,last=0,tmp;
  int pom[MAX];
  for(i=0;i<MAX;pom[i++]=0);
  for(i=0;i<n; ++pom[dlugosci[i++]]);
  for(i=0;i<MAX; tmp=pom[i],pom[i++]=last,last+=tmp);
  for(i=0;i<n; kolejnosc[pom[dlugosci[i]]++]=i++);
}

void preprocess(int k) {
  // KMP prefix function part
  int i, q=0, dl=dlugosci[k];
  char *slowo = slowa+poczatki[k];

  p[0]=0;
  for (i=1;i<dl;++i) {
    while (q && slowo[i] != slowo[q]) q=p[q-1];
    if (slowo[i] == slowo[q]) q++;
    p[i]=q;
  }

  for(i=0; i<dl; palindromy[i++]=0);
  i=p[dl-1];
  palindromy[dl]=1;
  palindromy[0]=1;
  while (i) {
    palindromy[i]=1;
    i=p[i-1];
  }
}

inline struct Wezel* stworz() {
  return (struct Wezel*) calloc(1,sizeof(struct Wezel));
}

int dodaj(int k) {
  int res=1,i,dl = dlugosci[k];
  char *akt = slowa+poczatki[k];
  struct Wezel *wierzch = &root;
  preprocess(k);
  for (i=0;i<dl;++i,++akt) {
    if (!wierzch->nast[WSK(*akt)])
      wierzch->nast[WSK(*akt)] = stworz();
    wierzch = wierzch->nast[WSK(*akt)];
    if (wierzch->czyKoniec && palindromy[dl-i-1])
      res+=2;
  }
  wierzch->czyKoniec=k+1;
  return res;
}

int main() {
  int i,last=0;
  scanf("%d",&n);
  for(i=0; i<n; ++i) {
    poczatki[i]=last;
    scanf("%d ",dlugosci+i);
    scanf("%s",slowa+last);
    last+=dlugosci[i];
  }
  posortuj();

  for(i=0; i<n ; ++i)
    wynik+=dodaj(kolejnosc[i]);

  printf("%lld\n", wynik);
  return 0;
}
