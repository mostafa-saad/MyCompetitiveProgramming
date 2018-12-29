/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Trojkaty (TRO)                                            *
 *   Plik:     tro1.java                                                *
 *   Autor:    Marcina Pilipczuka                                        *
 *   Opis:     Rozwiazanie wzorcowe O(n*n*logn).                         *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class tro1 implements Runnable{
  public static void main(String[] args){
    new Thread(new tro1()).start();
  }

    public static class Punkt implements Comparable<Punkt> {
        public int x;
        public int y;

        public int compareTo(Punkt p){
            if (y >= 0 && p.y < 0) return -1;
            if (y < 0 && p.y >= 0) return 1;
            if (y == 0 && p.y == 0){
                if (x > 0 && p.x < 0) return -1;
                if (x < 0 && p.x > 0) return 1;
                return 0;
            }
            return -(x * p.y - y * p.x);
        }
    }

    public int det(Punkt[] t, int i1, int i2){
        return t[i1].x * t[i2].y - t[i1].y * t[i2].x;
    }
    public int skal(Punkt[] t, int i1, int i2){
        return t[i1].x * t[i2].x + t[i1].y * t[i2].y;
    }

    public long obrot(int dy, Punkt[] pun){
        int n = pun.length;
        Arrays.sort(pun);

        long res = 0;
        int poz_wie = 0;
        int poz_minus = 1;
        int poz_mnie = 1;
        int poz_zgo = 1;
        for (int i = 0; i < n; ++i){
            if (poz_wie <= i) {
                poz_wie = i + 1;
                while (poz_wie % n != i && det(pun, i, poz_wie % n) == 0 && skal(pun, i, poz_wie % n) > 0) ++poz_wie;
                if (poz_wie > poz_minus) poz_minus = poz_wie;
                while (poz_minus % n != i && det(pun, i, poz_minus % n) > 0) ++poz_minus;
                if (poz_mnie < poz_minus) poz_mnie = poz_minus;
                while (poz_mnie % n != i && det(pun, i, poz_mnie % n) == 0 && skal(pun, i, poz_mnie % n) < 0) ++poz_mnie;
                if (poz_zgo < poz_mnie) poz_zgo = poz_mnie;
                while (poz_zgo % n != i && det(pun, i, poz_zgo % n) < 0) ++poz_zgo;
            }
            //System.out.println("Pun(" + i + ") = (" + pun[i].x + ", " + pun[i].y + ")");
            // System.out.println("E: " + i + "; " + poz_wie + " " + poz_minus + " " + poz_mnie + " " + poz_zgo);
            res += (long)(2*dy + pun[i].y) * (long)pun[i].x * (long)(poz_minus - poz_wie - (poz_zgo - poz_mnie));
        }
        return res;
    }

  public void run(){
    try{
            Scanner sca = new Scanner(System.in);
            int n = sca.nextInt();
            Punkt[] pun = new Punkt[n];
            for (int i = 0; i < n; ++i){
                pun[i] = new Punkt();
                pun[i].x = sca.nextInt();
                pun[i].y = sca.nextInt();
            }

            Punkt[] ptmp = new Punkt[n-1];
            for (int i = 0; i < n-1; ++i)
                ptmp[i] = new Punkt();

            long wynik = 0;
            for (int i = 0; i < n; ++i){
                for (int j = 0; j < n; ++j) if (i != j) {
                    ptmp[j>i ? j-1 : j].x = pun[j].x - pun[i].x;
                    ptmp[j>i ? j-1 : j].y = pun[j].y - pun[i].y;
                }
                wynik += obrot(pun[i].y, ptmp);
            }
            wynik = (-wynik)/2;
            System.out.println("" + (wynik/2) + "." + (5*(wynik%2)));
    }catch(Exception e){
      throw new RuntimeException(e);
    }
  }
};

