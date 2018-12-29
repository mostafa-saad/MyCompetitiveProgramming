/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PAL (Palindromy)                               *
 *   Plik:                pals4.c                                        *
 *   Autor:               Adam Iwanicki                                  *
 *   Opis:                Rozwiazanie alternatywn polegajace na budowie  *
 *                        drzewa typu TRIE, do ktorego dodawane sa       *
 *                        palindromy w niemalejacym porzadku wzgledem    *
 *                        dlugosci, dla kazdego slowa tez za pomoca      *
 *                        algorytmy Manahera obliczane sa na poczatku    *
 *                        promienie palindromow, tak aby w miejscu gdzie *
 *                        napotkamy koniec innego krotszego palindromu   *
 *                        mozna bylo szybko odpowiedziec na pytanie czy  *
 *                        pozostaly fragment jest palindromem, zlozonosc *
 *                        O(n), gdzie n - suma dlugosci slow             *
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
int palParzyste[MAX], palNieparzyste[MAX];
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

inline int palindrom(int i, int j) {
  int dl = dlugosci[i];
  if ((dl-j)&1)
    return palNieparzyste[j+((dl-j)>>1)] >= (dl-j)>>1;
  else
    return (palParzyste[j+((dl-j)>>1)] >= (dl-j)>>1);
}

inline int min(const int a, const int b) { return (a<b)?a:b; }

inline int max(const int a, const int b) { return (a<b)?b:a; }

void Manacher(int s, int niep, int *r) {
  int n=dlugosci[s],i=1,j=0,k;
  char *x= slowa+poczatki[s];
  for (i=0;i<n;r[i++]=0);
  i=1;
  while(i<n) {
    while(i+j<=n && i-j>0 && x[i-j-1]==x[i+j+niep]) j++;
    r[i]=j;
    k=1;
    while(r[i-k]!=r[i]-k && k<=j) {
      r[i+k] = min(r[i-k], r[i]-k); k++;
    }
    j=max(0,j-k); i+=k;
  }
}

void preprocess(int k) {
  int i, dl=dlugosci[k];
  for(i=0;i<dl;palNieparzyste[i]=0,palParzyste[i++]=0);
  Manacher(k,0,palParzyste);
  Manacher(k,1,palNieparzyste);
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
