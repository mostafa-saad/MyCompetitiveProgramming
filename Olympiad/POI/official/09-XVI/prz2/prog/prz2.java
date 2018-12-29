/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przechadzka Bajtusia (PRZ)                                *
 *   Plik:     przb2.cpp                                                 *
 *   Autor:    Jakub Lacki, Marcin Pilipczuk                             *
 *   Opis:     Rozwiazanie wzorcowe O(A+d)*n^2+m*n)                      *
 *                                                                       *
 *************************************************************************/

import java.lang.*;
import java.io.*;
import java.util.*;
import java.math.*;

public class prz2 implements Runnable{
  public static void main(String[] args){
    new Thread(new prz2()).start();
  }

  final int MAXN = 400;
  final int MAXM = 100000;
  final int MAXD = 100;
  final int ROZMIAR_ALF = 26;
  final int INF = 100000000;
  final char ZNAK_HASH = ('a' + ROZMIAR_ALF);
  final int ROZM_G = (MAXN*MAXN*(ROZMIAR_ALF+1));

  // Reprezentacja grafu
  static class wezel{
    public wezel nastepny;
    public int dokad;
    public char znak;
  };

  static class wierzcholek{
    public wezel lista_krawedzi;
  };


  void dodaj(wierzcholek w, int d, char z)
  {
    wezel nowy = new wezel();
    nowy.dokad = d;
    nowy.znak = z;
    nowy.nastepny = w.lista_krawedzi;
    w.lista_krawedzi = nowy;
  }


  // Implementacja kolejki
  int[] kolejka;
  int poczatek_kolejki, koniec_kolejki;


  void wstaw(int nr)
  {
    kolejka[koniec_kolejki++] = nr;
  }

  int wyjmij()
  {
    return kolejka[poczatek_kolejki++];
  }

  boolean czy_pusta()
  {
    return koniec_kolejki == poczatek_kolejki;
  }

  // Funkcja generujaca jednowymiarowe indeksy wierzcholkow w grafie par
  int stworz_indeks(int w1, int w2, char znak)
  {
    return w1*MAXN*(ROZMIAR_ALF+1) + w2*(ROZMIAR_ALF+1) + (znak-'a');
  }


  int[] odleglosc, poprzedni;
  char[] czym_doszlismy;

  wierzcholek[][] graf;
  wierzcholek[] graf_trans;

  void wczytaj_graf(Scanner scanner, int n, int m)
  {
    char zn;
    int a, b;

    for(int k=0; k<ROZMIAR_ALF+1; k++)
      for(int i=0; i<n; i++){
        graf[i][k] = new wierzcholek();
        graf[i][k].lista_krawedzi = null;
      }
    for(int i=0; i<n; i++){
      graf_trans[i] = new wierzcholek();
      graf_trans[i].lista_krawedzi = null;
    }

    for(int i=0; i<m; i++)
    {
      a = scanner.nextInt();
      b = scanner.nextInt();
      zn = scanner.next().charAt(0);
      a--; b--;
      dodaj(graf[a][(int)zn-'a'], b, zn);
      dodaj(graf_trans[b], a, zn);
    }
  }


  void znajdz_koncowe(int n)
  {
    int ind;
    for(int i=0; i<n; i++)
      for(int j=0; j<n; j++)
        for(int k=0; k<ROZMIAR_ALF+1; k++)
        {
          ind = stworz_indeks(i, j, (char)('a'+k));
          if(i == j && k == ROZMIAR_ALF)
            odleglosc[ind] = 0;
          else
            odleglosc[ind] = INF;
        }

    for(int k=0; k<ROZMIAR_ALF+1; k++)
      for(int i=0; i<n; i++)
        for(wezel ptr=graf[i][k].lista_krawedzi; ptr != null; ptr = ptr.nastepny)
        {
          odleglosc[stworz_indeks(i, ptr.dokad, ZNAK_HASH)] = 1;
          czym_doszlismy[stworz_indeks(i, ptr.dokad, ZNAK_HASH)] = ptr.znak;
        }
  }


  void bfs(int n)
  {
    int akt, poczatek, w1, w2, lit, dokad;

    for(int k=0; k<2; k++)
      for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
          poczatek = stworz_indeks(i, j, ZNAK_HASH);
          if(odleglosc[poczatek] == k)
          {
            poprzedni[poczatek] = -1;
            wstaw(poczatek);
          }
        }
    while(!czy_pusta())
    {
      akt = wyjmij();
      w1 = akt / ((ROZMIAR_ALF+1)*MAXN);
      w2 = (akt / (ROZMIAR_ALF+1)) % MAXN;
      lit = akt % (ROZMIAR_ALF+1);

      if(lit == ROZMIAR_ALF)
      {
        for(wezel ptr=graf_trans[w1].lista_krawedzi; ptr != null; ptr = ptr.nastepny)
        {
          dokad = stworz_indeks(ptr.dokad, w2, ptr.znak);
          if(odleglosc[dokad] > odleglosc[akt] + 1)
          {
            odleglosc[dokad] = odleglosc[akt] + 1;
            poprzedni[dokad] = akt;
            czym_doszlismy[dokad] = ptr.znak;
            wstaw(dokad);
          }
        }
      }
      else
      {
        for(wezel ptr=graf[w2][lit].lista_krawedzi; ptr != null; ptr = ptr.nastepny)
        {
          dokad = stworz_indeks(w1, ptr.dokad, ZNAK_HASH);
          if(odleglosc[dokad] > odleglosc[akt] + 1)
          {
            odleglosc[dokad] = odleglosc[akt] + 1;
            poprzedni[dokad] = akt;
            czym_doszlismy[dokad] = ptr.znak;
            wstaw(dokad);
          }
        }
      }
    }
  }

  void zapytanie(int p, int k)
  {
    int akt, dl;
    akt = stworz_indeks(p, k, ZNAK_HASH);
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
      if((dl-odleglosc[akt]) % 2 == 0)
        wynik[(dl-odleglosc[akt])/2] = czym_doszlismy[akt]; 
      else
        wynik[dl-1-(dl-odleglosc[akt])/2] = czym_doszlismy[akt];
      akt = poprzedni[akt];
    }
    if(odleglosc[akt] == 1)
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
    odleglosc = new int[ROZM_G];
    poprzedni = new int[ROZM_G];
    czym_doszlismy = new char[ROZM_G];
    graf = new wierzcholek[MAXN][ROZMIAR_ALF+1];
    graf_trans = new wierzcholek[MAXN];

    int n, m, d;
    Scanner scanner = new Scanner(System.in);
    int[] zapytania = new int[MAXD];
    n = scanner.nextInt();
    m = scanner.nextInt();
    wczytaj_graf(scanner, n, m);
    znajdz_koncowe(n);
    bfs(n);

    d = scanner.nextInt();
    for(int i=0; i<d; i++)
      zapytania[i] = scanner.nextInt();
    for(int i=0; i<d-1; i++)
      zapytanie(zapytania[i]-1, zapytania[i+1]-1);
  }
};
