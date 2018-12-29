/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gobeliny                                      *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Opis:                 Rozwiazanie bledne - czy wielokat jest        *
 *                         gwiazdzisty?                                  *
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
/* Iloczyn wektorowy */
double det(Point a, Point b) {
    return a.x*b.y-a.y*b.x;
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
        if ((low < high) && ok) return true;
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
    }

    /* Kiepska heurystyka ;) */
    return isStarShaped();

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

