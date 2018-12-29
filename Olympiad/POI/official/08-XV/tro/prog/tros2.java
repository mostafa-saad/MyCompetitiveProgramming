/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Trojkaty (TRO)                                            *
 *   Plik:     tros2.java                                                *
 *   Autor:    Marian Marek Kedzierski, Marcina Pilipczuka               *
 *   Opis:     Rozwiazanie nieoptymalne O(n^3).                          *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class tros2 implements Runnable{
	public static void main(String[] args){
		new Thread(new tros2()).start();
	}

    public static class Punkt {
        public int x;
        public int y;

    }

    public int det(Punkt[] t, int i1, int i2){
        return t[i1].x * t[i2].y - t[i1].y * t[i2].x;
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
        long wekt;
        for (int i=0; i<n; ++i)
          for (int j=i+1; j<n; ++j)
            for (int k=j+1; k<n; ++k) {
              wekt = (pun[j].x - pun[i].x) * (pun[k].y - pun[i].y)
                - (pun[k].x - pun[i].x) * (pun[j].y - pun[i].y);
              if (wekt < 0) wekt *= -1;
              wynik += wekt;
            }

        wynik /= 2;
        System.out.println("" + (wynik/2) + "." + (5*(wynik%2)));
            }catch(Exception e){
                    throw new RuntimeException(e);
            }
    }
};
