/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Lampki (LAM)                                              *
 *   Plik:     lams5.java                                                *
 *   Autor:    Adam Iwanicki                                             *
 *   Opis:     Rozwiazanie zbyt wolne, oblicza za kazdym razem NWD na    *
 *             duzych liczbach wbudowanych w Jave.                       *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.math.*;
import java.util.*;

public class lams5 implements Runnable {

  lams5() {
  }

  public static void main(String[] args) {
    new Thread(new lams5()).start();
  }

  public static final int MAX_N = 1000;

  public void run() {
    try {
      int[] num = new int[MAX_N];

      BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
      String line = br.readLine();
      int n = Integer.parseInt(line);

      for (int i = 0; i < n; ++i) {
        line = br.readLine();
        num[i] = Integer.parseInt(line);
      }

      ArrayList<String> out = new ArrayList<String>(n);
      out.add("1/" + num[n-1]);

      BigInteger licz = BigInteger.ONE;
      BigInteger mian = new BigInteger(String.valueOf(num[n-1]));

      for (int i = n-2 ; i >= 0; --i){
        BigInteger plicz = new BigInteger(String.valueOf(num[i+1]-1));
        BigInteger pmian = new BigInteger(String.valueOf(num[i]));

        if (0 == plicz.compareTo(BigInteger.ZERO))
          licz = BigInteger.ZERO;;

        if (1 == licz.compareTo(BigInteger.ZERO)) {
          BigInteger pnwd = plicz.gcd(pmian);
          plicz = plicz.divide(pnwd);
          pmian = pmian.divide(pnwd);

          BigInteger lg = licz.gcd(pmian);
          BigInteger lm = mian.gcd(plicz);
          pmian = pmian.divide(lg);
          plicz = plicz.divide(lm);
          
          mian = mian.divide(lm);
          licz = licz.divide(lg);
          mian = mian.multiply(pmian);
          licz = licz.multiply(plicz);
        } else 
          mian = BigInteger.ONE;

        out.add(licz.toString() + "/" + mian.toString());
      }
      Collections.reverse(out);
      for (String str : out) {
        System.out.println(str);
      }
    } catch (Exception e) {
      throw new RuntimeException(e);
    }
  }
}
