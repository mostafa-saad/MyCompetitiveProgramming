/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PAL (Palindromy)                               *
 *   Plik:                palb0.c                                        *
 *   Autor:               Adam Iwanicki                                  *
 *   Opis:                Rozwiazanie niepoprawne, polegajace na oblicze *
 *                        pierwiastkow pierwotnych slow, zgodnie z       *
 *                        obserwacja ze konkatenacja bedzie palindromem  *
 *                        o ile slowa sa potegami tego samo slowa.       *
 *                        Jednak robiace to w sposob niepoprawny stosuja *
 *                        heurystyke ze jesli pierwiastek jest dluzszy   *
 *                        od ustalonej dlugosci to jest calym slowem.    *
 *                        Nastepnie mozna posortowac te pierwiastki      *
 *                        pierwotne leksykograficznie, a nastepnie zlicz *
 *                        ile jest tych samych slow sortujac je          *
 *                        leksykograficznie zlozonosc O(n), gdzie        *
 *                        n - suma dlugosci slow                         *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX 2000001
#define ALPHA 26
#define WSK(X) (X-'a'+1)
#define CALE 20

char slowa[MAX];
int poczatki[MAX],dlugosci[MAX],kolejnosci[2][MAX],*kolejnosc,n;
long long int wynik=0;

/*
 * sortuje pierwiastki slow leksykograficznie 
 */
void posortuj() {
  int i,j,last=0,tmp,akt=0,*res1=kolejnosci[0],*res2=kolejnosci[1];
  int pom[ALPHA+1];
  int maxdl = dlugosci[0];
  for(i=0;i<n; ++i)
    if (dlugosci[i]>maxdl) maxdl=dlugosci[i];
  for(i=0;i<n; ++i) res1[i]=i;

  for(j=maxdl-1;j>=0;--j) {
    akt=(akt+1)&1;
    res1=kolejnosci[akt]; res2=kolejnosci[(akt+1)&1];
    for(i=0;i<ALPHA+1;pom[i++]=0);
    for(i=0;i<n; ++i)
      if (dlugosci[i]>j)
        ++pom[WSK(slowa[poczatki[i]+j])];
      else ++pom[0];
    last=0;
    for(i=0;i<ALPHA+1; tmp=pom[i],pom[i++]=last,last+=tmp);
    for(i=0;i<n; ++i)
      if (dlugosci[res2[i]]>j)
        res1[pom[WSK(slowa[poczatki[res2[i]]+j])]++]=res2[i];
      else res1[pom[0]++]=res2[i];
  }
  kolejnosc=res1;
}

int czyPierwiastek(int k, int len)
{
  int i,j,dl=dlugosci[k];
  char *slowo = slowa + poczatki[k];
  for (i=len,j=0;i<dl && slowo[i] == slowo[j]; ++i, j=j+1<len?j+1:0) ;
  return i==dl && j==0;
}

/*
 * funckja obliczajaca pierwiastek pierwotny danego slowa
 * wylicza to w sposob naiwny sprawdzajac dla kazdego prefiksu
 * czy da sie nim pokryc slowo
 */
void pierwiastek(int k)
{
  int i, dl=dlugosci[k];
  if (dl < CALE) dl = CALE;
  for (i=1;i<dl && !czyPierwiastek(k,i) ; ++i) ;
  if (i<CALE) dlugosci[k] = i;
}

int rowne(int a, int b) {
  int i,dla = dlugosci[a], dlb=dlugosci[b];
  char *pa = slowa+poczatki[a], *pb=slowa+poczatki[b];
  if (dla!=dlb) return 0;
  for(i=0;i<dla;++i)
    if (*pa++!=*pb++) return 0;
  return 1;
}

int main() {
  int i,last=0;

  scanf("%d",&n);
  for(i=0; i<n; ++i) {
    poczatki[i]=last;
    scanf("%d ",dlugosci+i);
    scanf("%s",slowa+last);
    pierwiastek(i);
    last+=dlugosci[i];
  }
  posortuj();

  last=0;
  wynik=n;
  for(i=1; i<n ; ++i) 
    if (rowne(kolejnosc[i-1],kolejnosc[i])) wynik+= ++last<<1;
    else last=0;
  
  printf("%lld\n", wynik);
  return 0;
}
