/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Blokada (BLO)                                             *
 *   Plik:     blo3.java                                                 *
 *   Autor:    Marek Cygan                                               *
 *   Opis:     Rozwiazanie wzorcowe zaimplementowane w Javie.            *
 *                                                                       *
 *************************************************************************/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class blo3 {

  public static int n; //liczba wierzcholkow
  public static ArrayList<Integer>[] krawedzie; //reprezentacja grafu poprzez listy sasiedztwa
  public static long[] blokada; //liczba zablokowanych spotkan dla kazdego wierzcholka
  public static boolean[] odwiedzony;
  public static int[] numer; //jako ktory dany wierzcholek zostal odwiedzony
  public static int[] low; //funkcja low dla kazdego wierzcholka
  public static int odwiedzone_wierzcholki;

  @SuppressWarnings("unchecked")
  public static void WczytajGraf() throws java.io.IOException{
    int m; //liczba krawedzi grafu
    BufferedReader bufReader = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer tokenizer = new StringTokenizer(bufReader.readLine());
    n = Integer.parseInt(tokenizer.nextToken());
    m = Integer.parseInt(tokenizer.nextToken());
    krawedzie = new ArrayList[n];
    for (int i = 0; i < n; ++i) krawedzie[i] = new ArrayList<Integer>();
    blokada = new long[n];
    odwiedzony = new boolean[n];
    numer = new int[n];
    low = new int[n];

    while (m-- > 0){
      int a,b;
      tokenizer = new StringTokenizer(bufReader.readLine());

      a = Integer.parseInt(tokenizer.nextToken());
      b = Integer.parseInt(tokenizer.nextToken());

      //dodanie nowej krawedzi nieskierowanej
      a--; b--;
      krawedzie[a].add(b);
      krawedzie[b].add(a);
    }
  }

  /* przeszukiwanie w glab
   * funkcja zwraca liczbe wierzcholkow z poddrzewa przeszukiwania*/
  public static int Dfs(int x, int ojciec){
    int liczba_odwiedzonych = 1;
    int liczba_zablokowanych = 0;
    odwiedzony[x] = true;
    numer[x] = low[x] = odwiedzone_wierzcholki++;
    blokada[x] = 2 * (n-1); //z wierzcholka x (i do wierzcholka x) nie da sie dojechac
    for(Integer it : krawedzie[x])
      if (!odwiedzony[it]){
        int rozmiar = Dfs(it, x);
        liczba_odwiedzonych += rozmiar;
        if (low[it] >= numer[x]){
          blokada[x] += (long)(n-1-rozmiar)*rozmiar;
          liczba_zablokowanych += rozmiar;
        } else{
          low[x] = Math.min(low[x], low[it]);
        }
      } else if (it != ojciec) low[x] = Math.min(low[x], numer[it]);
    blokada[x] += (long)(n-1-liczba_zablokowanych)*liczba_zablokowanych;
    return liczba_odwiedzonych;
  }

  public static void WypiszWynik(){
    for (int i = 0; i < n; ++i) System.out.println(blokada[i]);
  }

  public static void main(String[] args) throws java.io.IOException {
    new Thread(){
      public void run(){
        try{
          WczytajGraf();
          Dfs(0, -1);
          WypiszWynik();
        } catch (IOException e){
        }
      }
    }.start();
  }

}
