/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Architekci (ARC)                                          *
 *   Plik:     arc95.java                                                *
 *   Autor:    Marcin Pilipczuk                                          *
 *   Opis:     Alternatywne rozwiazanie wzorcowe z dodanym niepotrzebnym *
 *             drzewem licznikowym; czas: O(n log n); pamiec: O(k)       *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class arcs95 {
  final static int K = (1 << 20);
  final static int MAG = 2 * K;
  static int[] dr;
  static int[] q;
  static int pq, kq;
  static boolean pusta = true;
  static int k;

  static int min(int a, int b){
    return a < b ? a : b;
  }

  static int max(int a, int b){
    return a > b ? a : b;
  }

  static void dodaj(int x){
    int a = 1;
    while (a < MAG){
      a <<= 1;
      if (dr[a] >= x) a++;
    }
    if (a >= MAG + k) return;
    dr[a] = x;
    int b = a + 1;
    while (dr[b] > 0)
      dr[b++] = 0;
    --b;
    while (a > 1 && b > 1){
      a >>= 1; b >>= 1;
      for (int i = a; i <= b; ++i)
        dr[i] = min(dr[i << 1], dr[(i << 1) + 1]);
    }
  }

  static int wyszukaj_max(int a, int b){
    int oa = a;
    int ma = max(dr[a], dr[b]);
    while ((a >> 1) < (b >> 1)){
      if (0 == (a & 1))
        ma = max(ma, dr[a+1]);
      if (1 == (b & 1))
        ma = max(ma, dr[b-1]);
      a >>= 1; b >>= 1;
    }
    a = oa;
    if (dr[a] == ma) return a;
    while(true){
      if (0 == (a & 1))
        if (dr[a+1] >= ma){
          a++; break;
        }
      a >>= 1;
    }
    while (a < MAG){
      a <<= 1;
      if (dr[a] < ma)
        a++;
    }
    return a;
  }

  public static void main(String[] args){
    q = new int[K];
    dr = new int[4*K];
    k = jarclib.inicjuj();
    int x;
    while ((x = jarclib.wczytaj()) > 0){
      if (!pusta && pq == kq){
        int y = q[pq++];
        if (pq == k) pq = 0;
        dodaj(y);
      }
      q[kq++] = x;
      if (kq == k) kq = 0;
      pusta = false;
    }
    int poz = MAG;
    while (dr[poz] > 0) poz++;
    pusta = true;
    while (pusta || pq != kq){
      dr[poz++] = q[pq++];
      if (pq == k) pq = 0;
      pusta = false;
    }
    int a = MAG, b = poz - 1;
    while (a > 1 && b > 1){
      a >>= 1; b >>= 1;
      for (int i = a; i <= b; ++i)
        dr[i] = max(dr[i << 1], dr[(i << 1) + 1]);
    }
    int st = MAG, konc = poz - 1;
    while(k-- > 0){
      poz = wyszukaj_max(st, konc - k);
      jarclib.wypisz(dr[poz]);
      st = poz + 1;
    }
  }
};
