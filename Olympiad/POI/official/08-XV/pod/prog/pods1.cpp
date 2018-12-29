/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     pods1.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm nieoptymalny, o zlozonosci: O(2^V * E / sqrt(V)).*
 *             Przeliczanie kazdego polowienia tworzonego                *
 *             jak w algorytmie wzorcowym.                               *
 *                                                                       *
 *************************************************************************/
#include <cstdio>

#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)

const int MAX=26;

int present[MAX];                // aktualne polowienie (zerojedynkowo)
int sasiedzi[MAX][MAX];                // tablica list sasiedztwa
int degree[MAX];                // tablica stopni wierzcholkow grafu

int n,m,a,b;
int opt,opt_subset;        // zapamientane optymalne rozwiazanie
int akt=0;                // aktualny koszt
int subset;                // aktualne polowienie jako maska bitowa

int przelicz(){
    int ret=0;
    REP(i,n)
        REP(j,degree[i])
            ret+=(present[i]^present[sasiedzi[i][j]]);
    return ret;
}
// funkcja liczaca koszt aktualnego polowienia

void xch(int a,int b){
    subset^=(1<<a);
    present[a]^=1;
    // a w drugiej polowie

    subset^=(1<<b);
    present[b]^=1;
    // b w drugiej polowie

    akt=przelicz();
    if (akt<opt) {opt=akt; opt_subset=subset;}
    // przeliczamy i aktualizujemy wynik
}
// procedura do wymiany miast a i b pomiedzy polowkami

void perf(int k,int l){
    if ((k==0)||(l==0)) return;
    int seeked=present[k+l-1]^1;        // polowka w ktorej nie znajduje sie miasto k+l-1,
                                        // z ktorej bedziemy wybierac miasto do wymiany
    if (seeked==1) perf(k-1,l); else perf(k,l-1);
    int found;                //znalezione miasto do wymiany
    for(found=0;found<k+l;found++){if (present[found]==seeked) break;}
    xch(found,k+l-1);
    if (seeked==0) perf(k-1,l); else perf(k,l-1);
}
// funkcja symulujaca wymiany w ciagu zlozonym z k zer i l jedynek wsrod pierwszych k+l miast.

int main(){
    scanf("%d%d",&n,&m);
    REP(i,m){
        scanf("%d%d",&a,&b); a--; b--;
        sasiedzi[a][degree[a]++]=b;
        sasiedzi[b][degree[b]++]=a;
    }
    // wczytanie wejscia
    subset=(1<<(n/2))-1;
    REP(i,n){present[i]=((i<n/2)?1:0);}
    opt=przelicz();
    opt_subset=subset;
    // ustawienie warunkow poczatkowych
    perf(n/2-1,n/2);
    int v=(opt_subset&1);        // zmienna sygnujaca przynaleznosc miasta 1
    REP(i,n){
        if (((opt_subset&(1<<i))!=0)==v){printf("%d ",i+1);}
    }
    printf("\n");
    return 0;
}
