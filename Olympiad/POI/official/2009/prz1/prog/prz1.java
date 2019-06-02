/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     prz1.java                                                 *
 *   Autor:    Adam Gawarkiewicz                                         *
 *   Opis:     Rozwiazanie wzorcowe O(n*K)                               *
 *                                                                       *
 *************************************************************************/
import java.io.*;
import java.util.*;

public class prz1 {
    private static final int MAX_NUM = 100;
    private static final int MAX_N = 100000;
    private static final int X = 0;
    private static final int Y = 1;
    
    /* tablice przechowuj¹ce wierzcho³ki */
    private static int[] s = new int[2*MAX_N]; // 0 lub 1 - ktorego slowa (x lub y) tyczy sie dany wierzcholek
    private static int[] a = new int[2*MAX_N]; // poczatek przedzialu
    private static int[] b = new int[2*MAX_N]; // koniec przedzialu
    private static int[] pKraw = new int[2*MAX_N]; // krawedz przy przejsciu do prefiksu
    private static int[] pWart = new int[2*MAX_N]; // wartosc przy przejsciu do prefiksu
    private static int[] sKraw = new int[2*MAX_N]; // krawedz przy przejsciu do sufiksu
    private static int[] sWart = new int[2*MAX_N]; // wartosc przy przejsciu do sufiksu
    
    private static boolean rowneWierzch(int w1, int w2) {
        return pKraw[w1] == pKraw[w2] && pWart[w1] == pWart[w2]
            && sKraw[w1] == sKraw[w2] && sWart[w1] == sWart[w2];
    }
    
    private static int[] dl = new int[2]; // dlugosc ciagu (n, m)
    private static int[] tab1 = new int[2*MAX_N]; // potrzebne do sortowania przez zliczanie
    private static int[] tab2 = new int[2*MAX_N]; // potrzebne do sortowania przez zliczanie
    private static int ileWierzch;
    private static int[] ile = new int[2*MAX_N]; // potrzebne do sortowania przez zliczanie
    private static int rozmiar;
    private static int maxWart; // maksymalna wartosc nadana przy numerowaniu wierzcholkow

    private static int[][] slowo = new int[2][MAX_N];
    private static int[][] ilosc = new int[2][MAX_NUM]; // ilosci danych liczb calkowitych w ciagu
    private static int[] rozne = new int[2]; // ilosc roznych znakow w ciagach
    private static int[][][] najdluzszySufiks = new int[2][2][MAX_N]; // [poziom][slowo][i]: wartosci dla najdluzszych sufiksow slow [0..i]
    private static int[][][] najdluzszyPrefiks = new int[2][2][MAX_N]; //[poziom][slowo][i]: wartosci dla najdluzszych prefiksow slow [i..n-1]
    private static int poziom; // na ktorym poziomie akurat jestesmy - 0 lub 1
    
    // operacje na zbiorze, wykorzystuja tablice ile
    private static void dodaj(int a) {
        if (ile[a]++ == 0) rozmiar++;
    }
    
    private static void usun(int a) {
        if (--ile[a] == 0) rozmiar--;
    }
    
    private static boolean zawiera(int a) {
        return ile[a]!=0;
    }
    
    private static void tworzPoziom(int sl, int ileZnakow) {
        for (int i = 0; i < MAX_NUM; i++)
            ile[i] = 0;
        rozmiar = 0;
        int poprzedniPoziom = (poziom^1);
        int i = 0, j = 0;
        int ostatnioDodany = 0;
        while (j < dl[sl]) {
            while (j < dl[sl] && (rozmiar < ileZnakow || zawiera(slowo[sl][j]))) {
                if (!zawiera(slowo[sl][j])) ostatnioDodany = slowo[sl][j];
                dodaj(slowo[sl][j]);
                j++;
            }

            s[ileWierzch] = sl;
            a[ileWierzch] = i;
            b [ileWierzch]= j - 1;
            pWart[ileWierzch] = najdluzszyPrefiks[poprzedniPoziom][sl][i];
            sWart[ileWierzch] = najdluzszySufiks[poprzedniPoziom][sl][j - 1];
            pKraw[ileWierzch] = ostatnioDodany;
            while (rozmiar == ileZnakow) {
                sKraw[ileWierzch] = slowo[sl][i];
                usun(slowo[sl][i]);
                i++;
            }
            ileWierzch++;
        }
    }

    private static void sortujWierzcholki() {
        // sortuj wg pKraw, wynik zapisz w tab2
        for (int i = 0; i <= maxWart; i++)
            ile[i] = 0;
        for (int i = 0; i < ileWierzch; i++)
            ile[pKraw[i]]++;
        for (int i = 1; i <= maxWart; i++)
            ile[i] += ile[i-1];
        for (int i = ileWierzch-1; i >= 0; i--)
            tab2[--ile[pKraw[i]]] = i;
        // sortuj tab2 wg pWart, wynik zapisz w tab1
        for (int i = 0; i <= maxWart; i++)
            ile[i] = 0;
        for (int i = 0; i < ileWierzch; i++)
            ile[pWart[tab2[i]]]++;
        for (int i = 1; i <= maxWart; i++)
            ile[i] += ile[i-1];
        for (int i = ileWierzch-1; i >= 0; i--)
            tab1[--ile[pWart[tab2[i]]]] = tab2[i];
        // sortuj tab1 wg sKraw, wynik zapisz w tab2
        for (int i = 0; i <= maxWart; i++)
            ile[i] = 0;
        for (int i = 0; i < ileWierzch; i++)
            ile[sKraw[tab1[i]]]++;
        for (int i = 1; i <= maxWart; i++)
            ile[i] += ile[i-1];
        for (int i = ileWierzch-1; i >= 0; i--)
            tab2[--ile[sKraw[tab1[i]]]] = tab1[i];
        // sortuj tab2 wg sWart, wynik zapisz w tab1
        for (int i = 0; i <= maxWart; i++)
            ile[i] = 0;
        for (int i = 0; i < ileWierzch; i++)
            ile[sWart[tab2[i]]]++;
        for (int i = 1; i <= maxWart; i++)
            ile[i] += ile[i-1];
        for (int i = ileWierzch-1; i >= 0; i--)
            tab1[--ile[sWart[tab2[i]]]] = tab2[i];
    }
    
    private static void numerujWierzcholki() {
        int aktNumer = 0;
        najdluzszyPrefiks[poziom][s[tab1[0]]][a[tab1[0]]] = najdluzszySufiks[poziom][s[tab1[0]]][b[tab1[0]]] = aktNumer;
        for (int i = 1; i < ileWierzch; i++)
            najdluzszyPrefiks[poziom][s[tab1[i]]][a[tab1[i]]] = najdluzszySufiks[poziom][s[tab1[i]]][b[tab1[i]]] =
                (rowneWierzch(tab1[i-1], tab1[i]) ? aktNumer : ++aktNumer);
        maxWart = aktNumer > MAX_NUM ? aktNumer : MAX_NUM;
    }
    
    public static void main(String[] args) {
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            int k = Integer.parseInt(reader.readLine());
            while (k-- > 0) {
                for (int s = X; s <= Y; s++)
                    for (int i = 0; i < MAX_NUM; i++)
                        ilosc[s][i] = 0;
                rozne[X] = rozne[Y] = 0;
                
                StringTokenizer tokenizer = new StringTokenizer(reader.readLine());
                dl[0] = Integer.parseInt(tokenizer.nextToken());
                dl[1] = Integer.parseInt(tokenizer.nextToken());
                for (int s = X; s <= Y; s++) {
                    tokenizer = new StringTokenizer(reader.readLine());
                    for (int i = 0; i < dl[s]; i++) {
                        slowo[s][i] = Integer.parseInt(tokenizer.nextToken()) - 1;
                        if (ilosc[s][slowo[s][i]]==0) rozne[s]++;
                        ilosc[s][slowo[s][i]]++;
                    }
                }
                
                boolean czyRozne = (rozne[X] != rozne[Y]);
                for (int i = 0; i < MAX_NUM; i++)
                    if ((ilosc[X][i]!=0) != (ilosc[Y][i]!=0))
                        czyRozne = true;
                
                if (czyRozne) { // W(x) != W(y)
                    System.out.println("0");
                    continue;
                } else if (rozne[X]==1) { // |W(x)| = |W(y)| = 1
                    System.out.println("1");
                    continue;
                }
                
                poziom = 0;
                for (int s = X; s <= Y; s++)
                    for (int i = 0; i < dl[s]; i++)
                        najdluzszyPrefiks[poziom][s][i] = najdluzszySufiks[poziom][s][i] = slowo[s][i];
                
                maxWart = MAX_NUM;
                for (int ileZnakow = 2; ileZnakow <= rozne[X]; ileZnakow++) {
                    poziom ^= 1;
                    ileWierzch = 0;
                    tworzPoziom(X, ileZnakow);
                    tworzPoziom(Y, ileZnakow);
                    sortujWierzcholki();
                    numerujWierzcholki();
                }
                
                System.out.println((najdluzszyPrefiks[poziom][X][0]==najdluzszyPrefiks[poziom][Y][0]) ? "1" : "0");
            }
        } catch (IOException e) { }
    }
}
