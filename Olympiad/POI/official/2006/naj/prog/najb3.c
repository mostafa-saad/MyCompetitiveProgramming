/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: NAJ (Najazd)                                   *
 *   Plik:                najb3.c                                        *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie niepoprawne.                       *
 *                        Dopoki takowy istnieje, to usuwa skrajny       *
 *                        trojkat o najmniejszym zysku.                  *
 *                        Zlozonosc O(nm log n).                         *
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

/* Lista wierzcholkow, ktore zostaly */
int nast[MAXN];
int popr[MAXN];

/* Ile ma trojkat o srodku w tym miejscu */
int ile[MAXN];

/* Liczy ile */
int liczile(int b){
  int i, a = nast[b], c = popr[b], s = 0;
  for (i=0; i<m; ++i)
    if (sgndet(b,a,i) <= 0 && sgndet(c,b,i) <=0 && sgndet(a,c,i) < 0)
      s += fw[i];
  return s;
}

/* Kopiec trojkatow */
int kopiec[MAXN+1];
int gdzie[MAXN];
int kopcnt;
inline void zamien(int a,int b){
  int e;
  e = kopiec[a];
  kopiec[a] = kopiec[b];
  kopiec[b] = e;
  gdzie[kopiec[a]] = a;
  gdzie[kopiec[b]] = b;
}
void upheap(int a){
  while (a > 1){
    if (ile[kopiec[a>>1]] <= ile[kopiec[a]])
      break;
    zamien(a,a>>1);
    a>>=1;
  }
}
void downheap(int a){
  int b;
  while ((a<<1) <= kopcnt){
    b = (a<<1);
    if (b < kopcnt && ile[kopiec[b]] > ile[kopiec[b+1]])
      ++b;
    if (ile[kopiec[a]] <= ile[kopiec[b]])
      break;
    zamien(a,b);
    a = b;
  }
}

int main(void){
  int i, nn, x;
  wczyt();
  /* Inicjalizujemy liste i kopiec */
  for (i=0; i<n; ++i){
    nast[i] = (i+1)%n;
    popr[i] = (i-1+n)%n;
    kopiec[i+1] = i;
    gdzie[i] = i+1;
  }
  kopcnt = n;
  for (i=0; i<n; ++i)
    ile[i] = liczile(i);
  for (i=1; i<=n; ++i)
    upheap(i);
  /* No i lecimy, poki pozostaly >3 wierzcholki */
  for (nn = n; nn>3; --nn){
    x = kopiec[1];
    zamien(kopcnt, 1);
    kopcnt--;
    downheap(1);
    suma -= ile[x];
    nast[popr[x]] = nast[x];
    popr[nast[x]] = popr[x];
    ile[popr[x]] = liczile(popr[x]);
    upheap(gdzie[popr[x]]);
    downheap(gdzie[popr[x]]);
    ile[nast[x]] = liczile(nast[x]);
    upheap(gdzie[nast[x]]);
    downheap(gdzie[nast[x]]);
  }
  printf("%d\n", suma);
  return 0;
}
