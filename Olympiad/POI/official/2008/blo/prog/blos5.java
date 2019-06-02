/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Blokada (BLO)                                             *
 *   Plik:     blos5.java                                                *
 *   Autor:    Marek Cygan, Marian Marek Kedzierski                      *
 *   Opis:     Rozwiazanie nieoptymalne; implementacja w Javie.          *
 *                                                                       *
 *************************************************************************/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class blos5 {

  public static int n; //liczba wierzcholkow
  public static ArrayList<Integer>[] krawedzie; //reprezentacja grafu poprzez listy sasiedztwa
  public static long[] blokada; //liczba zablokowanych spotkan dla kazdego wierzcholka
  public static boolean[] odwiedzony;
  public static int odwiedzone;
  public static int blocked; // nr zablokowanego wierzcholka

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
  public static int Dfs(int x){
    if (x == blocked) return 0;
    odwiedzony[x] = true;
    int my_size = 1;

    for(Integer it : krawedzie[x])
      if (!odwiedzony[it])
        my_size += Dfs(it);

    return my_size;
  }

  public static void WypiszWynik(){
    for (int i = 0; i < n; ++i) System.out.println(blokada[i]);
  }

  public static void main(String[] args) throws java.io.IOException {
    new Thread(){
      public void run(){
        try{
          int size;
          WczytajGraf();
          for (int v=0; v<n; ++v) {
            blokada[v] = 2 * (n - 1);

            for (int i=0; i<n; ++i) odwiedzony[i] = false;
            blocked = v;
            for (int i=0; i<n; ++i)
              if (blocked != i && !odwiedzony[i]) {
                size = Dfs(i);
                blokada[v] += size * (n - 1 - size);
              }
          }
          WypiszWynik();
        } catch (IOException e){
        }
      }
    }.start();
  }

}
