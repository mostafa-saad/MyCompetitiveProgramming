/*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arczaw3.java                                               *}
{*   Opis:    Rozwiazanie NIEPOPRAWNE obrazujace sposob uzycia           *}
{*            biblioteki. Wczytuje caly ciag a jako rozwiazanie zwraca   *}
{*            pierwsze k elementow.                                      *}
{*                                                                       *}
{*************************************************************************/

public class arczaw3{
  public static void main(String args[]){
    int[] p = new int[1000000];
    int k = jarclib.inicjuj();
    int ip = 0;
    while(true){
      int a = jarclib.wczytaj();
      if (a == 0)
        break;
      if (ip < 1000000)
        p[ip++] = a;
    }
    for (int i = 0; i < k; ++i)
      jarclib.wypisz(p[i]);
  }
};
