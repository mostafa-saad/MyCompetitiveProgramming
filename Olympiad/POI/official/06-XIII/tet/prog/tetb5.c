/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TET (Tetris 3D)                                *
 *   Plik:                tetb5.c                                        *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie blêdne.                            *
 *                        Zwraca maksimum wysokosci.                     *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

int main(void){
  int n,D,S,d,s,w,x,y,wynik;
  wynik = 0;
  scanf("%d%d%d",&D,&S,&n);
  while(n--){
    scanf("%d%d%d%d%d",&d,&s,&w,&x,&y);
    if (wynik < w) wynik = w;
  }
  printf("%d\n",wynik);
  return 0;
}

