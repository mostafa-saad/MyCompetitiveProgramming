/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Gobeliny                                      *
 *   Autor:                Marcin Andrychowicz                           *
 *   Zlozonosc czasowa:    O(n^2)                                        *
 *   Opis:                 Rozwiazanie alternatywne                      *
 *                                                                       *
 *************************************************************************/

#include <cassert>
#include <cmath>
#include <iostream>
#include <complex>
#include <vector>

using namespace std;

typedef complex<long long> point;

long long det(const point& a,const point& b) {
    return real(a)*imag(b)-imag(a)*real(b);   //iloczyn wektorowy
}
bool turn(const point& a,const point& b,const point& c) {
    return det(b-a,c-b) > 0;   // czy skret ABC jest w lewo
}

// czy odcinek ab przecina cd (zadne trzy punkty nie sa wspolliniowe)
bool intersect_segms(const point& a, const point& b, const point& c, const point& d) {
    return (turn(a,b,c) != turn(a,b,d) && (turn(c,d,a) != turn(c,d,b)));
}

// punkt przeciecia prostych ab i cd a konkretniej jego wspolrzedna na prostej ab (przyjmujac a=0 b=1)
long double intersect_lines(point a, point b, point c, point d) {
    return ((long double)det(d-c, a-c)) / det(a-b, c-d);
}

const int MAX_N = 1000;
const int INF = 1000000000;

int n;
point p[2 * MAX_N + 2];
bool dark[2 * MAX_N + 2];
vector<pair<point, point> > lines;

// czy istnieje punkt na prostej ab nalezacy do przeciecia wszystkich prostych z lines (byc moze zbior pusty)
// i wszystkich polplaszczyzn wyznaczonych przez oswietlone boki?
bool check(point a, point b) {
    long double l = -INF, r = INF;

    // przecinamy proste
    for (int i = 0; i < (int)lines.size(); i++) {
        point c = lines[i].first, d = lines[i].second;
        if (det(b-a, d-c) == 0) { // rownolegle
            if (a != c && b != d)
                return false;
        } else {
            long double x = intersect_lines(a, b, c, d);
            if (l != -INF && l != x)
                return false;
            l = x;
            r = x;
        }
    }

    bool one_point = (l == r);

    // przecinamy polplaszczyzny
    for (int i = 0; i < n; i++) if (!dark[i]) {
            point c = p[i], d = p[i + 1];
            if (det(b-a, d-c) == 0) { // rownolegle
                if (det(d-c, a-c) > 0)
                    return false;
            } else {
                long double x = intersect_lines(a, b, c, d);
                if (one_point && (x == l || x == r))
                    return false;
                if (det(b-a, d-c) > 0)
                    l = max(l, x);
                else
                    r = min(r, x);
                if ((!one_point) && l == r)
                    return false;
            }
            if (r < l)
                return false;
        }

    return true;
}

bool one_test() {
    cin >> n;
    int x, y;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        p[i] = point(x, y);
    }
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        dark[i] = (c == 'C');
    }

    for (int i = 0; i < n; i++) {
        p[n + i] = p[i];
        dark[n + i] = dark[i];
    }
    p[2 * n] = p[0];

    lines.clear();
    int first = 0;
    while(first < n && dark[first])
        first++;
    if (first == n)
        return false; // wszystkie sciany nieoswietlone
    int i = first;
    while(i < first + n) {
        if (dark[i]) {
            int j = i;
            while(dark[j]) j++;
            // katy przy nowej scianie, jeden musi byc wklesly a drugi wypukly
            bool t1 = turn(p[(i+n-1)%n], p[i], p[j]), t2 = turn(p[i], p[j], p[j+1]);
            if (t1 == t2)
                return false;
            // a wszystkie punkty po drodze musza byc po jednej stronie...
            for (int k = i + 1; k + 1 < j; k++)
                if (intersect_segms(p[i], p[j], p[k], p[k+1]))
                    return false;
            // ...i to musi byc dobra strona
            if (j>i+1 && t2 && turn(p[i], p[j], p[j-1]) != turn(p[i], p[j], p[j+1]))
                return false;
            if (j>i+1 && t1 && turn(p[j], p[i], p[(i+n-1)%n]) != turn(p[j], p[i], p[i+1]))
                return false;
            lines.push_back(make_pair(p[i], p[j]));
            i = j;
        } else {
            i++;
        }
    }

    if (lines.empty()) { // wszystkie sciany oswietlone
        for (int i = 0; i < n; i++)
            if (check(p[i], p[i + 1]))
                return true;
        return false;
    } else {
        return check(lines[0].first, lines[0].second);
    }
}

int main() {
    std::ios_base::sync_with_stdio(0);
    int tests;
    cin >> tests;
    while(tests--)
        cout << (one_test() ? "TAK" : "NIE") << endl;
    return 0;
}
