/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kamyki (KAM)                                              *
 *   Plik:     kams4.java                                                *
 *   Autor:    Szymon Wrzyszcz                                           *
 *   Opis:     Rozwiazanie wykladnicze bez psamietywania                 *
 *                                                                       *
 *                                                                       *
 *************************************************************************/ 

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class kams4 {
  
  private static BufferedReader bufReader;
  private static StringTokenizer tokenizer;
  
  // wczytuje jedna liczbe ze standardowego wejscia
  static int readInt() throws java.io.IOException {
    if (tokenizer.hasMoreTokens() == false)
      tokenizer = new StringTokenizer(bufReader.readLine()); 
    return Integer.parseInt(tokenizer.nextToken());
  }
    
  // sprawcza czy zostaly jeszcze jakies kamienie
  static boolean koniec(int[] v) {
    for (int i=0; i<v.length; i++)
      if (v[i] > 0)
	return false;
    return true;
  }

  // zwraca 1 gdy dany stan jest wygrywajacy, 0 wpp
  static boolean wygra(int[] v) {
    if (koniec(v))
      return false;
    for (int i=0; i<v.length; i++) {
      int k = (i==0)?(v[0]):(v[i]-v[i-1]);
      while (k >= 1) {
	v[i] -= k;
	if (!wygra(v)) {
	  v[i] += k;
	  return true;
        }
        v[i] += k;
        k--;
      }
    }
    return false;
  }
    
  public static void main(String[] args) throws java.io.IOException {
    bufReader = new BufferedReader(new InputStreamReader(System.in));
    tokenizer = new StringTokenizer(bufReader.readLine());
    int u = readInt();
    for (int i=0; i<u; i++) {
      int n = readInt();
      int[] a = new int[n];
      for (int j=0; j<n; j++)
	a[j] = readInt();
	    
      System.out.println(wygra(a)?"TAK":"NIE");
    }
  }
};
