/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gobeliny                                      *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cmath>
#include <iostream>
#include <string>

const double INF = 1e12;
const double EPS = 1e-5;

/* Punkt lub wektor */
struct Point {

    double x,y;

    Point() {}
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }

};

/* Roznica wektorow */
Point operator-(Point a, Point b) {
    return Point(a.x-b.x, a.y-b.y);
}
/* Iloczyn skalarny */
double operator*(Point a, Point b) {
    return a.x*b.x + a.y*b.y;
}
/* Mnozenie wektora przez skalar */
Point operator*(Point a, double k) {
    return Point(a.x*k, a.y*k);
}
/* Obrot wektora o 90 stopni CCW */
Point rot90(Point a) {
    return Point(-a.y, a.x);
}
/* Kwadrat dlugosci wektora */
double dist2(Point a) {
    return a*a;
}
/* Iloczyn wektorowy */
double det(Point a, Point b) {
    return a.x*b.y-a.y*b.x;
}

/* Czy kat ABC jest wypukly (kolejnosc wierzcholkow: CW) */
bool convex(Point a, Point b, Point c) {
    return det(b-a, c-b) < -EPS;
}

/* Czy punkt X lezy wewnatrz trojkata ABC */
bool pointInsideTriangle(Point x, Point a, Point b, Point c) {
    return convex(a,b,x) && convex(b,c,x) && convex(c,a,x);
}

/* cosinus kata pomiedzy punktami x, i1, i2
   przemnozony przez dlugosc odcinka i1i2 */
double findCos(Point i1, Point i2, Point x) {
    return det(i2-i1, x-i1) / sqrt(dist2(x-i1));
}

/* czy punkt cand lezy 'blizej' odcinka i1 i2 niz punkt best */
bool isBetter(Point i1, Point i2, Point best, Point cand) {
    return findCos(i1, i2, best) < findCos(i1, i2, cand);
}

/* Prosta { p \in R^2: p*normal=c } */
struct Line {

    Point normal;   /* wektor normalny */
    double c;

    Line() {}
    /* Prosta przechodzaca przez dwa punkty */
    Line(Point a, Point b) {
        this->normal = rot90(b-a);
        this->c = this->normal*a;
    }

};

/* Czy dwie proste sa rownolegle */
bool parallel(Line a, Line b) {
    return fabs(det(a.normal, b.normal)) < EPS;
}

/* Przeciecie dwoch prostych (nie moga byc rownolegle) */
Point intersect(Line a, Line b) {
    return rot90(a.normal * b.c - b.normal * a.c) * (1.0/det(a.normal, b.normal));
}

const int MAXN = 1000;

int n;              /* Liczba wierzcholkow wielokata */
Point P[MAXN];      /* Punty na obwodzie wielokata */
bool dark[MAXN];    /* dark[i] = czy sciana miedzy p[i] a p[i+1] ma byc ciemna */

/* Czy wielokat jest gwiazdzisty */
bool isStarShaped() {
    /* Sprawdzamy, kazda prosta, ktora potencjalnie moze tworzyc krawedz jadra */
    for(int i=0; i<n; i++) {
        Line line1(P[i], P[(i+1)%n]);
        Point v = P[(i+1)%n] - P[i];
        double low = -INF, high = INF;
        bool ok = true;
        /* Odkladamy na tej prostej przeciecia z pozostalymi prostymi */
        for(int j=0; j<n; j++) if(i!=j) {
                Line line2(P[j], P[(j+1)%n]);
                if (parallel(line1, line2)) {
                    /* Proste rownolegle stanowia szczegolny przypadek */
                    if (line2.normal * P[i] > line2.c) {
                        ok = false;
                        break;
                    }
                } else {
                    double tmp = v * intersect(line1, line2);
                    if (det(line1.normal, line2.normal) > 0) {
                        if (tmp > low) low = tmp;
                    } else {
                        if (tmp < high) high = tmp;
                    }
                }
            }
        if ((low + EPS < high) && ok) return true;
    }
    return false;
}

bool singleTest() {

    /* Wczytywanie danych */
    std::cin >> n;

    for(int i=0; i<n; i++)
        std::cin >> P[i].x >> P[i].y;

    for(int i=0; i<n; i++) {
        std::string temp;
        std::cin >> temp;
        dark[i] = temp[0]=='C';
    }

    /* Sprawdzanie, czy wszystkie sciany maja byc ciemne/jasne */
    bool allDark = true, allLight = true;
    for(int i=0; i<n; i++)
        if (dark[i])
            allLight = false;
        else
            allDark = false;

    if (allDark)
        return false;

    if (allLight)
        return isStarShaped();

    /* Wykonujemy redukcje dopoki to jest mozliwe */
    while(true) {

        /* Jesli sa trzy sciany w tym przynajmniej jedna ciemna, to sie nie da */
        if (n==3) return false;

        /* Wyszukiwanie dwoch ciemnych scian tworzacych kat wypukly */
        int i1=0,i2=0,i3=0;
        for(i1=0; i1<n; i1++) {
            i2 = (i1+1)%n;
            i3 = (i2+1)%n;
            if (dark[i1] && dark[i2] && convex(P[i1], P[i2], P[i3]))
                break;
        }
        if (i1==n) break;

        /* Wyszukiwanie wierzcholka wchodzacego najglebiej w znaleziony kat */
        int best = -1;
        for(int i=0; i<n; i++)
            if (i!=i1 && i!=i2 && i!=i3 && pointInsideTriangle(P[i], P[i1], P[i2], P[i3]))
                if ((-1) == best || isBetter(P[i1], P[i2], P[best], P[i]))
                    best = i;

        /* Jesli takiego wierzcholka nie ma, zastepujemy dwie ciemne sciany przez jedna */
        if ((-1) == best) {
            for(int i=i2+1; i<n; i++) {
                P[i-1] = P[i];
                dark[i-1] = dark[i];
            }
            n--;
            continue;
        }

        int j1 = i2, j2 = best;
        if (j2 < j1) std::swap(j1, j2);


        /* Sprawdzenie, czy po ktorejs stronie znalezionego wierzcholka maja byc same ciemne sciany */
        bool allDark1=true, allDark2=true;

        for(int i=0; i<n; i++)
            if (!dark[i]) {
                if (i>=j1 && i<j2)
                    allDark1 = false;
                else
                    allDark2 = false;
            }

        /* Jesli po obu stronach maja byc jakies jasne sciany, to sie nie da */
        if (!allDark1 && !allDark2)
            return false;

        /* "Odcinamy" te czesc wielokata, w ktorej maja byc same ciemne sciany */
        if (allDark1) {
            for(int i=j2; i<n; i++) {
                P[i-(j2-j1-1)] = P[i];
                dark[i-(j2-j1-1)] = dark[i];
            }
            dark[j1] = true;
            n -= (j2-j1-1);
        } else {
            for(int i=j1; i<=j2; i++) {
                P[i-j1] = P[i];
                dark[i-j1] = dark[i];
            }
            n = (j2-j1+1);
            dark[n-1] = true;
        }

    }

    /* Jesli dwie sasiednie sciany maja byc ciemne, to sie nie da */
    for(int i=0; i<n; i++)
        if (dark[i] && dark[(i+1)%n])
            return false;

    /*  Jesli katy po obu stronach jakiejs ciemnej sciany
        sa oba wypukle lub oba niewypukle, to sie nie da */
    for(int i=0; i<n; i++) {
        int i1 = i;
        int i2 = (i+1)%n;
        int i3 = (i+2)%n;
        int i4 = (i+3)%n;
        if (dark[i2] && convex(P[i1],P[i2],P[i3]) == convex(P[i2],P[i3],P[i4])) return false;
    }

    /* Szukamy dwoch ciemnych scian */
    int i1 = 0;
    while(!dark[i1]) i1++;
    int i2 = i1+1;
    while(i2<n && !dark[i2]) i2++;

    if (i2==n) {
        /*  Jesli jest tylko jedna ciemna sciana, odkladamy na niej
            przeciecia polplaszczyn wyznaczanych przez jasne sciany */
        Line line1(P[i1], P[(i1+1)%n]);
        Point v = P[(i1+1)%n] - P[i1];
        double low = -INF, high = INF;
        for(int i=0; i<n; i++) {
            if(i!=i1) {
                Line line2(P[i], P[(i+1)%n]);
                if (parallel(line1, line2)) {
                    if (line2.normal * P[i1] > line2.c)
                        return false;
                } else {
                    double tmp = v * intersect(line1, line2);
                    if (det(line1.normal, line2.normal) > 0) {
                        if (tmp > low) low = tmp;
                    } else {
                        if (tmp < high) high = tmp;
                    }
                }
            }
        }
        if (low + EPS > high) return false;
    } else {
        /*  Jesli sa przynajmniej dwie ciemne sciany, wyznaczamy przeciecie
            prostych na ktorych leza i sprawdzamy, czy to jest dobre miejsce
            na lampe */
        Line line1(P[i1], P[(i1+1)%n]);
        Line line2(P[i2], P[(i2+1)%n]);
        if (parallel(line1, line2)) return false;
        Point v = intersect(line1, line2);
        for(int i=0; i<n; i++) {
            Line line(P[i], P[(i+1)%n]);
            if (dark[i] && fabs(line.normal*v - (double)line.c) > EPS) return false;
            if (!dark[i] && (line.normal*v > (double)line.c - EPS)) return false;
        }
    }

    /* Jesli do tej pory nie stwierdzilismy, ze sie nie da, to sie da */
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(0);
    int tests;
    std::cin >> tests;
    while(tests--)
        if (singleTest())
            std::cout << "TAK\n";
        else
            std::cout << "NIE\n";
    return 0;
}

