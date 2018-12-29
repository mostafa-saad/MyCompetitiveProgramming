/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gobeliny                                      *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Opis:                 Rozwiazanie wzorcowe, liczby wymierne         *
 *                                                                       *
 *************************************************************************/


#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>

const long long INF = 1000000000000LL;

/* Punkt lub wektor */
struct Point {

    long long x,y;

    Point() {}
    Point(long long x, long long y) {
        this->x = x;
        this->y = y;
    }

};

/* Roznica wektorow */
Point operator-(Point a, Point b) {
    return Point(a.x-b.x, a.y-b.y);
}
/* Iloczyn skalarny */
long long operator*(Point a, Point b) {
    return a.x*b.x + a.y*b.y;
}
std::pair<long long, long long> operator*(Point a, std::pair<Point, long long> b) {
    return std::make_pair(a*b.first, b.second);
}
/* Mnozenie wektora przez skalar */
Point operator*(Point a, long long k) {
    return Point(a.x*k, a.y*k);
}
/* Obrot wektora o 90 stopni CCW */
Point rot90(Point a) {
    return Point(-a.y, a.x);
}
/* Kwadrat dlugosci wektora */
long long dist2(Point a) {
    return a*a;
}
/* Iloczyn wektorowy */
long long det(Point a, Point b) {
    return a.x*b.y-a.y*b.x;
}

/* Czy kat ABC jest wypukly (kolejnosc wierzcholkow: CW) */
bool convex(Point a, Point b, Point c) {
    return det(b-a, c-b) < 0;
}

/* Czy punkt X lezy wewnatrz trojkata ABC */
bool pointInsideTriangle(Point x, Point a, Point b, Point c) {
    return convex(a,b,x) && convex(b,c,x) && convex(c,a,x);
}

/* Mnozenie dwoch long longow.
   Nie jest poprawne dla dowolnych argumentow,
   ale w tym zastosowaniu wystarcza. */
const long long BASE = (1LL<<32);
std::pair<long long, long long> mul(long long a, long long b) {
    bool minus = (a<0);
    if (minus) a = -a;
    assert( b > 0 );
    assert( (b/BASE) == 0 );
    std::pair<long long, long long> result;
    result.first = (a/BASE) * b;
    result.second = (a%BASE) * b;
    result.first += result.second/BASE;
    result.second %= BASE;
    if (minus) {
        result.first = -result.first;
        result.second = -result.second;
    }
    return result;
}

/* Porownywanie ulamkow */
bool smaller(std::pair<long long, long long> a, std::pair<long long, long long> b) {
    if (a.second < 0) {
        a.first = -a.first;
        a.second = -a.second;
    }
    if (b.second < 0) {
        b.first = -b.first;
        b.second = -b.second;
    }
    return mul(a.first, b.second) < mul(b.first, a.second);
}

/* cosinus kata pomiedzy punktami x, i1, i2
   przemnozony przez dlugosc odcinka i1i2 */
double findCos(Point i1, Point i2, Point x) {
    return det(i2-i1, x-i1) / sqrt(dist2(x-i1));
}

long long labs(long long x) {
    return x>0?x:-x;
}

/* czy punkt cand lezy 'blizej' odcinka i1 i2 niz punkt best */
bool isBetter(Point i1, Point i2, Point best, Point cand) {
    return mul(det(i2-i1,best-i1)*labs(det(i2-i1,best-i1)), dist2(cand-i1)) < mul(det(i2-i1,cand-i1)*labs(det(i2-i1,cand-i1)), dist2(best-i1));
}

/* Prosta { p \in R^2: p*normal=c } */
struct Line {

    Point normal;   /* wektor normalny */
    long long c;

    Line() {}
    /* Prosta przechodzaca przez dwa punkty */
    Line(Point a, Point b) {
        this->normal = rot90(b-a);
        this->c = this->normal*a;
    }

};

/* Czy dwie proste sa rownolegle */
bool parallel(Line a, Line b) {
    return det(a.normal, b.normal) == 0;
}

/* Przeciecie dwoch prostych (nie moga byc rownolegle) */
std::pair<Point, long long> intersect(Line a, Line b) {
    return std::make_pair(rot90(a.normal * b.c - b.normal * a.c), det(a.normal, b.normal));
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
        std::pair<long long, long long> low = std::make_pair(-INF,1);
        std::pair<long long, long long> high = std::make_pair(INF,1);;
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
                    std::pair<long long, long long> tmp = v * intersect(line1, line2);
                    if (det(line1.normal, line2.normal) > 0) {
                        if (smaller(low, tmp)) low = tmp;
                    } else {
                        if (smaller(tmp, high)) high = tmp;
                    }
                }
            }
        if (smaller(low,high) && ok) return true;
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
        std::pair<long long, long long> low = std::make_pair(-INF,1);
        std::pair<long long, long long> high = std::make_pair(INF,1);;
        for(int i=0; i<n; i++) {
            if(i!=i1) {
                Line line2(P[i], P[(i+1)%n]);
                if (parallel(line1, line2)) {
                    if (line2.normal * P[i1] > line2.c)
                        return false;
                } else {
                    std::pair<long long, long long> tmp = v * intersect(line1, line2);
                    //    std::cout << "i = " << i << " tmp = " << tmp.first << ", " << tmp.second << " " << tmp.first/(long double)tmp.second << " ";
                    if (det(line1.normal, line2.normal) > 0) {
                        //      std::cout << "low\n";
                        if (smaller(low, tmp)) low = tmp;
                    } else {
                        //    std::cout << "high\n";
                        if (smaller(tmp, high)) high = tmp;
                    }
                }
            }
        }
        if (!smaller(low,high)) return false;
    } else {
        /*  Jesli sa przynajmniej dwie ciemne sciany, wyznaczamy przeciecie
            prostych na ktorych leza i sprawdzamy, czy to jest dobre miejsce
            na lampe */
        Line line1(P[i1], P[(i1+1)%n]);
        Line line2(P[i2], P[(i2+1)%n]);
        if (parallel(line1, line2)) return false;
        std::pair<Point, long long> v = intersect(line1, line2);
        for(int i=0; i<n; i++) {
            Line line(P[i], P[(i+1)%n]);
            if (dark[i] && (smaller(line.normal*v, std::make_pair(line.c,1)) || smaller(std::make_pair(line.c,1), line.normal*v))) return false;
            //  if (!dark[i] && smaller(std::make_pair(line.c,1), line.normal*v)) return false;
            if (!dark[i] && !smaller(line.normal*v, std::make_pair(line.c,1))) return false;
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

