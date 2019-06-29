/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Plakatowanie (PLA)                                        *
 *   Plik:     pla10.java                                                *
 *   Autor:    Marcin Pilipczuk, Jakub Radoszewski                       *
 *   Opis:     Rozwiazanie autorskie - Find & Union.                     *
 *                                                                       *
 *************************************************************************/
import java.io.*;
import java.util.*;

public class pla10 implements Runnable{
    public static void main(String[] args){
        new Thread(new pla10()).start();
    }

    public static class Cosik implements Comparable<Cosik>{
        int first;
        int second;

        public int compareTo(Cosik t){
            if (t.first != first)
                return t.first - first;
            return t.second - second;
        }
    }

    /* Struktura danych dla zbiorow rozlacznych.
     * Zlozonosc: O(n log*n) */
    static final int MAX_N = 250000 + 1; /* n+1 */
    int[] p, rank;
    int n;
    Cosik[] w;

    public pla10(){
        p = new int[MAX_N];
        rank = new int[MAX_N];
    }

    void makeset(int x){
        p[x] = x;
        rank[x] = 0;
    }

    int findset(int x){
        if (x != p[x])
            p[x] = findset(p[x]);
        return p[x];
    }

    void link(int x, int y){
        if (rank[x] > rank[y])
            p[y] = x;
        else{
            p[x] = y;
            if (rank[x] == rank[y])
              rank[y]++;
        }
    }

    void unia(int x, int y){
        link(findset(x), findset(y));
    }

    /* Wlasciwe rozwiazanie */
    public void run(){
        try{
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            String linia = br.readLine();
            StringTokenizer st = new StringTokenizer(linia);
            n = Integer.parseInt(st.nextToken());
            w = new Cosik[n];
            for (int i = 0; i < n; ++i){
                linia = br.readLine();
                st = new StringTokenizer(linia);
                st.nextToken();
                w[i] = new Cosik();
                w[i].first = Integer.parseInt(st.nextToken());
                w[i].second = i;
            }

            Arrays.sort(w);

            for (int i = 0; i < n + 1; i++)
                makeset(i);
            /* Przetwarzamy na Find & Union */
            int i = 0, wynik = 0;
            while (i < n){
                /* Przetwarzamy wszystkie budynki o wysokosci w[i].first */
                int i0 = i;
                /* Pierwszy raz - scalanie */
                while (i0 < n && w[i0].first == w[i].first){
                    if (findset(w[i0].second) != findset(w[i0].second + 1))
                        unia(w[i0].second, w[i0].second + 1);
                    i0++;
                }
                /* Drugi raz - wyznaczanie wyniku */
                int poprz = -1;
                i0 = i;
                while (i0 < n && w[i0].first == w[i].first){
                    /* Pozycje drzew o tej samej wysokosci rozwazamy od prawej do lewej */
                    if (findset(w[i0].second) != poprz){
                        poprz = findset(w[i0].second);
                        wynik++;
                    }
                    i0++;
                }
                i=i0;
            }
            System.out.println(wynik);
        }catch(Exception e){
            throw new RuntimeException(e);
        }
    }
};
