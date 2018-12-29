/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Permutacja (PER)                                          *
 *   Plik:     per4.java                                                 *
 *   Autor:    Jakub Radoszewski, Marcin Pilipczuk                       *
 *   Opis:     Rozwiazanie autorskie.                                    *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class per4 implements Runnable{
    public static void main(String[] args){
        new Thread(new per4()).start();
    }

    final static int MAX_N = 300000;

    static int n, m;
    static int[] t;
    static int mx; /* = *max_element(t, t + n) + 1 */
    static ArrayList<Integer> p; /* liczby pierwsze z rozkladu m na czynniki */
    static int l; /* dlugosc tegoz */

    void rozklad()
    {
        int i = 2, m1 = m;
        while ((long)i * (long)i <= (long)m)
        {
            if (m1 % i == 0)
            {
                while (m1 % i == 0)
                    m1 /= i;
              p.add(i);
            }
            i++;
        }
        if (m1 > 1)
            p.add(m1);
        l = p.size();
    }

    /* Rozszerzony algorytm Euklidesa.
     * Dla a i b podaje (p,q,d) takie, ze ap+bq=d. */
    static int euclid(int a, int b, long[] r)
    {
      if (b == 0)
        {
            r[0] = 1; r[1] = 0;
            return a;
        } else
      {
        long[] r1 = new long[2]; int d1;
        d1 = euclid(b, a % b, r1);
        r[0] = r1[1];
            r[1] = r1[0] - r1[1] * (a / b);
            return d1;
      }
    }

    /* Odwrotnosc v modulo m (musi byc NWD(v,m)=1). */
    static int odwrotnosc(int v)
    {
        long[] r = new long[2];
        euclid(v, m, r);
        return (int)(r[0] % m + m) % m;
    }

    /* Szybkie potegowanie modulo: (x ^ u) modulo m. */
    static int potmod(int x, int u)
    {
      int a = 1, b = x;
      while (u > 0)
        if (u % 2 == 1)
            {
                a = (int)(((long)a * b) % m);
                u--;
            }
        else
            {
                b = (int)(((long)b * b) % m);
                u /= 2;
            }
      return (int)a;
    }

    /* Drzewo przedzialowe wraz z jego rozmiarem */
    int[] drz;
    int ile;

    void ustaw(int x, int delta){
        int v = x + ile;
        drz[v] += delta;
        while (v != 1)
        {
            v /= 2;
            drz[v] = drz[2 * v] + drz[2 * v + 1];
        }
    }

    int zapytanie(int x)
    {
        if (x <= 0)
            return 0;
        int v = x + ile, wyn = 0;
        while (v != 1)
        {
            if (v % 2 == 1)
                wyn += drz[v - 1];
            v /= 2;
        }
        return wyn;
    }

    /* Reprezentacja wyniku */
    public static class liczba {
        public int[] tab; /* wykladniki liczb pierwszych sposrod p[i],
                                   dzielacych liczbe (moga byc ujemne!) */
        public int val; /* reszta modulo m (z czynnikow wzglednie pierwszych z m) */

        public liczba(){
            val = 1;
            tab = new int[l];
            for (int i = 0; i < l; ++i)
                tab[i] = 0;
        }

        public liczba(liczba c){
            val = c.val;
            tab = new int[c.tab.length];
            for (int i = 0; i < c.tab.length; ++i)
                tab[i] = c.tab[i];
        }

        public void pomnozPrzez(int x)
        {
            if (x == 0)
            {
                val = 0;
                return;
            }
            for (int i = 0; i < l; i++)
                while (x % p.get(i) == 0)
                {
                    x /= p.get(i);
                    tab[i]++;
                }
            val = (int)(((long)(val) * x) % m);
        }

        public void podzielPrzez(int x)
        {
            if (x <= 1)
                return;
            for (int i = 0; i < l; i++)
            while (x % p.get(i) == 0)
            {
                x /= p.get(i);
                tab[i]--;
            }
            val = (int)(((long)(val) * odwrotnosc(x)) % m);
        }

        public int wartosc()
        {
            int wyn = val;
            for (int i = 0; i < l; i++)
                wyn = (int)(((long)(wyn) * potmod(p.get(i), tab[i])) % m);
            return wyn;
        }
    }

    /* Glowna funkcja, ktora... liczy wynik */
    void doit()
    {
        int wynik = 1;
        liczba akt = new liczba(), pom;
        for (int i = 2; i <= n - 1; i++)
            akt.pomnozPrzez(i);
        for (int i = 0; i < mx; i++)
            for (int j = 2; j <= drz[i + ile]; j++)
                akt.podzielPrzez(j);
        for (int i = 0; i < n - 1; i++)
        {
            pom = new liczba(akt);
            pom.pomnozPrzez(zapytanie(t[i]));
            wynik = (wynik + pom.wartosc()) % m;
            akt.pomnozPrzez(drz[t[i] + ile]);
            akt.podzielPrzez(n - i - 1);
            ustaw(t[i], -1);
        }
        System.out.println(wynik);
    }

    public void run(){
        try{
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            String linia = br.readLine();
            StringTokenizer st = new StringTokenizer(linia);
            n = Integer.parseInt(st.nextToken());
            m = Integer.parseInt(st.nextToken());
            linia = br.readLine();
            st = new StringTokenizer(linia);
            t = new int[n];
            for (int i = 0; i < n; ++i)
                t[i] = Integer.parseInt(st.nextToken());
            p = new ArrayList<Integer>();
            drz = new int[1100 * 1000];
            rozklad();

            /* Konstrukcja drzewa przedzialowego */
            mx = t[0];
            for (int i = 0; i < n; ++i) if (mx < t[i]) mx = t[i];
            mx++;
            ile = 1;
            while (ile < mx)
                ile *= 2;
            for (int i = 0; i < n; i++)
                ustaw(t[i], 1);

            doit();
        }catch(Exception e){
            throw new RuntimeException(e);
        }
    }
};

