/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Pociagi (POC)                                             *
 *   Plik:     poc3.java                                                 *
 *   Autor:    Marek Cygan                                               *
 *   Opis:     Rozwiazanie wzorcowe.                                     *
 *                                                                       *
 *************************************************************************/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;
import java.util.TreeMap;

public class poc3 {
  static final int MAXPOC = 1000; // Max. liczba pociagow
  static final int MAXDL = 128;    // Max. dlugosc pociagu, musi byc potega dwojki
  static final int BMAXDL = 7;   // Liczba poziomow
  static final int MAXOP = 100000; // Max. liczb operacji
  static final int STRMAX = 2*MAXPOC*MAXDL+4*MAXOP; // Max. wielkosc struktur danych do wyliczania max. liczby podobnych pociagow

  //Struktura do reprezentacji dynamicznych tesktow - pozwala na zmiane dowolnych liter w czasie log^2(n)
  //i porownywanie w czasie stalym
  static TreeMap<Long,Integer>[] pary;
  static int[] IdU;

  static class DynTxt{
    private int []heap;
    public DynTxt(){
      heap = new int[2 * MAXDL + 1];
      for (int x = 0; x <= 2 * MAXDL; ++x) heap[x] = 0;
    }
    public void zmiana(int pos, char zn) {
      int poz = BMAXDL;
      heap[pos += MAXDL] = zn;
      while((pos >>= 1) > 0) {
        --poz;
        long klucz = (((long)heap[pos<<1])<<32)+(long)heap[(pos<<1)+1];
        //Integer iter = pary[poz].get(klucz);
        if (!pary[poz].containsKey(klucz)) {
          heap[pos] = ++IdU[poz];
          pary[poz].put(klucz,IdU[poz]);
        } else{
          heap[pos] = pary[poz].get(klucz);
        }
      }
    }
    public char litera(int pos) {
      return (char) heap[pos+MAXDL];
    }
  }

  static DynTxt[] pociag;

  static class operacja {
    public int nast;
    public int waga;
    public int id;
  };

  static operacja[] op;
  static int[] lHead;
  static int opU = 0;

  static int ListLen(int l) {
    int res = 0;
    for(; l != -1; res++) l = op[l].nast;
    return res;
  }

  static class vert {
    public int suma; // Suma wartosci z poddrzewa
    public boolean pocz;
    public int poc;  // Identyfikator pociagu
  };

  static vert[] drzewo;

  static int Rzad(int v) {
    int res = 0;
    for(; v > 0; res++) v >>= 1;
        return res;
  }

  //Funkcja wyznacza dla kazdego pociagu o postaci identyfikowanej przez l
  //najwieksza liczbe pociagow wygladajacych tak samo
  //w pociag[x].heap[0] umieszczany jest wynik
  static void wyliczWynik(int l) {
    int len = ListLen(lHead[l]);
    int start = 1<<Rzad(len);
    int pos = len + start - 1;
    for(int p = lHead[l]; p != -1; p = op[p].nast, pos--) {
      drzewo[pos].poc = op[p].id;
      drzewo[pos].suma = op[p].waga;
      drzewo[pos].pocz = (op[p].waga == 1);
    }
    for (int x = start + 1; x <= start + len - 1; ++x) drzewo[x].suma += drzewo[x-1].suma;
    while (pos != 0) {
      drzewo[pos].suma = Math.max(drzewo[2*pos].suma, drzewo[2*pos+1].suma);
      pos--;
    }
    for (int x = start; x <= start + len - 1; ++x){
      if (drzewo[x].pocz) {
        pociag[drzewo[x].poc].heap[1] = x;
      } else {
        int lewy = pociag[drzewo[x].poc].heap[1];
        int prawy = x;
        int res = 0;
        while(lewy < prawy) {
          if ((lewy & 1) == 1) res = Math.max(res, drzewo[lewy++].suma);
          if ((prawy & 1) == 0) res = Math.max(res, drzewo[prawy--].suma);
          lewy >>= 1;
        prawy >>= 1;
        }
        if (lewy == prawy)
          res = Math.max(res, drzewo[lewy].suma);
        pociag[drzewo[x].poc].heap[0] = Math.max(pociag[drzewo[x].poc].heap[0], res);
      }
    }
  }


  static void dodajElement(int zb, int waga, int id) {
    if (lHead[zb] == -1) {
      lHead[zb] = opU;
      op[lHead[zb]].nast = -1;
    } else {
      op[opU].nast = lHead[zb];
      lHead[zb] = opU;
    }
    op[opU].waga = waga;
    op[opU++].id = id;
  }


  @SuppressWarnings("unchecked")
  public static void main(String[] args){
    new Thread(){
      public void run(){
        try{
          lHead = new int[STRMAX];
          op = new operacja[STRMAX];
          IdU = new int[BMAXDL];
          pociag = new DynTxt[MAXPOC];
          pary = new TreeMap[BMAXDL];
          drzewo = new vert[2 * STRMAX];
          for (int x = 0; x < 2 * STRMAX; ++x) drzewo[x] = new vert();
          for (int x = 0; x < MAXPOC; ++x) pociag[x] = new DynTxt();
          for (int x = 0; x < STRMAX; ++x){
            lHead[x] = -1;
            op[x] = new operacja();
          }
          for (int x = 0; x < BMAXDL; ++x){
            IdU[x] = 0;
            pary[x] = new TreeMap<Long,Integer>();
          }

          BufferedReader bufReader = new BufferedReader(new InputStreamReader(System.in));
          StringTokenizer tokenizer = new StringTokenizer(bufReader.readLine());
          int poc, dl, op;
          poc = Integer.parseInt(tokenizer.nextToken());
          dl = Integer.parseInt(tokenizer.nextToken());
          op = Integer.parseInt(tokenizer.nextToken());

          String buf;
          for (int x = 0; x < poc; ++x){
            buf = bufReader.readLine();
            for (int y = 0; y < dl; ++y) pociag[x].zmiana(y, buf.charAt(y));
            dodajElement(pociag[x].heap[1], 1, x);
          }

          int poc1, pos1, poc2, pos2;
          char l1, l2;
          for (int x = 0; x < op; ++x){
            tokenizer = new StringTokenizer(bufReader.readLine());
            poc1 = Integer.parseInt(tokenizer.nextToken());
            pos1 = Integer.parseInt(tokenizer.nextToken());
            poc2 = Integer.parseInt(tokenizer.nextToken());
            pos2 = Integer.parseInt(tokenizer.nextToken());

            poc1--;  poc2--; pos1--; pos2--;
            l1 = pociag[poc2].litera(pos2);
            l2 = pociag[poc1].litera(pos1);
            dodajElement(pociag[poc1].heap[1], -1, poc1);
            if (poc1 != poc2)
              dodajElement(pociag[poc2].heap[1], -1, poc2);
            pociag[poc1].zmiana(pos1, l1);
            pociag[poc2].zmiana(pos2, l2);
            if (poc1 != poc2)
              dodajElement(pociag[poc1].heap[1], 1, poc1);
            dodajElement(pociag[poc2].heap[1], 1, poc2);
          }
          for (int x = 0; x < poc; ++x) dodajElement(pociag[x].heap[1], -1, x);
          for (int x = 0; x < STRMAX; ++x) if (lHead[x] != -1)
            wyliczWynik(x);
          for (int x = 0; x < poc; ++x)
            System.out.println(pociag[x].heap[0]);
        } catch (IOException e){
        }
      }
    }.start();
  }

}
