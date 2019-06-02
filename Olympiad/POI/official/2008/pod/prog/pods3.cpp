/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     pods3.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm prawie optymalny, o zlozonosci: O(V * 2^V).      *
 *             Symulacja wymian na wszystkich podzbiorach.               *
 *                                                                       *
 *************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)
#define PB push_back

const int MAX=26;

vector<int> present;                // reprezentacja polowienia (przynaleznosc miast zerojedynkowo
vector<vector<int> > sasiedzi;        // vector list sasiedztwa

int n,m,a,b,n2;                        // n2 = n/2
int ile;                        // liczba miast w polowce oznaczonej jako 1
int opt;
vector<int> opt_subset;                // znalezione rozwiazanie optymalne
int akt=0;                        // aktualny koszt polowienia

void xch(int a){
    if (present[a]) ile--; else ile++;        // aktualizacja ile
    present[a]^=1;
    int k=0;
    REP(i,sasiedzi[a].size()){k+=present[sasiedzi[a][i]];}
    if (present[a]) akt+=(sasiedzi[a].size()-(k<<1)); else akt-=(sasiedzi[a].size()-(k<<1));
    // aktualizacja aktualnego kosztu
    if ((ile==n2)&&(akt<opt)) {opt=akt; opt_subset=present;}
    // aktualizacja optymalnego rozwiazania
}
// funkcja zmieniajaca przynaleznosc miasta a

void perf(int v){ // v - numer miasta ktorego przynaleznosc ustalamy
    if (v<n){
        perf(v+1);
        xch(v);
        perf(v+1);
    }
}
// funkcja rekurencyjnie przegladajaca wszystkie podzialy - przeglada te z aktualnie zapisana przynaleznoscia miasta v,
// po czym ja zmienia i przeglada jeszcze raz

int main(){
    scanf("%d%d",&n,&m);
    sasiedzi=vector<vector<int> >(n,vector<int>());
    n2=(n>>1);
    REP(i,m){
        scanf("%d%d",&a,&b); a--; b--;
        sasiedzi[a].PB(b);
        sasiedzi[b].PB(a);
    }
    // wczytanie wejscia
    REP(i,n){present.PB(0);}
    akt=0;
    opt=1000;
    opt_subset=present;
    // ustawienie poczatkowej sytuacji
    perf(1);
    int v=opt_subset[0];        // przynaleznosc miasta 1
    REP(i,n){
        if (opt_subset[i]==v){printf("%d ",i+1);}
    }
    printf("\n");
    return 0;
}
