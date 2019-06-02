/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przechadzka Bajtusia (PRZ)                                *
 *   Plik:     prz21.java                                                *
 *   Autor:    Jakub Lacki, Marcin Pilipczuk                             *
 *   Opis:     Rozwiazanie prawie wzorcowe. Dla kazdego zapytania        *
 *             wykonuje BFS                                              *
 *                                                                       *
 *************************************************************************/

import java.lang.*;
import java.io.*;
import java.util.*;
import java.math.*;

public class przs21 implements Runnable{
  public static void main(String[] args){
    new Thread(new przs21()).start();
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


  void czysc()
  {
    poczatek_kolejki = koniec_kolejki = 0;
  }

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

  int stworz_indeks(int w1, int w2, char znak)
  {
    return w1*MAXN*(ROZMIAR_ALF+1) + w2*(ROZMIAR_ALF+1) + (int)(znak-'a');
  }


  int[] odleglosc, poprzedni;
  char[] czym_doszlismy;
  boolean[] czy_koncowy;
  wierzcholek[] graf;
  wierzcholek[][] graf_trans;

  void wczytaj_graf(Scanner scanner, int n, int m)
  {
    char zn;
    int a, b;

    for(int k=0; k<ROZMIAR_ALF+1; k++)
      for(int i=0; i<n; i++){
        graf_trans[i][k] = new wierzcholek();
        graf_trans[i][k].lista_krawedzi = null;
      }
    for(int i=0; i<n; i++){
      graf[i] = new wierzcholek();
      graf[i].lista_krawedzi = null;
    }

    for(int i=0; i<m; i++)
    {
      a = scanner.nextInt();
      b = scanner.nextInt();
      zn = scanner.next().charAt(0);
      a --; b --;
      dodaj(graf[a], b, zn);
      dodaj(graf_trans[b][(int)zn-'a'], a, zn);
    }
  }

  void znajdz_koncowe(int n)
  {
    int ind;
    for(int i=0; i<n; i++)
      for(int j=0; j<n; j++)
        for(int k=0; k<ROZMIAR_ALF+1; k++)
        {
          ind = stworz_indeks(i, j, (char)(k+'a'));
          if(i == j)
            czy_koncowy[ind] = true;
          else
            czy_koncowy[ind] = false;
        }
  }

  void odtworz_wynik(int poczatek, int n)
  {
    int akt, dl, ind, najblizszy, min_odleglosc;
    char[] wynik;

    min_odleglosc = INF;
    najblizszy = -1;
    for(int i=0; i<n; i++)
      for(int k=0; k<ROZMIAR_ALF+1; k++)
      {
        ind = stworz_indeks(i, i, (char)(k+'a'));
        if(odleglosc[ind] < min_odleglosc)
        {
          min_odleglosc = odleglosc[ind];
          najblizszy = ind;
        }
      }


    akt = najblizszy;
    if(min_odleglosc == INF)
    {
      System.out.println("-1");
      return;
    }

    dl = odleglosc[akt];
    wynik = new char[dl];
    System.out.print("" + dl + " ");

    while(poprzedni[akt] != -1)
    {
      if(odleglosc[akt] % 2 == 1)
        wynik[odleglosc[akt]/2] = czym_doszlismy[akt]; 
      else
        wynik[dl-odleglosc[akt]/2] = czym_doszlismy[akt];
      akt = poprzedni[akt];
    }
    System.out.println(String.valueOf(wynik));
  }

  void bfs(int n, int p, int k)
  {
    int akt, poczatek, w1, w2, lit, dokad;
    boolean znalazlem;

    czysc();
    for(int l=0; l<ROZMIAR_ALF+1; l++)
      for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
          akt = stworz_indeks(i, j, (char)(l+'a'));
          odleglosc[akt] = INF;
        }

    poczatek = stworz_indeks(p, k, ZNAK_HASH);
    odleglosc[poczatek] = 0;
    poprzedni[poczatek] = -1;
    wstaw(poczatek);

    znalazlem = false;
    while(!czy_pusta() && !znalazlem)
    {
      akt = wyjmij();
      w1 = akt / ((ROZMIAR_ALF+1)*MAXN);
      w2 = (akt / (ROZMIAR_ALF+1)) % MAXN;
      lit = akt % (ROZMIAR_ALF+1);

      if(lit == ROZMIAR_ALF)
      {
        for(wezel ptr=graf[w1].lista_krawedzi; ptr != null; ptr = ptr.nastepny)
        {
          dokad = stworz_indeks(ptr.dokad, w2, ptr.znak);
          if(odleglosc[dokad] > odleglosc[akt] + 1)
          {
            odleglosc[dokad] = odleglosc[akt] + 1;
            poprzedni[dokad] = akt;
            czym_doszlismy[dokad] = ptr.znak;
            if(czy_koncowy[dokad])
            {
              znalazlem = true;
              break;
            }
            wstaw(dokad);
          }
        }
      }
      else
      {
        for(wezel ptr=graf_trans[w2][lit].lista_krawedzi; ptr != null; ptr = ptr.nastepny)
        {
          dokad = stworz_indeks(w1, ptr.dokad, ZNAK_HASH);
          if(odleglosc[dokad] > odleglosc[akt] + 1)
          {
            odleglosc[dokad] = odleglosc[akt] + 1;
            poprzedni[dokad] = akt;
            czym_doszlismy[dokad] = ptr.znak;
            if(czy_koncowy[dokad])
            {
              znalazlem = true;
              break;
            }
            wstaw(dokad);
          }
        }
      }
    }
    odtworz_wynik(poczatek, n);
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
    czy_koncowy = new boolean[ROZM_G];
    graf = new wierzcholek[MAXN];
    graf_trans = new wierzcholek[MAXN][ROZMIAR_ALF+1];

    int[] zapytania = new int[MAXD];
    int n, m, d;
    Scanner scanner = new Scanner(System.in);
    n = scanner.nextInt();
    m = scanner.nextInt();
    wczytaj_graf(scanner, n, m);
    znajdz_koncowe(n);
    d = scanner.nextInt();
    for(int i=0; i<d; i++)
      zapytania[i] = scanner.nextInt();
    for(int i=0; i<d-1; i++)
      bfs(n, zapytania[i]-1, zapytania[i+1]-1);
  }
};
