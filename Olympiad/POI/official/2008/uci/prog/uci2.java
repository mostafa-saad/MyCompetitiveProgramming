/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Ucieczka (UCI)                                            *
 *   Plik:     uci2.java                                                 *
 *   Autor:    Filip Wolski                                              *
 *   Opis:     Rozwiazanie wzorcowe, zapisane w Javie.                   *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class uci2 implements Runnable
{
  public static void main(String[] args){
    new Thread(new uci2()).start();
  }

  int n, m, x, y, mod;
  boolean police[][];

  int step[][] = { {-1,0}, {0,1}, {1,0}, {0,-1} };
  int res[][][][][];
  boolean clear[][][][];

  int dir, l0, l1, l2, l3, sz;

  private void init()
  {
    res = new int[4][2][100][100][100];
    clear = new boolean[4][100][100][100];
    police = new boolean[100][100];
  }

  private int compute()
  {
    int cura = y-1 + step[(dir+3)%4][0] * l0;
    int curb = x-1 + step[(dir+3)%4][1] * l0;
    int mva = step[dir][0];
    int mvb = step[dir][1];
    clear[dir][l0][l1][l3] = (!police[cura + mva * l1][curb + mvb * l1]) && (!police[cura - mva * l3][curb - mvb * l3]);
    if (l1 > 0)
      clear[dir][l0][l1][l3] &= clear[dir][l0][l1-1][l3];
    if (l3 > 0)
      clear[dir][l0][l1][l3] &= clear[dir][l0][l1][l3-1];
    if (!clear[dir][l0][0][l3])
      return 0;
    if (l0 == 0)
      return 1;
    int ret = 0;
    if (l1 > 0)
      ret += res[dir][(sz-1)%2][l0][l1-1][l2];
    if (clear[dir][l0][l1][l3])
      ret += res[(dir+1)%4][(sz-1)%2][l1][l2][l3];
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
      for (sz = 2; sz <= n+m; sz++ )
        for (int szn = Math.max(1,sz-m); szn <= n && szn < sz; szn++ )
          for (int a = 0; a + szn <= n; a++ )
            for (int b = 0; b + sz-szn <= m; b++ )
            {
              l0 = x-1 - b;
              l1 = y-1 - a;
              l2 = b+sz-szn - x;
              l3 = a+szn - y;
              if (l0 < 0 || l1 < 0 || l2 < 0 || l3 < 0)
                continue;
              for (dir = 0; dir < 4; dir++ )
              {
                res[dir][sz%2][l0][l1][l2] = compute() % mod;
                int tmp = l0; l0 = l1; l1 = l2; l2 = l3; l3 = tmp;
              }
            }
      System.out.println(res[0][(n+m)%2][x-1][y-1][m-x]);
    }
    catch (Exception e)
    {
      throw new RuntimeException(e);
    }

  }
}

