/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wyspa (WYS)                                               *
 *   Plik:     wys6.java                                                 *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie wzorcowe O(n+m)                               *
 *                                                                       *
 *************************************************************************/

import java.io.*; 
import java.util.*;


public class wys6 {

/////////////// punkty:
static class Punkt {
    double x, y;
    Punkt(double xx, double yy) { x = xx; y = yy; }
};

static double len(Punkt p) {
  return Math.sqrt(p.x*p.x+p.y*p.y);
}

static double il_wek(Punkt a, Punkt b) {
    return a.x*b.y-a.y*b.x;
}

static Punkt razy_stala(Punkt p, double k) {
    return new Punkt(p.x*k, p.y*k);
}

static Punkt dodaj(Punkt a, Punkt b) {
    return new Punkt(a.x+b.x, a.y+b.y);
}

static Punkt odejmij(Punkt a, Punkt b) {
    return new Punkt(a.x-b.x, a.y-b.y);
}


static Punkt pkt_przec(Punkt a, Punkt b, Punkt c, Punkt d) { // punkt przeciecia linii a-b z c-d
    double p1 = //(a.x-c.x)*(d.y-c.y)-(a.y-c.y)*(d.x-c.x);
      il_wek(odejmij(a, c), odejmij(d, c)); // pole trojkata a-c-d
    double p2 = //(a.x-b.x)*(d.y-c.y)-(a.y-b.y)*(d.x-c.x);
      il_wek(odejmij(a, b), odejmij(d, c)); // pole czworokata a-b-c-d
    double k = p1/p2;
    return dodaj(a, razy_stala(odejmij(b, a), k)); // a+(b-a)*k
//    return new Punkt(a.x+(b.x-a.x)*k, a.y+(b.y-a.y)*k);
}

////////////// program wlasciwy:

static final int MAX_N = 60000;
static final int MAX_M = 1000000;

// wszystkie numeracje od 0

static Punkt punkty[] = new Punkt[MAX_N];

// krawedzie, ktorych nie ma (czyli te z wejscia)
static int brakujace_tab[] = new int[MAX_M]; // dokad krawedz
static int brakujace_next[] = new int[MAX_M]; // wskaznik na nastepna krawedz z tego wierzcholka (lub -1)
static int brakujace_first[] = new int[MAX_N]; // wskaznik na pierwsza krawedz z tego wierzcholka (lub -1)

static int ostatni[] = new int[MAX_N]; // najwiekszy wierzcholek, do ktorego mamy krawedz
    // lub -1 jesli nie zadnego wiekszego niz ostatni dla wczesniejszych wierzcholkow

static boolean czy_obstawiana[] = new boolean[MAX_N]; // tablica tymczasowa: czy krawedz z aktualnego jest blokowana

// trasa
static int ile_stos = 0;
static int stos_nr[] = new int[MAX_N];  // poczatek krawedzi (koniec jest w ostatni[])
static Punkt stos_prz[] = new Punkt[MAX_N]; // punkt przeciecia z poprzednia (dla pierwszej punkt startowy)

static boolean czy_na_lewo(Punkt p, int a, int b) {
    return il_wek(odejmij(p, punkty[a]), odejmij(punkty[b], punkty[a]))<0;
//    return (p.x-punkty[a].x)*(punkty[b].y-punkty[a].y)-(p.y-punkty[a].y)*(punkty[b].x-punkty[a].x)<0;
}

public static void main(String[] args) {
    // wczytywanie
    int N = 0, M = 0;
    BufferedReader rd = new BufferedReader(new InputStreamReader(System.in));
    try {
	String buf = rd.readLine();     
	StringTokenizer input = new StringTokenizer(buf);
	N = Integer.parseInt(input.nextToken());
	M = Integer.parseInt(input.nextToken());
        for (int a = 0; a<N; ++a) {
            buf = rd.readLine();
            input = new StringTokenizer(buf);
            punkty[a] = new Punkt(Integer.parseInt(input.nextToken()), Integer.parseInt(input.nextToken()));
            brakujace_first[a] = -1;
        }   
        for (int a = 0; a<M; ++a) {
            buf = rd.readLine();
            input = new StringTokenizer(buf);
            int i = Integer.parseInt(input.nextToken());
            int j = Integer.parseInt(input.nextToken());
            --i; --j;
            brakujace_tab[a] = j;
            brakujace_next[a] = brakujace_first[i];
            brakujace_first[i] = a;
        }
    } catch (IOException e) { e.printStackTrace(); }                                                                                                         
    
    // znajdowanie krawedzi po ktorych w ogole warto chodzic
    int max_ost = 0;
    for (int a = 0; a<N; ++a) {
        for (int i = brakujace_first[a]; i>=0; i = brakujace_next[i])
            czy_obstawiana[brakujace_tab[i]] = true;
        ostatni[a] = -1;
        for (int b = N-1; b>max_ost; --b)
            if (czy_obstawiana[b])
                czy_obstawiana[b] = false;
            else
                ostatni[a] = max_ost = b; // (czyli konczymy petle, dalej nie trzeba zerowac)
        // wewnetrzna petla zrobi w sumie najwyzej M obrotow
    } 
    
    // szukanie trasy
    // (z zalozenia jakas trasa istnieje)
    stos_nr[0] = 0;
    stos_prz[0] = punkty[0];
    ile_stos = 1;
    for (int a = 1; a<N; ++a) {
        if (ostatni[a]<0) 
            continue;
        for (;;) {
            int ost = stos_nr[ile_stos-1];
            Punkt prz = pkt_przec(punkty[ost], punkty[ostatni[ost]], punkty[a], punkty[ostatni[a]]);
//            System.out.println("punkt przeciecia "+ost+"-"+ostatni[ost]+" z "+a+"-"+ostatni[a]+" to "+prz.x+" "+prz.y);
            // na pewno proste nie sa rownolegle (z zalozenia)
            if (ile_stos>1) {
                int poprz = stos_nr[ile_stos-2]; // przedostatni
                if (czy_na_lewo(prz, poprz, ostatni[poprz])) { // ostatnia krawedz na stosie niepotrzebna
                    --ile_stos;
//                    System.out.println("zdejmuje");
                    continue;
                }
            }
            stos_nr[ile_stos] = a;
            stos_prz[ile_stos] = prz;
            ++ile_stos;
            break;
        }
    }
    
    // liczenie dlugosci trasy
    stos_prz[ile_stos] = punkty[N-1]; // wstawiamy ostatni punkt
    double dl = 0;
    for (int a = 0; a<ile_stos; ++a) {
        dl += len(odejmij(stos_prz[a+1], stos_prz[a]));
//        printf("%d %f %f\n", stos[a].first, stos[a].second.x, stos[a].second.y);
    }
    
    System.out.println(dl);
}
};
