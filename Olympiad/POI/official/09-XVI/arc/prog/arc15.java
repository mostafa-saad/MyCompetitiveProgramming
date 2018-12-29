/*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arc1.cpp                                                   *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie wzorcowe.                                      *}
{*            Zlozonosc obliczeniowa: O(n + k)                           *}
{*            Rozwiazanie wykorzystuje STLa.                             *}
{*   Ujavowienie: Marcin Pilipczuk                                       *}
{*                                                                       *}
{*************************************************************************/

import java.io.*;
import java.util.*;

public class arc15 {
  // Javowe iteratory maja ta wade, ze wypierniczaja
  // sie w czasie modyfikacji listy :(
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
    int a, k = jarclib.inicjuj();
    sub = new Lista();
    sub.x = -1;
    sub.next = sub.prev = sub;
    for(int i = 0; i < k; ++i)
      addTail(0);
    cen = sub.prev;
    while((a = jarclib.wczytaj()) != 0)
    {
        addTail(a);
        nex = cen;
        nex = nex.next;
        while(nex != sub) {
            if(cen.x < nex.x)
                break;
            cen = cen.next;
            nex = nex.next;
        }
        if (cen != sub.next){
          nex = cen.prev;
        }
        cen.prev.next = cen.next;
        cen.next.prev = cen.prev;
        cen = nex;
    }
    for (cen = sub.next; cen != sub; cen = cen.next)
      jarclib.wypisz(cen.x);
  }
};
