/*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arc3.cpp                                                   *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie alternatywne.                                  *}
{*            Zlozonosc obliczeniowa: O(n + k)                           *}
{*   Ujavowienie: Marcin Pilipczuk                                       *}
{*                                                                       *}
{*************************************************************************/

import java.io.*;
import java.util.*;

public class arc35 {
  final static int MAX_K = 1000000; // maksymalna dlugosc szukanego podciagu

  static int[] buf; // kolejka reprezentujaca bufor
  static int a, k;
  static int ib, ie; // wskazniki na pierwszy i ostatni element w kolejce
  static int cou; // ilosc elementow znajdujacych sie w kolejce
  static int[] sub; // stos reprezentujacy szukany podciag
  static int is; // wskaznik na szczyt stosu
  static boolean is_end; // czy zakonczylismy juz wczytywanie ciagu

  /* Uzupelnia bufor tak aby znajdowalo sie w nim [k] elementow jesli to mozliwe
   * (jesli wczytywany ciag jeszcze sie nie skonczyl) */
  static void fill_buffer() {
    if(is_end || cou == k)
      return;
    int a;
    while(cou < k) {
      a = jarclib.wczytaj();
      if(a == 0) {
        is_end = true;
        return;
      }
      buf[ie++] = a;
      cou++;
      if(ie == MAX_K)
        ie = 0;
    }
  }

  public static void main(String[] args){
    k = jarclib.inicjuj();
    buf = new int[MAX_K];
    sub = new int[MAX_K];
    ib = ie = cou = 0;
    is = 0;
    is_end = false;
    fill_buffer();
    while(cou > 0) {
        a = buf[ib++];
        cou--;
        if(ib == MAX_K)
            ib = 0;
        while((is + cou + 1) > k && sub[is-1] < a)
            is--;
        if(is < k)
            sub[is++] = a;
        fill_buffer();
    }
    for(int i = 0; i < k; ++i)
        jarclib.wypisz(sub[i]);
  }
};
