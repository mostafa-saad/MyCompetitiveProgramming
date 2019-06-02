/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Klocki (KLO)                                              *
 *   Plik:     klo3.java                                                 *
 *   Autor:    Marek Cygan, Jakub Radoszewski                            *
 *   Opis:     Program o zlozonosci O(nlogn), zapisany z uzyciem         *
 *             TreeSet'a, aby rozroznic elementy o tej samej wartosci do *
 *             TreeSet'a dodajemy element (wartosc * n + pozycja) dzieki *
 *             czemu elementy o tych samych wartosciach beda             *
 *             rozroznialne.                                             *
 *                                                                       *
 *************************************************************************/
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.util.TreeSet;

public class klo3 {
  public static int n, k;
  public static int[] h;

  /* Obsluga wyszukiwania median */
  @SuppressWarnings("unchecked")
  public static TreeSet<Long> mniejsze = new TreeSet(), wieksze = new TreeSet();
  public static long suma_mniejsze, suma_wieksze;
  public static long mediana;

  public static void rownowaz()
  {
    int s1 = mniejsze.size(), s2 = wieksze.size();
    if (s2 > s1)
    {
      /* wieksze -> mniejsze */
      long elt_pom = wieksze.first();
      wieksze.remove(elt_pom);
      long elt = elt_pom / n;
      suma_wieksze -= elt;
      mniejsze.add(elt_pom);
      suma_mniejsze += elt;
      mediana = elt;
    }
    else if (s1 > s2 + 1)
    {
      /* mniejsze -> wieksze */
      long elt_pom = mniejsze.last();
      long elt = elt_pom / n;
      mniejsze.remove(elt_pom);
      mediana = mniejsze.last() / n;
      mniejsze.remove(elt_pom);
      suma_mniejsze -= elt;
      wieksze.add(elt_pom);
      suma_wieksze += elt;
    }
    else if (s1 > 0)
    {
      /* po prostu pobieramy mediane */
      mediana = mniejsze.last() / n;
    }
  }

  public static void wstaw(int wys, int pozycja)
  {
    if (wys <= mediana)
    {
      mniejsze.add((long)wys * n + pozycja);
      suma_mniejsze += wys;
    } else
    {
      wieksze.add((long)wys * n + pozycja);
      suma_wieksze += wys;
    }
    rownowaz();
  }

  public static void usun(int wys, int pozycja)
  {
    if (wys <= mediana)
    {
      suma_mniejsze -= wys;
      mniejsze.remove((long) wys * n + pozycja);
    } else
    {
      suma_wieksze -= wys;
      wieksze.remove((long) wys * n + pozycja);
    }
    rownowaz();
  }

  public static long minimum, min_mediana;
  public static int min_i;

  public static void main(String[] args) throws java.io.IOException{
    /* Odczyt */
    BufferedReader bufReader = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer tokenizer = new StringTokenizer(bufReader.readLine());
    n = Integer.parseInt(tokenizer.nextToken());
    k = Integer.parseInt(tokenizer.nextToken());
    h = new int[n];

    for (int i = 0; i < n; i++){
      tokenizer = new StringTokenizer(bufReader.readLine());
      h[i] = Integer.parseInt(tokenizer.nextToken());
    }

    /* Poczatek */
    mediana = -1;
    for (int i = 0; i < k - 1; i++)
      wstaw(h[i], i);

    /* Obliczanie wyniku */
    minimum = (long)1000 * 1000 * 1000 * 1000;
    for (int i = k - 1; i < n; i++)
    {
      wstaw(h[i], i);
      long akt = (long)mediana * mniejsze.size() - suma_mniejsze +
      suma_wieksze - (long)mediana * wieksze.size();
      if (akt < minimum)
      {
        minimum = akt;
        min_i = i - k + 1;
        min_mediana = mediana;
      }
      usun(h[i - k + 1], i - k + 1);
    }

    /* Wypisywanie wyniku */
    System.out.println(minimum);
    for (int i = 0; i < min_i; i++)
      System.out.println(h[i]);
    for (int i = min_i; i < min_i + k; i++)
      System.out.println(min_mediana);
    for (int i = min_i + k; i < n; i++)
      System.out.println(h[i]);

  }

}
