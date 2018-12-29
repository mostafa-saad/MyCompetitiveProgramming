/*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arcb6.cpp                                                  *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie nieefektywne czasowo i pamieciowo.             *}
{*            Zlozonosc obliczeniowa: O(n + k)                           *}
{*            Zlozonosc pamiecowa: O(n + k)                              *}
{*            Realizuje pomysl rozwiazania alternatywnego ale wczytuje   *}
{*            caly ciag do pamieci.                                      *} 
{*   Ujavowienie: Marcin Pilipczuk                                       *}
{*                                                                       *}
{*************************************************************************/


import java.io.*;
import java.util.*;

public class arcb65 {
  final static int MAX_K = 1000000;
  final static int MAX_N = 7000000;
  static int n, k, is;
  static int[] seq, sub;

  public static void main(String[] args){
    seq = new int[MAX_N+1];
    sub = new int[MAX_K];
    k = jarclib.inicjuj();
    n = 0;
    while((n < MAX_N) && ((seq[n++] = jarclib.wczytaj()) != 0));
    seq[n] = 0;
    n--;
    is = 0;
    for(int i = 0; i < n; ++i) {
      while(is > 0 && (is + n - i) > k && sub[is - 1] < seq[i])
        is--;
      if(is < k)
        sub[is++] = seq[i];
    }
    for(int i = 0; i < k; ++i)
      jarclib.wypisz(sub[i]);
  }
};
