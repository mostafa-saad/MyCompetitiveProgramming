/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: NAJ (Najazd)                                   *
 *   Plik:                naj2.c                                         *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie wzorcowe O(nm log n + n^3)         *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAXN 600
#define MAXM 10000
/* Wielokat */
int wx[MAXN],wy[MAXN];
/* Fabryki */
int fx[MAXM],fy[MAXM],fw[MAXM];

int n,m;

/* Tablica t --- ile jest w otwartej polowce 
   od a do b (a+1,...,b-1) */
int t[MAXN][MAXN];
/* Suma zyskow */
int suma;

/* Wczytanie danych */
void wczyt(void){
  int i;
  scanf("%d",&n);
  for (i=0; i<n; ++i)
    scanf("%d%d",&(wx[i]),&(wy[i]));
  scanf("%d",&m);
  for (i=0; i<m; ++i){
    scanf("%d%d%d",&(fx[i]),&(fy[i]),&(fw[i]));
    suma += fw[i];
  }
}

/* Znak iloczynu skalarnego wierzcholka a, wierzcholka b oraz punktu p */
inline int sgndet(int a,int b,int p){
  return (wx[b]-wx[a]) * (fy[p]-wy[a]) - (wy[b]-wy[a]) * (fx[p]-wx[a]);
}
inline int sgndet2(int a,int p1,int p2){
  return (fx[p1]-wx[a]) * (fy[p2]-wy[a]) - (fy[p1]-wy[a]) * (fx[p2]-wx[a]);
}

/* Wierzcholki do posortowania */
int pom[MAXM];
int pomcnt;
int aktstart;
int porownaj(const void *a,const void *b){
  int c = *((int *)a);
  int d = *((int *)b);
  return sgndet2(aktstart,c,d);
}

/* Faza liczenia tablicy t */
void licz_t(void){
  int i,j,a;
  for (i=0; i<n; ++i){
    pomcnt=0;
    aktstart=i;
    for (j=0; j<m; ++j)
      if (sgndet(i,(i-1+n)%n,j) != 0)
        pom[pomcnt++]=j;
    qsort(pom,pomcnt,sizeof(int),porownaj);
    a=2;
    for (j=0; j<pomcnt; ++j){
      while (sgndet(i,(i+a)%n,pom[j]) <= 0) ++a;
      t[i][(i+a)%n] += fw[pom[j]];
    }
    for (j=1; j<n-1; ++j)
      t[i][(i+j+1)%n] += t[i][(i+j)%n];
  }
}

/* Faza liczenia wyniku */
void licz_wynik(void){
  int wynik = -2000*1000*1000;
  int a,b,c,x;
  for (a=0; a<n; ++a)
    for (b=0; b<a; ++b)
      for (c=0; c<b; ++c){
        x = suma - t[b][a] - t[c][b] - t[a][c];
        if (x > wynik)
          wynik = x;
      }
  printf("%d\n",wynik);
}

int main(void){
  wczyt();
  licz_t();
  licz_wynik();
  return 0;
}
