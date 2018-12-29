/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Trojkaty (TRO)                                            *
 *   Plik:     tro2.java                                                 *
 *   Autor:    Anna Niewiarowska, Marcina Pilipczuka                     *
 *   Opis:     Rozwiazanie wzorcowe.                                     *
 *                                                                       *
 *************************************************************************/

import java.io.*;
import java.util.*;

public class tro2 implements Runnable{
  public static void main(String[] args){
    new Thread(new tro2()).start();
  }

    static public int actx, acty; //wspolrzedne akt. obrabianego punktu

    public static class Punkt implements Comparable<Punkt> {
        public int x;
        public int y;

        //funkcja porownawcza - sortowanie biegunowe wzgledem punktu (actx, acty)
        public int compareTo(Punkt p){
            double x1,x2,y1,y2;

            x1 = x - actx;
            x2 = p.x - actx;
            y1 = y - acty;
            y2 = p.y - acty;
            if (x1==0 && x2==0) return 0;
            if (x1==0) return -1;
            if (x2==0) return 1;
            double d1 = y1/x1;
            double d2 = y2/x2;
            if ( d1 < d2) return -1;
            if ( d1 > d2) return 1;
            return 0;
        }
    }


    int n; //liczba punktow
    Punkt[] t;

    void input() {
        Scanner sca = new Scanner(System.in);
        n = sca.nextInt();
        t = new Punkt[n];
        for (int i = 0; i < n; ++i){
            t[i] = new Punkt();
            t[i].x = sca.nextInt();
            t[i].y = sca.nextInt();
        }
    }

    //wartosc bezwzgledna iloczynu wektorowego (wektory zaczepione w punkcie (0,0))
    long wekt(Punkt p1, Punkt p2) {
        long tmp = ((long)p1.x) * ((long)p2.y) - ((long)p1.y) * ((long)p2.x);
        if (tmp>=0) return tmp;
        return -tmp;
    }

    //oblicza 2 * (pole trojkatow o najmniejszym wierzcholku nr)
    long pole(int nr) {
       long wyniktmp; //wynik tymczasowy
        Punkt sl = new Punkt(), sp = new Punkt(); //punkt -- suma wspolrzednych punktow na lewo/prawo

        sl.x=0; sl.y=0; sp.x=0; sp.y=0;
        wyniktmp=0;
        for (int i=nr+1; i<n; i++)
            if (t[i].x>actx || (t[i].x==actx && t[i].y<acty) ) {sp.x+=t[i].x-actx; sp.y+=t[i].y-acty;}
            else {sl.x+=t[i].x-actx; sl.y+=t[i].y-acty;}
        for (int i=nr+1; i<n; i++) {
            Punkt p = new Punkt(); p.x=t[i].x-actx; p.y=t[i].y-acty;
            wyniktmp+=wekt(p,sl);
            wyniktmp+=wekt(p,sp);
            if (p.x>0 || (p.x==0 && p.y<0) ) { //punkt przechodzi z prawej na lewa
                sp.x-=p.x; sp.y-=p.y;
                sl.x+=p.x; sl.y+=p.y;
            } else { //punkt przechodzi z lewej na prawa
                sl.x-=p.x; sl.y-=p.y;
                sp.x+=p.x; sp.y+=p.y;
            }
        }
        return (wyniktmp/2); //kazdy trojkat policzony dwa razy
        //wynik jest wciaz zawyzony dwukrotnie: |iloczyn wektorowy| = 2*(pole trojkata)
        //dzieki temu wynik jest calkowity
    }

    public void run(){
    try{
            long wynik2; //wynik zwiekszony dwukrotnie

            input();
            wynik2=0;
            for (int i=0; i<n-2; i++) {
                actx = t[i].x;
                acty = t[i].y;
                Arrays.sort(t, i+1, n);
                wynik2+=pole(i);
            }
            System.out.println("" + (wynik2/2) + "." + (5*(wynik2%2)));
    }catch(Exception e){
      throw new RuntimeException(e);
    }
  }
};

