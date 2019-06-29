/*
/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przechadzka Bajtusia (PRZ)                                *
 *   Plik:     przs23.java                                               *
 *   Autor:    Jakub Lacki, Marcin Pilipczuk                             *
 *   Opis:     Rozwiazanie nieoptymalne. Operuje na grafie o m^2         *
 *             krawedziach; dla kazdego zapytania wykonuje BFSa          *
 *                                                                       *
 *************************************************************************/

import java.lang.*;
import java.io.*;
import java.util.*;
import java.math.*;

public class przs23 implements Runnable{
  public static void main(String[] args){
    new Thread(new przs23()).start();
  }

  final int MAXN = 400;
  final int MAXM = 100000;
  final int MAXD = 100;
  final int ROZMIAR_ALF = 26;
  final int INF = 100000000;
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

  void wczytaj_graf(Scanner scanner, int n, int m)
  {
    char znak;
    int a, b;

    for(int i=0; i<n; i++)
      for(int k=0; k<ROZMIAR_ALF; k++){
        graf[i][k] = new wierzcholek();
        graf_trans[i][k] = new wierzcholek();
        graf[i][k].lista_krawedzi = null;
        graf_trans[i][k].lista_krawedzi = null;
      }

    for(int i=0; i<m; i++)
    {
      a = scanner.nextInt();
      b = scanner.nextInt();
      znak = scanner.next().charAt(0);
      a --; b --;
      dodaj(graf[a][znak-'a'], b);
      dodaj(graf_trans[b][znak-'a'], a);
    }
  }

  int[] czy_koncowy;
  char[] znak_koncowy;

  int buduj_graf(int n)
  {
    for(int i=0; i<n; i++)
      for(int j=0; j<n; j++)
        czy_koncowy[stworz_indeks(i, j)] = 0;

    for(int i=0; i<n; i++)
      for(int l=0; l<ROZMIAR_ALF; l++)
        for(wezel ptr=graf[i][l].lista_krawedzi; ptr != null; ptr = ptr.nastepny)
        {
          czy_koncowy[stworz_indeks(i, i)] = 1;
          czy_koncowy[stworz_indeks(i, ptr.dokad)] = 2;
          znak_koncowy[stworz_indeks(i, ptr.dokad)] = (char)(l+'a');
        }
    return n*n;
  }

  int[] odleglosc, poprzedni;
  char[] czym_doszlismy;

  void bfs(int n, int poczatek)
  {
    int akt, w1, w2, dokad;

    for(int i=0; i<n; i++)
      for(int j=0; j<n; j++)
        odleglosc[stworz_indeks(i, j)] = INF;


    odleglosc[poczatek] = 0;
    poprzedni[poczatek] = -1;

    czysc();
    wstaw(poczatek);

    while(!czy_pusta())
    {
      akt = wyjmij();
      w1 = akt / MAXN;
      w2 = akt % MAXN;
      for(int k=0; k<ROZMIAR_ALF; k++)
        for(wezel ptr=graf[w1][k].lista_krawedzi; ptr != null; ptr = ptr.nastepny)
          for(wezel ptr2=graf_trans[w2][k].lista_krawedzi; ptr2 != null; ptr2 = ptr2.nastepny)
          {
            dokad = stworz_indeks(ptr.dokad, ptr2.dokad);
            if(odleglosc[dokad] > odleglosc[akt] + 1)
            {
              odleglosc[dokad] = odleglosc[akt] + 1;
              poprzedni[dokad] = akt;
              czym_doszlismy[dokad] = (char)(k+'a');
              wstaw(dokad);
            }
          }
    }
    int min_odleglosc, najblizszy_w, ind;
    najblizszy_w = -1;
    min_odleglosc = INF;
    for(int i=0; i<n; i++)
      for(int j=0; j<n; j++)
      {
        ind = stworz_indeks(i, j);
        if(czy_koncowy[ind] != 0 && 2*odleglosc[ind]+czy_koncowy[ind]-1 < min_odleglosc)
        {
          min_odleglosc = 2*odleglosc[ind]+czy_koncowy[ind]-1;
          najblizszy_w = ind;
        }
      }

    if(najblizszy_w == -1)
      System.out.println("-1");
    else
    {
      int dl = min_odleglosc;
      char[] wynik = new char[dl];

      if(czy_koncowy[najblizszy_w] == 2)
        wynik[dl/2] = znak_koncowy[najblizszy_w];

      System.out.print("" + dl + " ");
      akt = najblizszy_w;
      while(akt != poczatek)
      {
        wynik[odleglosc[akt]-1] = wynik[dl-1-odleglosc[akt]+1] = czym_doszlismy[akt]; 
        akt = poprzedni[akt];
      }
      System.out.println(String.valueOf(wynik));
    }
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
    czy_koncowy = new int[ROZM_G];
    znak_koncowy = new char[ROZM_G];
    odleglosc = new int[ROZM_G];
    poprzedni = new int[ROZM_G];
    czym_doszlismy = new char[ROZM_G];
    int n, m;
    Scanner scanner = new Scanner(System.in);
    int[] droga = new int[MAXD];
    n = scanner.nextInt();
    m = scanner.nextInt();
    wczytaj_graf(scanner, n, m);
    buduj_graf(n);
    int d;
    d = scanner.nextInt();
    for(int i=0; i<d; i++)
      droga[i] = scanner.nextInt();
    for(int i=0; i<d-1; i++)
      bfs(n, stworz_indeks(droga[i]-1, droga[i+1]-1));
  }
};
