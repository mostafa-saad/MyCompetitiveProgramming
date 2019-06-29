/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kamyki (KAM)                                              *
 *   Plik:     kam2.java                                                 *
 *   Autor:    Szymon Wrzyszcz                                           *
 *   Opis:     Rozwiazanie wzorowe O(n)                                  *
 *                                                                       *
 *                                                                       *
 *************************************************************************/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class kam2 {
  
  private static BufferedReader bufReader;
  private static StringTokenizer tokenizer;
  
  // wczytuje jedna liczbe ze standardowego wejscia
  static int readInt() throws java.io.IOException {
    if (tokenizer.hasMoreTokens() == false)
      tokenizer = new StringTokenizer(bufReader.readLine()); 
    return Integer.parseInt(tokenizer.nextToken());
  }
  
  public static void main(String[] args) throws java.io.IOException {
    bufReader = new BufferedReader(new InputStreamReader(System.in));
    tokenizer = new StringTokenizer(bufReader.readLine());
    int u = readInt();
    for (int i=0; i<u; i++) {
      int n = readInt();
      int x = 0;
      
      int[] a = new int[n+1];
      for (int j=1; j<=n; j++)
        a[j] = readInt();
        
      int[] d = new int[n+1];  
      for (int j=1; j<n; j++)    // wyznaczanie ciagu d
        d[j] = a[n-j+1] - a[n-j];
      d[n] = a[1];
    
      for (int j=1; j<=n; j+=2)  // xor-uj elementy o nieparzystych indeksach
        x ^= d[j];
      
      System.out.println((x!=0)?"TAK":"NIE");
    }
  }
};
