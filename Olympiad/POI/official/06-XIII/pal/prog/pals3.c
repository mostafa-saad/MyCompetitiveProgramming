/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PAL (Palindromy)                               *
 *   Plik:                pals3.cpp                                      *
 *   Autor:               Adam Iwanicki                                  *
 *   Opis:                Rozwiazanie optymalne polegajace na obliczaniu *
 *                        pierwiastkow pierwotnych slow, zgodnie z       *
 *                        obserwacja ze konkatenacja bedzie palindromem  *
 *                        o ile slowa sa potegami tego samo slowa.       *
 *                        Nastepnie mozna posortowac te pierwiastki      *
 *                        pierwotne leksykograficznie i policzyc ile     *
 *                        jest tych samych, mozna tez jednak posortowac  *
 *                        je po dlugosci, a nastepnie dodawac je do      *
 *                        drzewa TRIE jednoczesnie je zliczajac zlozonos *
 *                        O(n), gdzie n - suma dlugosci slow             *
 *                        Jednak o zbyt duzej stalej przy zlozonosci     *
 *                        pamieciowej.                                   *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX 2000001
#define ALPHA 26
#define WSK(X) (X-'a')

struct Wezel {
  struct Wezel *nast[ALPHA];
  int ileKoniec;              // ile slow sie konczy w tym miejscu
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

/*
 * funckja obliczajaca pierwiastek pierwotny danego slowa
 * wylicza tablice prefiksow, a nastepnie zgodnie z obserwacja
 * ze pierwiastek to n-p[n] jesli to dzieli n lub cale slowo
 */
int p[MAX];
void pierwiastek(int k) {
  int i=1, q=0, dl=dlugosci[k];
  char *slowo = slowa+poczatki[k];
  p[1]=0;
  while (i<dl) {
    while (q && slowo[i] != slowo[q]) q=p[q-1];
    if (slowo[i] == slowo[q]) q++;
    p[i++]=q;
  }
  dlugosci[k] = (dl%(dl-p[dl-1]))==0 ? dl-p[dl-1] : dl;
}

inline struct Wezel* stworz() {
  return (struct Wezel*) calloc(1,sizeof(struct Wezel));
}

int dodaj(int k) {
  int i,dl = dlugosci[k];
  char *akt = slowa+poczatki[k];
  struct Wezel *wierzch = &root;
  for (i=0;i<dl;++i,++akt) {
    if (!wierzch->nast[WSK(*akt)])
      wierzch->nast[WSK(*akt)] = stworz();
    wierzch = wierzch->nast[WSK(*akt)];
  }
  ++wierzch->ileKoniec;
  return (wierzch->ileKoniec<<1)-1;
}

int main() {
  int i,last=0;
  scanf("%d",&n);
  for(i=0; i<n; ++i) {
    poczatki[i]=last;
    scanf("%d ",dlugosci+i);
    scanf("%s",slowa+last);
    last+=dlugosci[i];
    pierwiastek(i);
  }
  posortuj();

  for(i=0; i<n ; ++i)
    wynik+=dodaj(kolejnosc[i]);

  printf("%lld\n", wynik);
  return 0;
}
