/*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arcb2.cpp                                                  *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie nieefektywne czasowo i pamieciowo.             *}
{*            Zlozonosc obliczeniowa: O(n * k)                           *}
{*            Zlozonosc pamiecowa: O(n + k)                              *}
{*            Realizuje pomysl rozwiazania alternatywnego i wybiera      *}
{*            maksimum z przedzialu w czasie liniowym wzgledem jego      *}
{*            dlugosci.                                                  *} 
{*   Ujavowienie: Marcin Pilipczuk                                       *}
{*                                                                       *}
{*************************************************************************/

import java.io.*;
import java.util.*;

public class arcb25{
  final static int MAX_N = 8000000;
  static int n, k, is, il, max_num;
  static int[] seq;

  public static void main(String[] args){
    seq = new int[MAX_N + 1];
    k = jarclib.inicjuj();
    n = 0;
    while((n < MAX_N) && ((seq[n++] = jarclib.wczytaj()) != 0));
    seq[n] = 0;
    n--;
    is = 0;
    for(int i = 0; i < k; ++i) {
        max_num = 0;
        for(int j = is; j < n - k + i + 1; ++j)
            if(seq[j] > max_num) {
                il = j;
                max_num = seq[j];
            }
        is = il + 1;
        jarclib.wypisz(max_num);
    }
  }
};

