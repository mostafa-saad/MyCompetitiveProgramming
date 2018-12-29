/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Squarki                                          *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n^3 log n)                                     *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#define MAXN 300
#define LEAF 65536
#define MAXV 100000001

int pary[MAXN*MAXN]; //masy par kwarkow
int a[MAXN]; //masy pojedynczych kwarkow
int wynik[MAXN][MAXN]; //tablica wynikow
int ilewynik; //ilosc wynikow

int n, ilepar; //ilosc kwarkow i par

int oczekiwane_wartosc[LEAF*2]; //drzewo oczekiwanych mas
int oczekiwane_ilosc[LEAF*2]; //drzewo oczekiwanych mas

int max(int a, int b){
  if(a > b)return a;
  return b;
}

int min(int a, int b){
  if(a > b)return b;
  return a;
}

void inicjalizuj(){
  int i;
  for(i = 0; i < ilepar; ++i){
    oczekiwane_wartosc[LEAF + i] = pary[i];
    oczekiwane_ilosc[LEAF + i] = 0;
  }
  for(i = ilepar; i < LEAF; ++i){
    oczekiwane_wartosc[LEAF + i] = MAXV;
    oczekiwane_ilosc[LEAF + i] = -2;
  }
  for(i = LEAF - 1; i > 0; --i){
    oczekiwane_wartosc[i] = max(oczekiwane_wartosc[i * 2], oczekiwane_wartosc[i * 2 + 1]);
    oczekiwane_ilosc[i] = 0;
  }
}

int znajdz(int klucz){
  int ind = 1;
  while(ind < LEAF){
    ind *= 2;
    if(oczekiwane_wartosc[ind] < klucz)++ind;
  }
  if(oczekiwane_wartosc[ind] != klucz)return -1;
  return ind;
}

void zwieksz(int klucz){
  int ind = znajdz(klucz);
  if(ind > 0)++oczekiwane_ilosc[ind];
}

void zmniejsz(int klucz){
  int ind = znajdz(klucz);
  if(ind > 0)--oczekiwane_ilosc[ind];
}

int ile(int klucz){
  int ind = znajdz(klucz);
  if(ind > 0)return oczekiwane_ilosc[ind];
  return ind;
}

int pomoc[MAXN * MAXN];

void polacz(int start, int srod, int stop){
  int i = start, j = srod + 1;
  int akt = i;
  while(i <= srod || j <= stop){
    if(i <= srod && j <= stop){
      if(pary[i] < pary[j]){
        pomoc[akt] = pary[i];
        ++i;
      }
      else{
        pomoc[akt] = pary[j];
        ++j;
      }
    }
    else if(i <= srod){
      pomoc[akt] = pary[i];
      ++i;
    }
    else{
      pomoc[akt] = pary[j];
      ++j;
    }
    ++akt;
  }
  for(i = start; i <= stop; ++i)pary[i] = pomoc[i];
}

void sortuj(int start, int stop){ //sortowanie przez scalanie
  int ile = stop - start + 1;
  if(ile >= 2){
    int srod = (start + stop) / 2;
    sortuj(start, srod);
    sortuj(srod + 1, stop);
    polacz(start, srod, stop);
  }
}
  
int main(){
  int ret;
  ret = scanf("%d", &n); //wczytujemy dane
  ilepar = (n * (n - 1)) / 2;
  int i, j, l;
  for(i = 0; i < ilepar; ++i){
    ret = scanf("%d", &pary[i]); //wczytywanie par
  }
  if (ret < 0) return 0;
  sortuj(0, ilepar - 1);
  for(i = 2; i < n; ++i){ //iteracja po mozliwych masach a2+a3
    a[0] = pary[0] + pary[1] - pary[i]; //obliczanie a1
    if(a[0] % 2 || a[0] < 0)continue; //niecalkowita masa
    if(i > 2 && pary[i] == pary[i - 1])continue;
    a[0] /= 2;
    a[1] = pary[0] - a[0]; //a2
    a[2] = pary[1] - a[0]; //i a3
    //inicjalizacja oczekiwanych dodawanie do nich a1+a2, a1+a3 i a2+a3
    inicjalizuj();
    zwieksz(a[0] + a[1]);
    zwieksz(a[0] + a[2]);
    zwieksz(a[1] + a[2]);
    int znalezione = 3;
    int ok = 1;
    for(j = 0; j < ilepar; ++j){ //przegladanie par
      if(ile(pary[j]) > 0)zmniejsz(pary[j]); //oczekiwana
      else{ //nieoczekiwana, czyli masa nowego kwarka
        if(znalezione >= n){ //za duzo kwarkow
          j = ilepar;
          ok = 0;
        }
        else{ //dodanie nowego kwarka
          a[znalezione] = pary[j] - a[0];
          for(l = 1; l < znalezione; ++l)zwieksz(a[l] + a[znalezione]);
          ++znalezione;
        }
      }
    }
    if(znalezione == n && ok){ //jesli poszlo ok
            for(j = 1; j < n; ++j){
                if(a[j] == a[j - 1])ok = 0;
            }
      if(ok){
                for(j = 0; j < n; ++j){ //dodajemy wynik do tablicy wynikow
            wynik[ilewynik][j] = a[j];
          }
          ++ilewynik;
            }
    }
  }
  printf("%d\n", ilewynik); //wypisanie wyniku
  for(i = 0; i < ilewynik; ++i){
    for(j = 0; j < n; ++j){
      printf("%d ", wynik[i][j]);
    }
    printf("\n");
  }
  return 0;
}
