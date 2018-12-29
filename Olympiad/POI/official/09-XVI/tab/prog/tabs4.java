/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Tablice (TAB)                                             *
 *   Plik:     tabs4.java                                                *
 *   Autor:    Blazej Osinski                                            *
 *   Opis:     Rozwiazanie wolne O(n!*m!*n*m). Sprawdza wszystkie        *
 *             permutacje wierszy i kolumn.                              *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class tabs4 implements Runnable {
  public static final int N = 1000, INF = 2000000007, M = 1000000;
  
  private int t, n, m, i, j;
  private int[][][] tab = new int[2][N][N];
  private int[] tmp = new int[2*M+1];
  private int[] perw = new int[N];
  private int[] perk = new int[N];

  /* Konstruktor klasy, inicjalizuje zmienne. */
  tabs4() {
    for (int i = 0; i <= 2*M; ++i) {
      tmp[i] = 0;
    }
  }

  public static void main(String[] args) {
    new Thread(new tabs4()).start();
  }

  private static boolean next_permutation(int t[], int n){
    int i, j, tmp;
    boolean res = true;
    for(i=n-1; i>0; i--)
      if(t[i]>t[i-1])
        break;
 
    if(i==0)
      res = false;
    else {
      for(j=i; j<n; j++)
        if(t[i-1]>=t[j])
          break;
      tmp = t[i-1];
      t[i-1] = t[j-1];
      t[j-1] = tmp;
    }
    for(j=n-1;i<j;i++,j--){
      tmp = t[i];
      t[i] = t[j];
      t[j] = tmp;
    }
    return res;
  }
  public void run() {
    try {
      BufferedReader bufReader = new BufferedReader(new InputStreamReader(System.in));
      t = Integer.parseInt(bufReader.readLine());
      StringTokenizer tokenizer;
      for(int tnr=1; tnr <= t; tnr++){
        tokenizer = new StringTokenizer(bufReader.readLine());
        n = Integer.parseInt(tokenizer.nextToken());
        m = Integer.parseInt(tokenizer.nextToken());
        boolean odp = true;
        for(int nr=0; nr<2; nr++){
          for(i=0; i<n; i++){
            tokenizer = new StringTokenizer(bufReader.readLine());
            for(j=0; j<m; j++){ 
              tab[nr][i][j] = Integer.parseInt(tokenizer.nextToken()) + M;
              if(nr==0)
                tmp[tab[nr][i][j]] = tnr;
              else
                if(tmp[tab[nr][i][j]] != tnr)
                  odp=false;

            }
          }
        }
        if(!odp){
          System.out.println("NIE");
          continue;
        }
        for(i=0; i<n; i++)
          perw[i]=i;
        for(j=0; j<m; j++)
          perk[j]=j;
        odp=false;
        do{
          do{
            boolean f = true;
            for(i=0;i<n && f;i++)
              for(j=0;j<m;j++)
                if(tab[0][i][j] != tab[1][perw[i]][perk[j]]){
                  f = false;
                  break;
                }
            odp |= f;
          }while(!odp && next_permutation(perk,m));          
        }while(!odp && next_permutation(perw,n));
        if(!odp)
          System.out.println("NIE");
        else
          System.out.println("TAK");
      }
    } catch (Exception e) {
      throw new RuntimeException(e);
    }
  }
}
