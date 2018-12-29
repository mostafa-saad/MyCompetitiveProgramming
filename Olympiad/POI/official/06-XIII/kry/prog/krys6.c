/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: KRY (Kryszta³)                                 *
 *   Plik:                krys6.c                                        *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Hybryda niepelnego rozwiazania wzorcowego oraz *
 *                        rozwiazania dynamicznego.                      *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long ull;

ull m[50];
int n;

/* Dynamik jest prosty */
ull dynt1[1 << 21], dynt2[1 << 21];
ull *dynz, *dyndo;

ull dynamik(void){
  int ile = 0, i, j, k, ile2;
  ull wynik = (ull)0;
  ull *tmp;
  dynz = dynt1;
  dyndo = dynt2;
  dynz[0] = (ull)1;
  for (i=0; i<n-1; ++i){
    ile2 = ile;
    for (k=0; k<=ile; ++k){
      for (j=0; j<=m[i]; ++j){
        dyndo[k ^ j] += dynz[k];
        if ((k ^ j) > ile2)
          ile2 = (k ^ j);
      }
      dynz[k] = 0;
    }
    ile = ile2;
    tmp = dynz; 
    dynz = dyndo;
    dyndo = tmp;
  }
  for (i=0; i<=m[n-1] && i<=ile; ++i)
    wynik += dynz[i];
  return wynik - (ull)1;
}

/* Niepelne wzorcowe troche skomplikowansze:
   potega - taka potega, ze 2^potega > m[n-1] */
int potega;

/* Funkcja rekurencyjnie wybierajaca podzbior */
ull licz_wzorc(int s, int poz, int ilejuz){
  int i=0; 
  ull ret = (ull)1;
  if (poz <= s){
    if (ilejuz&1) /* Wzielismy nieparzyscie wiele */
      return (ull)0;
    if (ilejuz == n-1-s) /* Wszystkie wzielismy - to policzymy osobno */
      return (ull)0;
    else{ /* Nie wszystkie wzielismy, czyli iloczyn reszty */
      for (i=0; i<=s; ++i)
        ret *= m[i] + (ull)1;
      return ret;
    }
  }

  ret = (ull)0;
  /* Wpierw nie bierzemy */
  if (ilejuz == n - 1 - poz)
    /* Znaczy sie, jeszcze nie wzielismy tego dopelniajacego */
    ret += licz_wzorc(s, poz-1, ilejuz);
  else
    /* Wzielismy, czyli my dowolnie wiele */
    ret += licz_wzorc(s, poz-1, ilejuz) * ((ull)1 << (ull)potega);

  /* Teraz bierzemy jedynke */
  ret += licz_wzorc(s, poz-1, ilejuz+1) * (m[poz] + (ull)1 - ((ull)1 << (ull)potega));
  return ret;
}

int por(const void *a, const void *b){
  ull c = *((ull *)a), d = *((ull *)b);
  if (c < d) return -1;
  if (c > d) return 1;
  return 0;
}

/* Glowna funkcja do niepelnego wzorcowego */
ull niepelne_wzorcowe(void){
  int s, i;
  ull ret = (ull)0;
  
  if (potega == 0)
    return (ull)1;

  --potega;
  /* Szukamy, gdzie sie koncza duze liczby */
  for (s=n-1; s>=0 && m[s] >= ((ull)1 << (ull)potega); --s) ;
  
  /* Liczymy te poza wszystkimi jedynkami */
  ret += licz_wzorc(s, n-1, 0);
  /* I te z jedynkami - tylko jesli jest ich parzyscie wiele*/
  if (!((n-s-1)&1)){
    for (i=s+1; i<n; ++i)
      m[i] ^= ((ull)1 << (ull)potega);
    qsort(m, n, sizeof(ull), por);
    ret += niepelne_wzorcowe();
  }
  return ret;
}


int main(void){
  int i;
  ull tmp;
  scanf("%d", &n);
  for (i=0; i<n; ++i)
    scanf("%llu", &(m[i]));
  
  qsort(m, n, sizeof(ull), por);
  
  tmp = m[n-1];
  while (tmp > (ull)0){
    tmp >>= (ull)1;
    ++potega;
  }
 
  tmp = (ull)1;
  if (n > 3)
    tmp = (m[n-2]+(ull)1) * (m[n-3]+(ull)1);
  if (potega > 17 || tmp > ((ull)11 << (ull)24)){
    printf("%llu\n", niepelne_wzorcowe() - (ull)1);
  }
  else{
    printf("%llu\n", dynamik());
  } 
  return 0;
}
