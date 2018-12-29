/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: TET (Tetris 3D)                                *
 *   Plik:                tetb4.c                                        *
 *   Autor:               Marcin Pilipczuk                               *
 *   Opis:                Rozwiazanie blêdne.                            *
 *                        Sumuje wysokosci wszystkich prostokatow.       *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

int main(void){
  int n,D,S,d,s,w,x,y,wynik;
  wynik = 0;
  scanf("%d%d%d",&D,&S,&n);
  while(n--){
    scanf("%d%d%d%d%d",&d,&s,&w,&x,&y);
    wynik += w;
  }
  printf("%d\n",wynik);
  return 0;
}

