/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Tablice (TAB)                                             *
 *   Plik:     tabs7.java                                                *
 *   Autor:    Blazej Osinski                                            *
 *   Opis:     Rozwiazanie wolne O(min(n,m)*n*m). Sprowadza do postaci   *
 *             kanonicznej.                                              *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class tabs7 implements Runnable {
  public static final int N = 1000, INF = 2000000007, M = 1000000;
  
  private int t, n, m, i, j;
  private int[][][] tab = new int[2][N][N];

  public static void main(String[] args) {
    new Thread(new tabs7()).start();
  }
  public void ustalPostac(int[][] t){
    int i, j;
    int kon, tmp;
    if(n<m)
      kon = n;
    else
      kon = m;
    for(int l=0;l<kon;l++){
      int mw = INF,w=l,k=l;
      for(i=l;i<n;i++)
        for(j=l;j<m;j++)
          if(t[i][j]<mw){
            w = i;
            k = j;
            mw = t[i][j];
          }
      /*zamiana odpowiednich wierszy i kolumn*/
      if(w!=l)
        for(j=0;j<m;j++){
          tmp = t[w][j];
          t[w][j] = t[l][j];
          t[l][j] = tmp;
        }
      if(k!=l)
        for(i=0;i<n;i++){
          tmp = t[i][k];
          t[i][k] = t[i][l];
          t[i][l] = tmp;
        }
    }
    /* sortowanie leksykograficzne nadmiarowych wierszy lub kolumn*/
    if(kon<n){
      int w;
      for(int l=kon;l<n;l++){
        w=l;
        for(i=l+1;i<n;i++)
          if(t[i][0]<t[w][0])
            w=i; 
        if(w!=l)
          for(j=0;j<m;j++){
            tmp = t[w][j];
            t[w][j] = t[l][j];
            t[l][j] = tmp;
          }
      }
    }
    if(kon<m){
      int k;
      for(int l=kon;l<m;l++){
        k=l;
        for(j=l+1;j<m;j++)
          if(t[0][j]<t[0][k])
            k=j;
        if(k!=l)
          for(i=0;i<n;i++){
            tmp = t[i][k];
            t[i][k] = t[i][l];
            t[i][l] = tmp;
          }
      }
    }
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
        for(int nr=0; nr<2; nr++){
          for(i=0; i<n; i++){
            tokenizer = new StringTokenizer(bufReader.readLine());
            for(j=0; j<m; j++) 
              tab[nr][i][j] = Integer.parseInt(tokenizer.nextToken());            
          }
          ustalPostac(tab[nr]);
        }
        boolean odp = true;
        for(i=0;i<n && odp;i++)
          for(j=0;j<m;j++)
            if(tab[0][i][j] != tab[1][i][j]){
              odp = false;
              break;
            }
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
