/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Ucieczka (UCI)                                            *
 *   Plik:     ucib4.java                                                *
 *   Autor:    Wojciech Tyczynski                                        *
 *   Opis:     Rozwiazanie niepoprawne, zapisane w Javie.                *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class ucib4 implements Runnable
{
  public static void main(String[] args){
    new Thread(new ucib4()).start();
  }

  int n, m, x, y, mod;
  boolean police[][];

  int step[][] = { {-1,0}, {0,1}, {1,0}, {0,-1} };
  int memoize[][][][][];

  private void init()
  {
    memoize = new int[4][40][40][40][40];
    police = new boolean[40][40];
  }

  private int compute(int dir, int l0, int l1, int l2, int l3)
  {
    if (memoize[dir][l0][l1][l2][l3] > 0)
      return memoize[dir][l0][l1][l2][l3]-1;
    int cura = y-1 + step[(dir+3)%4][0] * l0;
    int curb = x-1 + step[(dir+3)%4][1] * l0;
    int mva = step[dir][0];
    int mvb = step[dir][1];
    boolean clear = true;
    for (int a = 0; a < l3; a++ )
    {
      cura -= mva;
      curb -= mvb;
      clear &= !police[cura][curb];
    }
    if (!clear)
    {
      memoize[dir][l0][l1][l2][l3] = 1;
      return 0;
    }
    if (l0 == 0)
    {
      memoize[dir][l0][l1][l2][l3] = 2;
      return 1;
    }
    cura = y-1 + step[(dir+3)%4][0] * l0;
    curb = x-1 + step[(dir+3)%4][1] * l0;
    int ret = 0;
    for (int a = 0; a <= l1 && (clear &= !police[cura][curb]); a++ )
    {
      ret = (ret + compute((dir+1)%4, a, l2, l3, l0-1)) % mod;
      cura += mva;
      curb += mvb;
    }
    memoize[dir][l0][l1][l2][l3] = ret+1;
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
      System.out.println(compute(0, x-1, y-1, m-x, n-y));
    }
    catch (Exception e)
    {
      throw new RuntimeException(e);
    }

  }
}

