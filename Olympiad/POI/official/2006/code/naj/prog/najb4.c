/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: NAJ (Najazd)                                   *
 *   Plik:                najb4.c                                        *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie niepoprawne.                       *
 *                        Dodaje kolejne fabryki od najbardziej          *
 *                        zyskownych i patrzy czy wciaz jest wszystko    *
 *                        w 1 trojkacie                                  *
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

/* Tablica p --- majac dane fabryki na razie
   gdzie najdalej mozemy polozyc przekatna od i
   by je odgrodzic */
int p[MAXN],sp[MAXN];
/* Suma zyskow */
int suma;

int pom[MAXM];

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

/* Liczy ile */
int liczile(int a, int b, int c){
  int i, s = 0;
  for (i=0; i<m; ++i)
    if (sgndet(b,a,i) <= 0 && sgndet(c,b,i) <=0 && sgndet(a,c,i) <= 0)
      s += fw[i];
  return s;
}

int por(const void *a, const void *b){
  return fw[ *((int *)b) ] - fw [ *((int *)a) ];
}

int main(void){
  int i,a,k,j,f,b,c;
  int wynik = -2000*1000*1000;
  wczyt();
  for (i=0;i<m;++i)
    pom[i] = i;
  qsort(pom, m, sizeof(int), por);
  for (i=0;i<n;++i) p[i] = n-1;
  k = 0;
  while(k < m){
    a = pom[k];
    if (fw[a] <= 0)
      break;
    for (j=0; j<n; ++j)
      while (sgndet(j, (j+p[j])%n, a) > 0)
        p[j]--;
    f=1;
    for (j=0; j<n; ++j)
      if (p[j] + p[(j+p[j])%n] + p[(j+p[j]+p[(j+p[j])%n])%n] >= n){
        f = 0;
        break;
      }
    if (f) break;
    for (j=0; j<n; ++j)
      sp[j] = p[j];
    ++k;
  }
  for (j=0; j<n; ++j)
    if (sp[j] + sp[(j+sp[j])%n] + sp[(j+sp[j]+sp[(j+sp[j])%n])%n] >= n){
      a = j;
      b = j+sp[j];
      if (sp[j]==n-1)
        c = b--;
      else{
        b%=n;
        c = sp[j] + sp[b];
        if (c >= n) c = n-1;
        c += j;
        c %= n;
      }
      f = liczile(c, b, a);
      if (wynik < f)
        wynik = f;
    }
  printf("%d\n",wynik); 
  return 0;
}
