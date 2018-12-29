/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PAL (Palindromy)                               *
 *   Plik:                pals0.c                                        *
 *   Autor:               Adam Iwanicki                                  *
 *   Opis:                Rozwiazanie silowe - sprawdzajace dla kazdej   *
 *                        pary palindromow, czy ich konkatenacja jest    *
 *                        rowniez palindromem.                           *
 *                                                                       *
 *************************************************************************/

#include<stdio.h>
#define MAX 2000001

char slowa[MAX];
int poczatki[MAX],dlugosci[MAX], n;
long long int wynik=0;


int palindrom(int i, int j) {
  int res=1;
  int pom,k,li,lj;
  char *wi, *wj;
  if (dlugosci[i] < dlugosci[j]) {
    pom=i; i=j; j=pom;
  }
  wi = slowa + poczatki[i];
  wj = slowa + poczatki[j];
  li = dlugosci[i];
  lj = dlugosci[j];
  for(k=0 ; k < lj ; ++k) {
    if (*wi++ != *wj++) {
      res=0;
      break;
    }    
  }
  if (res) {
    wj=slowa+poczatki[i]+dlugosci[i]-1;
    while (wi < wj) {
      if (*wi++ != *wj--) {
        res=0;
        break;
      }
    }
  }
  return res;
}

int main() {
  int i,j,last=0;
  scanf("%d",&n);
  for(i=0; i<n; ++i) {
    poczatki[i]=last;
    scanf("%d ",dlugosci+i);
    scanf("%s",slowa+last);
    last+=dlugosci[i];
  }

  wynik=n;
  for(i=0; i<n ; ++i)
    for(j=0; j<i; ++j)
      if (palindrom(i,j)) 
        wynik+=2;

  printf("%lld\n", wynik);
  return 0;
}
