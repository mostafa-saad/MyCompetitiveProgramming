/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kamyki (KAM)                                              *
 *   Plik:     kams5.java                                                *
 *   Autor:    Szymon Wrzyszcz                                           *
 *   Opis:     Rozwiazanie wykladnicze uzywajace programowania           *
 *             dynamicznego                                              *
 *                                                                       *
 *                                                                       *
 *************************************************************************/
 
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.util.HashMap;

public class kams5 {
  
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

  static HashMap M;
    
  static String serializuj(int[] v) {
    String s = "";
    for (int i=0; i<v.length; i++)
      s += v[i] + " ";
    return s;
  }

  // zwraca true gdy dany stan jest wygrywajacy, false wpp
  static boolean wygra(int[] v) {
    if (koniec(v))
      return false;
    String s = serializuj(v);
    if (M.containsKey(s))
      return M.get(s).equals(true);
    for (int i=0; i<v.length; i++) {
      int k = (i==0)?(v[0]):(v[i]-v[i-1]);
      while (k >= 1) {
	v[i] -= k;
	if (wygra(v) == false) {
	  v[i] += k;
	  M.put(serializuj(v), true);
	  return true;
	}
	v[i] += k;
	k--;
      }
    }
    M.put(serializuj(v), false);
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
	    
      M = new HashMap();
      System.out.println(wygra(a)?"TAK":"NIE");
    }
  }
};
