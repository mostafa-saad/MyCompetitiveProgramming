/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Tablice (TAB)                                             *
 *   Plik:     tab3.java                                                 *
 *   Autor:    Blazej Osinski                                            *
 *   Opis:     Rozwiazanie wzorcowe O(n*m).                              *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class tab3 implements Runnable {
  public static final int N = 1000, INF = 2000000007, M = 1000000;
  
  private int t, n, m, i, j;
  private int[][][] tab = new int[2][N][N];
  private int[] tmp = new int[2*M+1];

  /* Konstruktor klasy, inicjalizuje zmienne. */
  tab3() {
    for (int i = 0; i <= 2*M; ++i) {
      tmp[i] = 0;
    }
  }

  public static void main(String[] args) {
    new Thread(new tab3()).start();
  }

  public class PII implements Comparable{
    public int first;
    public int second;
    PII(int f, int s) {
      first = f;
      second = s;
    }
    public int compareTo(Object o){
      PII a = (PII)o;
      if(first != a.first)
        return first - a.first;
      return second - a.second; 
    }
  }
  /* tablice zawierają najmniejsze liczby z wierszy tablic a i b oraz numery odpowiadających wierszy*/
  private PII[][] tr = new PII[2][N];

  public void run() {
    try {
      BufferedReader bufReader = new BufferedReader(new InputStreamReader(System.in));
      t = Integer.parseInt(bufReader.readLine());
      StringTokenizer tokenizer;
      for(int tnr=1; tnr <= t; tnr++){
        tokenizer = new StringTokenizer(bufReader.readLine());
        n = Integer.parseInt(tokenizer.nextToken());
        m = Integer.parseInt(tokenizer.nextToken());
        for(int nr=0; nr<2; nr++){
          for(i=0; i<n; i++){
            tokenizer = new StringTokenizer(bufReader.readLine());
            int mel = INF;
            for(j=0; j<m; j++){ 
              tab[nr][i][j] = Integer.parseInt(tokenizer.nextToken()) + M;
              mel = (mel>tab[nr][i][j]) ? tab[nr][i][j] : mel;
            }
            tr[nr][i] = new PII(mel, i);
          }
          Arrays.sort(tr[nr],0,n);
        }
        boolean pod = true;
        for(i=0; i<n; i++)
          if(tr[0][i].first != tr[1][i].first)
            pod = false;
        if(!pod){
          System.out.println("NIE");
          continue;
        }
        /* generowanie permutacji elementów w wierszu */
        int nra = tr[0][0].second, nrb = tr[1][0].second;
        int[] perm = new int[N];
        for(i=0; i<m; i++)
          tmp[tab[1][nrb][i]] = tnr*N+i;
        for(i=0; i<m; i++){
          int a = tmp[tab[0][nra][i]];
          if(a<tnr*N){
            pod=false;
            break;
          }
          a %= N;
          perm[i] = a;
        }
        if(!pod){
          System.out.println("NIE");
          continue;
        }
        /* sprawdzenie czy permutacje zgadzają się dla wszystkich wierszy */
        for(i=1; i<n && pod; i++){
          nra = tr[0][i].second;
          nrb = tr[1][i].second;
          for(j=0;j<m;j++)
            if(tab[0][nra][j] != tab[1][nrb][perm[j]]){
              pod = false;
              break;
            }
        }
        if(!pod)
          System.out.println("NIE");
        else
          System.out.println("TAK");
      }
    } catch (Exception e) {
      throw new RuntimeException(e);
    }
  }
}
