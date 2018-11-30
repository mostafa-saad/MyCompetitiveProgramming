/*
TASK: POLY
LANG: C++
*/

// BOI 2005
// Task: CONVEX POLYGON
// Solution
// Author: Ahto Truu

#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

const char iname[] = "POLY.IN"; // input file name
const char oname[] = "POLY.OUT"; // output file name

const int MAXN = 1000; // max number of edges
const double PREC = 0.001; // required precision

int n; // number of edges of the polygon
int e[MAXN]; // required lengths of the edges
double a[MAXN+1]; // polar angles of the vertices

// computes the angle between two points whose
// distance is d on a circle with radius r
double angle(double r, double d) {
    // d / 2 = r * sin(a / 2), solve for a
    return 2.0 * asin(d / (2.0 * r));
}

// tries to space the vertices on a circle with radius r
// the first vertex is always (r, 0)
// if b, places the second vertex below x-axis, else above
// the rest always go in counter-clockwise direction from the second
// returns 0 on success, -1 if radius too short, +1 if radius too long
int place(double r, bool b) {
    static const double twopi = 2.0 * acos(-1.0);
    double prec = asin(PREC / r); // translate the precision to angle
    a[0] = 0.0;
    for (int i = 0; i < n; ++i) {
        a[i + 1] = a[i] + angle(r, e[i]);
        if (i == 0 && b)
            a[i + 1] = twopi - a[i + 1];
    }
    if (a[n] > twopi + prec)
        return (b ? +1 : -1);
    if (a[n] < twopi - prec)
        return (b ? -1 : +1);
    return 0;
}

int main() {
    ifstream ifile(iname);
    ofstream ofile(oname);

    ifile >> n;
    for (int i = 0; i < n; ++i)
        ifile >> e[i];
    sort(e, e + n);
    reverse(e, e + n);

    int s = 0;
    for (int i = 1; i < n; ++i)
        s += e[i];

    if (s > e[0]) {
        // there must be a solution, find it
        double r2 = e[0], r1 = r2 / 2.0;
        bool b = (place(r1, false) > 0);
        // while circle too small, increase the radius
        while (place(r2, b) < 0) {
            r1 = r2; r2 *= 2.0;
        }
        // binary search between the last too small and the first too big
        double r;
        while (true) {
            r = (r1 + r2) / 2.0;
            int x = place(r, b);
            if (x == 0)
                break;
            if (x < 0)
                r1 = r;
            if (x > 0)
                r2 = r;
        }
        // output the result
        ofile.precision(15);
        for (int i = 0; i < n; ++i)
            ofile << r * cos(a[i]) << " " << r * sin(a[i]) << endl;
    } else {
        // there's no solution
        ofile << "NO SOLUTION" << endl;
    }
    return 0;
}
