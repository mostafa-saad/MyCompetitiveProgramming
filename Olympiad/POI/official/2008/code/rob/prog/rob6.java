/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Robinson (ROB)                                            *
 *   Plik:     rob6.java                                                 *
 *   Autor:    Adam Iwanicki, Jakub Radoszewski                          *
 *   Opis:     Rozwiazanie o zlozonosci czasowej O(n^2), ktore najpierw  *
 *             sprytnie znajduje wszystkie pola zabronione, a potem      *
 *             wykonuje jedno przeszukiwanie grafu wszerz.               *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class rob6 implements Runnable {
  public static final int MAX_N = 2000;
  
  private byte[][] lodz = new byte[MAX_N][MAX_N + 1];
  private int n;
  private List<Integer> odc = new ArrayList<Integer>(); /* odcinki skladajace sie na lodke */

  private int minx, miny, maxx, maxy, odcsize;
  private int sr; /* srodek lodki */
  private boolean[][] zabr = new boolean[3 * MAX_N][2 * MAX_N]; /* pola zabronione */

  /** Konstruktor klasy, inicjalizuje zmienne. */
  rob6() {
    pocz = new ArrayList(MAX_N);
    for (int i = 0; i < MAX_N; ++i) {
    	pocz.add(new ArrayList());
    }
  }

  public static void main(String[] args) {
    new Thread(new rob6()).start();
  }

  /* Sprawdzanie poprawnosci ulozenia lodki */
  boolean lodka() {
    minx = n; miny = n; maxx = -1; maxy=-1;
    odc.clear();
    odcsize = 0;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (lodz[i][j] == 'r')
        {
          minx = Math.min(minx, i);
          maxx = Math.max(maxx, i);
          miny = Math.min(miny, j);
          maxy = Math.max(maxy, j);
        }
    sr = (maxx + minx) / 2;
    for (int j = miny; j <= maxy; j++)
    {
      int i1 = 0, i2 = 0; /* ile kawalkow pod osia symetrii, a ile nad */
      for (int i = minx; i <= maxx; i++)
      {
        if (lodz[i][j] == 'r')
        {
          if (i < sr)
            i1++;
          if (i > sr)
            i2++;
        }
      }
      if (i1 != i2)
        /* Lodka nie jest symetryczna */
        return false;
      odc.add(i1);
      odcsize++;
    }
    return true;
  }

  public class PII {
    public int first;
    public int second;
    PII(int f, int s) {
      first = f;
      second = s;
    }
  }

  Queue<PII> kol = new LinkedList<PII>();
  int[][] odl = new int[3 * MAX_N][2 * MAX_N];

  int x[] = {1, -1, 0, 0};
  int y[] = {0, 0, 1, -1};

  List<List<Integer>> pocz;
  /* poczatki odpowiednikow lodzi, ktore wyznaczaja
   * pola zabronione */

  int[] pkt = new int[3 * MAX_N];

  void zabronione()
  {
    for (int i = 0; i < n; i++)
    {
      List<Integer> akt = pocz.get(i);
      for (int j = 0; j < n; j++)
        if (lodz[i][j] == 'X')
          akt.add(j + n - (maxy - miny));
      Collections.reverse(akt);
    }
    for (int j = 0; j < 2 * n; j++)
    {
      for (int ii = 0; ii < 3*n; ++ii) {
        pkt[ii] = 0;
      }
      for (int i = 0; i < n; i++)
      {
        List<Integer> akt = pocz.get(i);
        int dlug = akt.size() - 1;
        while (!akt.isEmpty() && akt.get(dlug) < j - (maxy - miny))
          akt.remove(dlug--);
        while (dlug >= 1 && akt.get(dlug) <= j && akt.get(dlug - 1) <= j
            && odc.get(j - akt.get(dlug - 1)) > odc.get(j - akt.get(dlug)))
          akt.remove(dlug--);
        if (!akt.isEmpty() && akt.get(dlug) <= j)
        {
          pkt[i + n - odc.get(j - akt.get(dlug))]++;
          pkt[i + n + odc.get(j - akt.get(dlug)) + 1]--;
        }
      }
      int licznik = 0;
      for (int i = 0; i < 3 * n; i++)
      {
        licznik += pkt[i];
        zabr[i][j] = (licznik > 0);
      }
    }
  }

  private PII[] przedzial = new PII[2 * MAX_N + 1];

  /* Funkcja zwraca przykladowy pusty przedzial (obustronnie domkniety). */
  PII pusty()
  {
    return new PII(1, 0);
  }

  /* Dla kazdego b liczy, w jakim przedziale musi sie znajdowac a,
   * zeby lodka o poczatku w polu (a,b) byla wewnatrz planszy. */
  void licz_przedzialy()
  {
    /* lodka przed plansza */
    int p = n - odcsize;
    for (int i = 0; i <= p; i++)
      przedzial[i] = pusty();
    
    /* lodka nad/pod plansza */
    int mx = odc.get(0);
    for (int i = 1; i < odcsize; i++)
      if (odc.get(i) > mx)
        mx = odc.get(i);
    for (int i = p + 1; i < 2 * n; i++)
      przedzial[i] = new PII(n - mx, 2 * n - 1 + mx);

    /* lodka dochodzi do planszy */
    int j = 0;
    while (j < odcsize - 1 && odc.get(j) <= odc.get(j + 1))
    {
      p++;
      przedzial[p] = new PII(n - odc.get(j), 2 * n - 1 + odc.get(j));
      j++;
    }

    /* lodka odchodzi od planszy */
    int k = 2 * n - 1;
    j = odcsize - 1;
    while (j > 0 && odc.get(j) <= odc.get(j - 1))
    {
      przedzial[k] = new PII(n - odc.get(j), 2 * n - 1 + odc.get(j));
      j--;
      k--;
    }

    /* lodka za plansza */
    przedzial[2 * n] = pusty();
  }

  boolean wyplynela(int a, int b)
  {
    return a < przedzial[b].first || a > przedzial[b].second;
  }

  /* BFS zaczynajacy od punktu (x0,y0). */
  int bfs(int x0, int y0)
  {
    for (int i = 0; i < 3 * n; i++)
      for (int j = 0; j < 2 * n; j++)
        odl[i][j] = -1;
    odl[x0][y0] = 0;
    kol.add(new PII(x0, y0));

    int a, b;
    while (!kol.isEmpty())
    {
      PII p = kol.poll();
      for (int i = 0; i < 4; i++)
      {
        a = p.first + x[i]; b = p.second + y[i];
        /* Wyszlismy poza plansze - sukces */
        if (wyplynela(a, b))
          return odl[p.first][p.second] + 1;
        if (odl[a][b] == -1 && !zabr[a][b])
        {
          odl[a][b] = odl[p.first][p.second] + 1;
          kol.add(new PII(a, b));
        }
      }
    }
    return -1;
  }


  public void run() {
    try {
      BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
      n = Integer.parseInt(br.readLine());
      for (int i = 0; i < n; i++) {
        lodz[i] = br.readLine().getBytes();
      }
      if (!lodka()) {  /* czy lodka zorienowana poziomo */
        /* Odbij wszystko wzgledem osi y=x */
        for (int i = 0; i < n; i++)
          for (int j = 0; j < i; j++) {
            byte tmp = lodz[j][i];
            lodz[j][i] = lodz[i][j];
            lodz[i][j] = tmp;
          }
        lodka(); /* no to lodka zorientowana pionowo */
      }
      Collections.reverse(odc);
      zabronione();
      licz_przedzialy();
      int wynik = bfs(n + sr, n + miny);
      if (wynik < 0)
        System.out.println("NIE");
      else
        System.out.println(wynik); 
    } catch (Exception e) {
      throw new RuntimeException(e);
    }
  }
}
