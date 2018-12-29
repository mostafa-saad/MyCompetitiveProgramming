/*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arcs3.cpp                                                  *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie nieefektywne czasowo.                          *}
{*            Wyszukuje w czasie liniowym pierwsza niemotonicznosc.      *}
{*            Zlozonosc obliczeniowa: O(n * k)                           *}
{*   Ujavowienie: Marcin Pilipczuk                                       *}
{*                                                                       *}
{*************************************************************************/

import java.io.*;
import java.util.*;

public class arcs35 {
  static int k, a;

  public static class Lista {
    public int x;
    public Lista prev, next;
  };

  private static Lista sub, cen, nex;

  private static void addTail(int x){
    Lista l = new Lista();
    l.x = x;
    l.prev = sub.prev;
    l.next = sub;
    l.prev.next = l.next.prev = l;
  }

  public static void main(String[] args){
    k = jarclib.inicjuj();
    sub = new Lista();
    sub.next = sub.prev = sub;
    for(int i = 0; i < k; ++i)
      addTail(0);
    while((a = jarclib.wczytaj()) != 0) {
      addTail(a);
      nex = cen = sub.next;
      nex = nex.next;
      while(nex != sub) {
        if(cen.x < nex.x)
          break;
        cen = cen.next;
        nex = nex.next;;
      }
      cen.prev.next = cen.next;
      cen.next.prev = cen.prev;
      cen = null;
    }
    for (nex = sub.next; nex != sub; nex = nex.next)
      jarclib.wypisz(nex.x);
  }
};
