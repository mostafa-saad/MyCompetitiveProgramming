/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PAL (Palindromy)                               *
 *   Plik:                pals1.c                                        *
 *   Autor:               Adam Iwanicki                                  *
 *   Opis:                Rozwiazanie nieoptymalne budujace drzewo TRIE  *
 *                        a nastepnie sprawdzajace w sposob silowy czy   *
 *                        pozostala czesc slowa jest palindromem         *
 *                        zlozonosc O(n*a), gdzie n - ilosc slow, a-suma *
 *                        dlugosci                                       *
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

int palindrom(int i, int j) {
  char *wi=slowa+poczatki[i]+j, *wj=slowa+poczatki[i]+dlugosci[i]-1;
  char c = *(wj+1); *(wj+1)='\0';
  *(wj+1)=c;
  while (wi < wj)
    if (*wi++ != *wj--)
      return 0;
  return 1;
}

inline struct Wezel* stworz() {
  return (struct Wezel*) calloc(1,sizeof(struct Wezel));
}

int dodaj(int k) {
  int res=1,i,dl = dlugosci[k];
  char *akt = slowa+poczatki[k];
  struct Wezel *wierzch = &root;
  for (i=0;i<dl;++i,++akt) {
    if (!wierzch->nast[WSK(*akt)])
      wierzch->nast[WSK(*akt)] = stworz();
    wierzch = wierzch->nast[WSK(*akt)];
    if (wierzch->czyKoniec && palindrom(k,i+1))
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
