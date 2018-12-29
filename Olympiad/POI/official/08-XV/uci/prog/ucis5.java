/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Ucieczka (UCI)                                            *
 *   Plik:     ucis5.java                                                *
 *   Autor:    Wojciech Tyczynski                                        *
 *   Opis:     Rozwiazanie nieoptymalne, zapisane w Javie.               *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class ucis5 implements Runnable
{
  public static void main(String[] args){
    new Thread(new ucis5()).start();
  }
  
  int n, m, x, y, mod;
  boolean police[][];
  int step[][] = { {-1,0}, {0,1}, {1,0}, {0,-1} };

  private void init()
  {
    police = new boolean[100][100];
  }

  private int compute(int a, int b, int dir)
  {
    if (a+1 == y && b+1 == x)
      return 1;
    int ret = 0;
    police[a][b] = true;
    for (int cnt = 0; cnt < 2; cnt++ )
    {
      int aa = a + step[dir][0];
      int bb = b + step[dir][1];
      if (0 <= aa && aa < n && 0 <= bb && bb < m && !police[aa][bb])
        ret = (ret + compute(aa,bb,dir)) % mod;
      dir = (dir+1) % 4;
    }
    police[a][b] = false;
    return ret;
  }

  public void run()
  {
    try
    {
      init();
      BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
      String linia = br.readLine();
      StringTokenizer st = new StringTokenizer(linia);
      n = Integer.parseInt(st.nextToken());
      m = Integer.parseInt(st.nextToken());
      mod = Integer.parseInt(st.nextToken());
      linia = br.readLine();
      st = new StringTokenizer(linia);
      x = Integer.parseInt(st.nextToken());
      y = Integer.parseInt(st.nextToken());
      for (int a = 0; a < n; a++ )
      {
        linia = br.readLine();
        for (int b = 0; b < m; b++ )
          police[a][b] = linia.charAt(b) == '*';
      }
      System.out.println(compute(n-1,0,0));
    }
    catch (Exception e)
    {
      throw new RuntimeException(e);
    }

  }
}

