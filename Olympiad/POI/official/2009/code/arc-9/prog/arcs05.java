/*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arcs0.cpp                                                  *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie nieefektywne czasowo.                          *}
{*            Szukajac najwiekszego leksykograficznie podciagu dlugosci  *}
{*            k sprawdza wszystkie podciagi dlugosci k - 1.              *}
{*            Zlozonosc obliczeniowa: O(n * k ^ 2)                       *}
{*   Ujavowienie: Marcin Pilipczuk                                       *}
{*                                                                       *}
{*************************************************************************/

import java.io.*;
import java.util.*;

public class arcs05 {
  final static int MAX_K = 1000000; // maksymalna dlugosc szukanego podciagu
  static int k, a;
  static int[] sub;
  static int[][] tmp;

  public static void main(String[] args){
    sub = new int[MAX_K];
    tmp = new int[MAX_K][2];
    k = jarclib.inicjuj();
    for(int i = 0; i < k; ++i)
      sub[i] = 0;
    while((a = jarclib.wczytaj()) != 0) {
      for(int i = 0; i < k; ++i)
        tmp[i][0] = sub[i];
      for(int i = 0; i < k; ++i) {
        for(int j = 0; j < i; ++j)
          tmp[j][1] = sub[j];
        for(int j = i + 1; j < k; ++j)
          tmp[j - 1][1] = sub[j];
        tmp[k - 1][1] = a;
        for(int j = 0; j < k; ++j) {
          if(tmp[j][0] < tmp[j][1]) {
            for(int l = 0; l < k; l++)
              tmp[l][0] = tmp[l][1];
            break;
          }
          if(tmp[j][0] > tmp[j][1])
            break;
        }
      }
      for(int i = 0; i < k; ++i)
        sub[i] = tmp[i][0];
    }
    for(int i = 0; i < k; ++i)
      jarclib.wypisz(sub[i]);
  }
};
