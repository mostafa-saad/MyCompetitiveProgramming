/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Osie (OSI)                                                 *}
{*   Plik:    osis2.cpp                                                  *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Rozwiazanie alternatywne. Z³o¿ono¶æ obliczeniowa:          *}
{*            oczekiwana O(n^2). Dzieli boki na pol i sprawdza dla       *}
{*            kazdego wierzcholka, czy przechodzi przez niego os symetrii*}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

typedef long long LL;

#define Cyc(a, b) ((a) < 0 ? (a+b) : (a) >= b ? (a-b) : a) 

struct POINT {
    int x, y;
    POINT(int x=0, int y=0) : x(x), y(y) {}
};

LL sqr(int a) {
    return LL(a) * LL(a);
}

int main() {
    int testy;
    scanf("%d", &testy);
    while(testy--) {
    int n;
    scanf("%d", &n);
    vector<POINT> v(2*n);
    for(int x = 0; x < n; x++) {
    scanf("%d %d", &v[2*x].x, &v[2*x].y); 
    v[2*x].x <<= 1;
    v[2*x].y <<= 1;
    }
    for(int x = 0; x < n; x++) {
    v[2*x+1].x = (v[2*x].x + v[Cyc(2*x+2, 2*n)].x) >> 1;
    v[2*x+1].y = (v[2*x].y + v[Cyc(2*x+2, 2*n)].y) >> 1;
    }
    int res = 0;
// Dla kazdego wierzcholka sprawdzane jest, czy przechodzi przez niego os symetrii
    for(int x = 0; x < 2 * n; x++) {
    bool ok = true;
    for(int y = 1; y <= n; y++) 
        if (sqr(v[x].x - v[Cyc(x + y, 2 * n)].x) + sqr(v[x].y - v[Cyc(x + y, 2 * n)].y) !=
        sqr(v[x].x - v[Cyc(x - y, 2 * n)].x) + sqr(v[x].y - v[Cyc(x - y, 2 * n)].y) ||
        sqr(v[Cyc(x + y - 1, 2 * n)].x - v[Cyc(x + y, 2 * n)].x) + sqr(v[Cyc(x + y - 1, 2 * n)].y - v[Cyc(x + y, 2 * n)].y) != 
        sqr(v[Cyc(x - y + 1, 2 * n)].x - v[Cyc(x - y, 2 * n)].x) + sqr(v[Cyc(x - y + 1, 2 * n)].y - v[Cyc(x - y, 2 * n)].y))
            ok = false;
    if (ok) res++;
    }
    printf("%d\n", res/2);
    }
    return 0;
}
