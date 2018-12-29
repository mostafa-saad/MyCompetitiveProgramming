/*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arcb0.cpp                                                  *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie nieefektywne czasowo i pamieciowo.             *}
{*            Zlozonosc obliczeniowa: O((n po k) * n * k)                *}
{*            Zlozonosc pamiecowa: O(n + k)                              *}
{*            Sprawdza wszystkie k elementowe podzbiory.                 *}
{*   Ujavowienie: Marcin Pilipczuk                                       *}
{*                                                                       *}
{*************************************************************************/

import java.io.*;
import java.util.*;

public class arcb05{
  final static int MAX_N = 1000000;
  final static int MAX_K = 1000000;
  static int n, k;
  static int[] seq, sub, tmp;

  static void check(int is, int ele) {
    if((n - is) < ele)
      return;
    if(ele == 0) {
      for(int i = 0; i < k; ++i) {
        if(sub[i] < tmp[i]) {
          for(int j = 0; j < k; ++j)
            sub[j] = tmp[j];
          break;
        }
        if(sub[i] > tmp[i])
          break;
      }
      return;
    }
    tmp[k - ele] = seq[is];
    check(is + 1, ele - 1);
    check(is + 1, ele);
  }

  public static void main(String[] args){
    seq = new int[MAX_N + 1];
    sub = new int[MAX_K];
    tmp = new int[MAX_K];
    k = jarclib.inicjuj();
    n = 0;
    while((n < MAX_N) && ((seq[n++] = jarclib.wczytaj()) != 0));
    seq[n] = 0;
    n--;
    for(int i = 0; i < k; ++i)
      sub[i] = 0;
    check(0, k);
    for(int i = 0; i < k; ++i)
      jarclib.wypisz(sub[i]);
  }
};
