/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Robinson (ROB)                                            *
 *   Plik:     rob7.java                                                 *
 *   Autor:    Adam Iwanicki, Jakub Radoszewski                          *
 *   Opis:     Rozwiazanie o zlozonosci czasowej O(n^2), zgodne z idea   *
 *             rozwiazania autorskiego.                                  *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class rob7 implements Runnable {
  public static final int MAX_N = 2000;

  byte[][] lodz = new byte[MAX_N][MAX_N + 1];
  int n;
  ArrayList<Integer> odc = new ArrayList<Integer>(); /* odcinki skladajace sie na lodke */

  int minx, miny, maxx, maxy, odcsize;
  int sr; /* srodek lodki */
  int polsz;

  /** Konstruktor klasy, inicjalizuje zmienne. */
  rob7() {
  }

  public static void main(String[] args) {
    new Thread(new rob7()).start();
  }

  /* Sprawdzanie poprawnosci ulozenia lodki */
  boolean lodka()
  {
    minx = n; miny = n; maxx = -1; maxy=-1;
    odcsize = 0;
    odc.clear();
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
    polsz = (maxx - minx) / 2;
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

  ArrayList<Integer> polowka = new ArrayList<Integer>();

  int[] przekroj = new int[MAX_N]; /* dla danego promienia trzymamy numer
                                      najwiekszego mieszczacego sie przekroju */

  void policz_przekroj(int rozm)
  {
    /* Liczymy tablice przekroj */
    int i = 0;
    for (int j = 0; j < n; j++)
    {
      i = Math.max(i, 0);
      while (i < rozm && polowka.get(i) <= j)
        i++;
      i--;
      przekroj[j] = i;
    }
  }


  int[][] pole = new int[3 * MAX_N][MAX_N]; /* jaki najwiekszy numer przekroju polowki
                                               miesci sie w danym polu */
  int[] gora = new int[3 * MAX_N];
  int[] dol = new int[3 * MAX_N];

  void policz_przekroje_pol(int rozm)
  {
    /* Liczymy tablice pole */
    for (int j = 0; j < n; j++)
    {
      gora[0] = n;
      for (int i = 1; i < 3 * n; i++)
        if (i >= n && i < 2 * n && lodz[i - n][j] == 'X')
          gora[i] = 0;
        else
          gora[i] = Math.min(gora[i - 1] + 1, n);

      dol[3 * n - 1] = n;
      for (int i = 3 * n - 2; i >= 0; i--)
        if (i >= n && i < 2 * n && lodz[i - n][j] == 'X')
          dol[i] = 0;
        else
          dol[i] = Math.min(dol[i + 1] + 1, n);

      for (int i = 0; i < 3 * n; i++)
      {
        int wlk = Math.min(gora[i], dol[i]) - 1;
        if (wlk < 0)
          pole[i][j] = -1;
        else
          pole[i][j] = przekroj[wlk];
      }
    }
  }


  boolean[][] zabr = new boolean[3 * MAX_N][3 * MAX_N]; /* pola zabronione */

  void policz_polowke(int przesuniecie, boolean na_odwrot)
  {
    int rozm = polowka.size();
    policz_przekroj(rozm);
    policz_przekroje_pol(rozm);

    /* Glowny algorytm szukania pol zabronionych */
    for (int i = 0; i < 3 * n; i++)
    {
      int numer = rozm - 1; /* numer poprzedniego najlepszego przekroju */
      int przekr; /* numer najlepszego biezacego przekroju */
      for (int j = n; j < 3 * n; j++)
      {
        if (j < 2 * n)
          przekr = pole[i][j - n];
        else
          /* jestesmy poza plansza - a tam tylko woda */
          przekr = rozm - 1;
        if (numer == rozm - 1)
          numer--;
        /* Obliczamy najlepszy biezacy numer */
        numer = Math.min(numer + 1, przekr);

        if (numer != rozm - 1)
        {
          /* Mamy pole zabronione */
          if (na_odwrot)
            zabr[i][3 * n - 1 - j - przesuniecie] = true;
          else
            zabr[i][j - przesuniecie] = true;
        }
      }
    }
  }


  void zabronione()
  {
    /* Lewa polowka */
    int i = 0;
    polowka.add(odc.get(i));
    while (odc.get(i) < polsz)
    {
      i++;
      polowka.add(odc.get(i));
    }
    int wlk0 = polowka.size() - 1;
    policz_polowke(wlk0, false);

    /* Prawa polowka */
    polowka.clear();
    do
    {
      polowka.add(odc.get(i));
      i++;
    } while (i < (int)odc.size());

    /* Odwracamy polowke i lodz */
    Collections.reverse(polowka);
    for (i = 0; i < n; i++) {
      for (int l = 0, r = n-1; l < r; ++l, --r) {
        byte tmp = lodz[i][l];
        lodz[i][l] = lodz[i][r];
        lodz[i][r] = tmp;
      }
    }
    policz_polowke(wlk0, true);
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
      zabronione();
      for (int i = 0; i < odcsize / 2; i++)
      {
        int pom = odc.get(i);
        odc.set(i, odc.get(odcsize - i - 1));
        odc.set(odcsize - i - 1, pom);
      }
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
};
