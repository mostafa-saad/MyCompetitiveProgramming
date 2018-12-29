/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: NAJ (Najazd)                                   *
 *   Plik:                najs2.c                                        *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie nieoptymalne, ale sprytniejsze.    *
 *                        Zlozonosc O(n^2(n+m)).                         *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

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

/* Faza liczenia tablicy t 
   Dla kazdej przekatnej liczymy te na lewo i te na prawo */
void licz_t(void){
  int a,b,i,x;
  for (a=0; a<n; ++a)
    for (b=0; b<a; ++b)
      for(i=0; i<m; ++i){
        x = sgndet(b,a,i);
        if (x > 0) 
          t[b][a] += fw[i];
        else if (x < 0)
          t[a][b] += fw[i]; 
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
