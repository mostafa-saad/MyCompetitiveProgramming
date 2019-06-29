/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przechadzka Bajtusia (PRZ)                                *
 *   Plik:     prz22.java                                                *
 *   Autor:    Jakub Lacki, Marcin Pilipczuk                             *
 *   Opis:     Rozwiazanie nieoptymalne. Operuje na grafie o m^2         *
 *             krawedziach, ale na kazde zapytanie odpowiada szybko.     *
 *                                                                       *
 *************************************************************************/

import java.lang.*;
import java.io.*;
import java.util.*;
import java.math.*;

public class przs22 implements Runnable{
  public static void main(String[] args){
    new Thread(new przs22()).start();
  }

  final int MAXN = 400;
  final int MAXM = 100000;
  final int MAXD = 100;
  final int ROZMIAR_ALF = 26;
  final int INF = 100000000;
  final char ZNAK_HASH = ('a' + ROZMIAR_ALF);
  final int ROZM_G = (MAXN*MAXN);

  // Reprezentacja grafu
  static class wezel{
    public wezel nastepny;
    public int dokad;
  };

  static class wierzcholek{
    public wezel lista_krawedzi;
  };

  void dodaj(wierzcholek w, int d)
  {
    wezel nowy = new wezel();
    nowy.dokad = d;
    nowy.nastepny = w.lista_krawedzi;
    w.lista_krawedzi = nowy;
  }

  // Implementacja kolejki
  int[] kolejka;
  int poczatek_kolejki, koniec_kolejki;


  void czysc()
  {
    poczatek_kolejki = koniec_kolejki = 0;
  }

  void wstaw(int nr)
  {
    kolejka[koniec_kolejki++] = nr;
    if(koniec_kolejki == ROZM_G)
      koniec_kolejki = 0;
  }

  int wyjmij()
  {
    int ret = kolejka[poczatek_kolejki++];
    if(poczatek_kolejki == ROZM_G)
      poczatek_kolejki = 0;
    return ret;
  }

  boolean czy_pusta()
  {
    return koniec_kolejki == poczatek_kolejki;
  }
  int stworz_indeks(int w1, int w2)
  {
    return w1*MAXN + w2;
  }

  wierzcholek[][] graf_trans, graf;
  int[] odleglosc, poprzedni;
  char[] czym_doszlismy;

  void wczytaj_graf(Scanner scanner, int n, int m)
  {
    char zn;
    int a, b;

    for(int i=0; i<n; i++)
    {
      for(int k=0; k<ROZMIAR_ALF; k++){
        graf[i][k] = new wierzcholek();
        graf_trans[i][k] = new wierzcholek();
        graf[i][k].lista_krawedzi = null;
        graf_trans[i][k].lista_krawedzi = null;
      }
      for(int j=0; j<n; j++)
        if(i != j)
          odleglosc[stworz_indeks(i, j)] = INF;
        else
          odleglosc[stworz_indeks(i, j)] = 0;
    }

    for(int i=0; i<m; i++)
    {
      a = scanner.nextInt();
      b = scanner.nextInt();
      zn = scanner.next().charAt(0);
      a --; b --;
      dodaj(graf[a][(int)zn-'a'], b);
      dodaj(graf_trans[b][(int)zn-'a'], a);
      odleglosc[stworz_indeks(a, b)] = 1;
      czym_doszlismy[stworz_indeks(a, b)] = zn;
    }
  }

  void bfs(int n)
  {
    int akt, poczatek;
    int w1, w2, dokad;

    for(int k=0; k<2; k++)
      for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
          poczatek = stworz_indeks(i, j);
          if(odleglosc[poczatek] == k)
          {
            poprzedni[poczatek] = -1;
            wstaw(poczatek);
          }
        }
    int cnt = 0, c2 = 0;
    while(!czy_pusta())
    {
      akt = wyjmij();
      w1 = akt / MAXN;
      w2 = akt % MAXN;
      c2 ++;
      for(int k=0; k<ROZMIAR_ALF; k++)
        for(wezel ptr=graf[w2][k].lista_krawedzi; ptr != null; ptr = ptr.nastepny)
          for(wezel ptr2=graf_trans[w1][k].lista_krawedzi; ptr2 != null; ptr2 = ptr2.nastepny)
          {
            cnt ++;
            dokad = stworz_indeks(ptr2.dokad, ptr.dokad);
            if(odleglosc[dokad] > odleglosc[akt] + 2)
            {
              odleglosc[dokad] = odleglosc[akt] + 2;
              poprzedni[dokad] = akt;
              czym_doszlismy[dokad] = (char)(k+'a');
              wstaw(dokad);
            }
          }
    }
  }

  void zapytanie(int p, int k)
  {
    int akt, dl;
    akt = stworz_indeks(p, k);
    if(odleglosc[akt] == INF)
    {
      System.out.println("-1");
      return;
    }

    dl = odleglosc[akt];
    System.out.print("" + dl + " ");
    char[] wynik = new char[dl];
    while(poprzedni[akt] != -1)
    {
      wynik[dl/2 - odleglosc[akt]/2] = wynik[dl/2 + (odleglosc[akt]-1)/2] = czym_doszlismy[akt];
      akt = poprzedni[akt];
    }
    if(odleglosc[akt] == 1) //palindrom nieparzysty
      wynik[dl/2] = czym_doszlismy[akt];
    System.out.println(String.valueOf(wynik));
  }


  public void run(){
    try{
      doit();
    }catch(IOException e){
      throw new RuntimeException(e);
    }
  }

  public void doit() throws IOException{
    kolejka = new int[ROZM_G];
    graf_trans = new wierzcholek[MAXN][ROZMIAR_ALF];
    graf = new wierzcholek[MAXN][ROZMIAR_ALF];
    odleglosc = new int[ROZM_G];
    poprzedni = new int[ROZM_G];
    czym_doszlismy = new char[ROZM_G];

    int n, m, d;
    Scanner scanner = new Scanner(System.in);
    int[] zapytania = new int[MAXD];
    n = scanner.nextInt();
    m = scanner.nextInt();
    wczytaj_graf(scanner, n, m);
    bfs(n);
    d = scanner.nextInt();
    for(int i=0; i<d; i++)
      zapytania[i] = scanner.nextInt();
    for(int i=0; i<d-1; i++)
      zapytanie(zapytania[i]-1, zapytania[i+1]-1);
  }
};

