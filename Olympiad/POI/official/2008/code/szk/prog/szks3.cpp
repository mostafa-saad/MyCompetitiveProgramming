/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Szklana pulapka (SZK)                                     *
 *   Plik:     szks3.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie nieefektywne 3 - symulacja nie krok po kroku  *
 *             O(n*l).                                                   *
 *                                                                       *
 *************************************************************************/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

typedef long long LL;

#define FOR(v,p,k) for(int v=p;v<=k;++v)
#define FORD(v,p,k) for(int v=p;v>=k;--v)
#define FORL(v,p,k) for(int v=p;v<k;++v)
#define REP(i,n) for(int i=0;i<(n);++i)
#define VAR(v,i) __typeof(i) v=(i)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define SIZE(x) (int)x.size()
#define ALL(c) c.begin(),c.end()

const int N = 200*1000;
int xi[N], yi[N], n, wynik[N];
bool jakirog[N];
inline int sgn(int x){ return x < 0 ? -1 : (x == 0 ? 0 : 1); }
int symuluj(int k){
    int ax = xi[k], ay = yi[k];
    int kx, ky;
    if (xi[k] == xi[(k+1)%n]){
        if (jakirog[k]) kx = 1, ky = -1;
        else kx = 1, ky = 1;
        if (yi[k] > yi[(k+1)%n])
            kx *= -1, ky *= -1;
    }else{
        if (jakirog[k]) kx = -1, ky = 1;
        else kx = 1, ky = 1;
        if (xi[k] < xi[(k+1)%n])
            kx *= -1, ky *= -1;
    }
    while(1){
        int bedi = 1000*1000*1000, bekier = 0;
        REP(i, n)
            if ((jakirog[i] == (kx*ky < 0)) && (xi[i]-ax) * kx == (yi[i]-ay) * ky && (xi[i]-ax)*kx > 0)
                if (bedi > (xi[i]-ax) * kx){
                    bedi = (xi[i]-ax) * kx;
                    bekier = i;
                }
        REP(i, n){
            int Ax = min(xi[i], xi[(i+1)%n]);
            int Bx = max(xi[i], xi[(i+1)%n]);
            int Ay = min(yi[i], yi[(i+1)%n]);
            int By = max(yi[i], yi[(i+1)%n]);
            int nodi = Ax == Bx ? (Ax-ax)*kx : (Ay-ay)*ky;
            if (nodi > 0 && nodi < bedi &&
                sgn((Ax-ax) * ky - (Ay-ay) * kx) * sgn((Bx-ax) * ky - (By-ay)* kx) < 0){
                bedi = nodi;
                bekier = Ax == Bx ? -1 : -2;
            }
        }
        if (bekier >= 0) return bekier;
        ax += kx * bedi;
        ay += ky * bedi;
        if (bekier == -2) ky *= -1; else kx *= -1;
    }
}

int main(){
    scanf("%d", &n);
    REP(i, n) scanf("%d%d", &xi[i], &yi[i]);
    REP(i, n){
        if (xi[i]==xi[(i+1)%n]){
            if (sgn(yi[(i+1)%n] - yi[i]) * sgn(xi[(i-1+n)%n] - xi[i]) < 0)
                jakirog[i] = true;
            else
                jakirog[i] = false;
        }else{
            if (sgn(yi[(i-1+n)%n] - yi[i]) * sgn(xi[(i+1)%n] - xi[i]) < 0)
                jakirog[i] = true;
            else
                jakirog[i] = false;
        }
    }
    REP(i, n) if (!wynik[i]){
        wynik[i] = symuluj(i) + 1;
        wynik[wynik[i]-1] = i+1;
    }
    printf("%d\n", n/2);
    REP(i, n) if (wynik[i] < i+1) printf("%d %d\n", wynik[i], i+1);
    return 0;
}
