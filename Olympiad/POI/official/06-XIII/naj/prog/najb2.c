/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: NAJ (Najazd)                                   *
 *   Plik:                najb2.c                                        *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie niepoprawne.                       *
 *                        Silniczek Wankla: losuje cos, a potem kreci    *
 *                        poki jest lepiej                               *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAXN 600
#define MAXM 10000
#define ILESPR 15000

/* Wielokat */
int wx[MAXN],wy[MAXN];
/* Fabryki */
int fx[MAXM],fy[MAXM],fw[MAXM];

int n,m;

/* Wczytanie danych */
void wczyt(void){
  int i;
  scanf("%d",&n);
  for (i=0; i<n; ++i)
    scanf("%d%d",&(wx[i]),&(wy[i]));
  scanf("%d",&m);
  for (i=0; i<m; ++i)
    scanf("%d%d%d",&(fx[i]),&(fy[i]),&(fw[i]));
}

/* Znak iloczynu skalarnego wierzcholka a, wierzcholka b oraz punktu p */
inline int sgndet(int a,int b,int p){
  return (wx[b]-wx[a]) * (fy[p]-wy[a]) - (wy[b]-wy[a]) * (fx[p]-wx[a]);
}
inline int sgndet2(int a,int p1,int p2){
  return (fx[p1]-wx[a]) * (fy[p2]-wy[a]) - (fy[p1]-wy[a]) * (fx[p2]-wx[a]);
}

/* Liczy pole, zaklada skierowanie a,b,c */
inline int pole(int a,int b,int c){
  int s = 0, i;
  for (i=0; i<m; ++i)
    if (sgndet(b,a,i) <= 0 && sgndet(c,b,i) <=0 && sgndet(a,c,i) <= 0)
      s += fw[i];
  return s;
}

int main(void){
  int wynik = -2000 * 1000 * 1000;
  int a,b,c,k,s,e,akts,zm,dx;
  wczyt();
  srand(n+m+343);
  k = 0;
  while (k < ILESPR){
    /* losujemy startowy */
    a = rand() % n;
    b = (a + 1 + rand() % (n-1))%n;
    do{
      c = rand()%n;
    } while (a==c || b==c);
    if (a < b){ e = a; a = b; b = e; }
    if (c > a){ e = a; a = c; c = e; }
    if (c > b){ e = b; b = c; c = e; }
    akts = pole(a, b, c);
    if (wynik < akts)
      wynik = akts;
    zm = 3;
    while (k < ILESPR && zm > 0){
      while ((c+1)%n != b){
        s = pole (a,b,(c+1)%n);
        if (s <= akts)
          break;
        zm = 3; /* Czy byla zmiana ? */
        c = (c+1)%n;
        akts = s;
        if (wynik < akts)
          wynik = akts;
        ++k;
      }
      e = a;
      a = b;
      b = c;
      c = e;
      ++k;
      --zm;
    }
  }
  printf("%d\n",wynik);
  return 0;
}

