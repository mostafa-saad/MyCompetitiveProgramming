/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kamyki (KAM)                                              *
 *   Plik:     kamb3.java                                                *
 *   Autor:    Szymon Wrzyszcz                                           *
 *   Opis:     Rozwiazanie niepoprawne. Zaklada, ze r_n=r_{n-2}=...=0    *
 *             jest warunkiem dostatecznym, zeby uklad byl przegrywajacy.*
 *                                                                       *
 *                                                                       *
 *************************************************************************/
 
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class kamb3 {
  
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
      int[] a;
      
      if (n % 2 == 0) {
        a = new int[n];
        for (int j=0; j<n; j++)
          a[j] = readInt();
      } else {
        a = new int[n+1];
        a[0] = 0;
        for (int j=1; j<=n; j++)
          a[j] = readInt();
        n++;
      }
      
      boolean wygra = false;
      for (int j=0; j<n; j+=2) {
        if (a[j] != a[j+1])
          wygra = true;
      }
        
      System.out.println(wygra?"TAK":"NIE");
    }
  }
};
