/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     podb6.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm heurystyczny, o zlozonosci: O(E * V^2).          *
 *             Dwa kolorujace bfsy antygrafu.                            *
 *                                                                       *
 *************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)

const int MAX=26;

int present[MAX];                // reprezentacja polowienia (kolejne miasta 0 lub 1)
int sasiedzi[MAX][MAX];                // tablica list sasiedztwa
int degree[MAX];                // tablica stopni wierzcholkow
int kol[MAX];                        // kolejka do bfs-a
int bylo[MAX];                        // tablica z zapisanymi 0 przy nieodwiedzonych i 1 przy odwiedzonych miastach
int mat[MAX][MAX];                // macierz sasiedztwa antygrafu

int kolp,kolk;                        // kolp - poczatek kolejki (first), kolk - koniec (last)

int n,m,a,b,n2,duzo,mn,gd,v;
int ile_w_podziale,roznica,wiecej_1;
int opt,opt_subset;                // zapamietane rozwiazanie optymalne (koszt i maska bitowa)
int akt=0;

int przelicz(){
    int ret=0;
    REP(i,n)
        REP(j,degree[i])
            ret+=(present[i]^present[sasiedzi[i][j]]);
    return ret;
}
// przeliczenie kosztu polowienia z present

void losuj1(int pocz){        // pocz - wierzcholek od ktorego zaczynamy
    REP(i,n) {bylo[i]=0; present[i]=0;}
    present[pocz]=1;
    kolp=1;
    kolk=0;
    kol[0]=pocz;
    /* ustawienie poczatku */
    hell_1:
    while (kolp>kolk){
        v=kol[kolk];
        REP(i,n){
            if (mat[v][i] && (!bylo[i])){
                bylo[i]=1;
                present[i]=present[v]^1;
                kol[kolp++]=i;
            }
            /* kolorujemy warstwy bfs-a naprzemian tworzac polowienie */
        }
        kolk++;
    }
    REP(i,n) if (!bylo[i]) {kol[kolp++]=i; goto hell_1;}
    /* jeszcze nie wszystkie spojne skladowa pokolorowane => wracamy na gore */
    ile_w_podziale=0;
    REP(i,n) ile_w_podziale+=present[i];
    if (ile_w_podziale==n2) return;
    if (ile_w_podziale<n2)
        {roznica=n2-ile_w_podziale; wiecej_1=0;}
    else
        {roznica=ile_w_podziale-n2; wiecej_1=1;}
    /* ile_w_podziale - liczba miast w polowce nr 1
       roznica - roznica pomieszy ta liczba a n/2
       wiecej_1 - bool okreslajacy czy jest za duzo jedynek, czy zer */

    REP(t,roznica){
        mn=-1000;        /* mn - znalezione minimum , gd - co to minimum realizuje */
        REP(i,n)
            if (present[i]==wiecej_1){
                int k=0;
                REP(j,degree[i]){
                    k+=(present[sasiedzi[i][j]]!=wiecej_1);
                }
                k=(degree[i]-(k<<1));
                if (k>mn){k=mn; gd=i;}
            }
        present[gd]^=1;
    }
    /* zachlanne przerabianie podzialu do polowienia */
}
// pierwszy bfs - koloruje antygraf i zachlannie dopowadza do polowienia

void losuj2(int pocz){
    REP(i,n) {bylo[i]=0; present[i]=0;}
    present[pocz]=1;
    kolp=1;
    kolk=0;
    kol[0]=pocz;
    /* ustawienie poczatku */
    hell_2:
    while (kolp>kolk){
        v=kol[kolk];
        REP(i,n){
            if (mat[v][i]){
                if (!bylo[i]){
                    bylo[i]=1;
                    present[i]=present[v]^1;
                    kol[kolp++]=i;
                } else {
                    if (present[i]==present[v]) present[i]^=1;
                }
            }
            /* kolorujemy warstwy bfs-a naprzemian tworzac polowienie
               znajdujac niepasujacy kolor (wracajac) zmieniamy go */
        }
        kolk++;
    }
    REP(i,n) if (!bylo[i]) {kol[kolp++]=i; goto hell_2;}
    /* jeszcze nie wszystkie spojne skladowa pokolorowane => wracamy na gore */
    ile_w_podziale=0;
    REP(i,n) ile_w_podziale+=present[i];
    if (ile_w_podziale==n2) return;
    if (ile_w_podziale<n2)
        {roznica=n2-ile_w_podziale; wiecej_1=0;}
    else
        {roznica=ile_w_podziale-n2; wiecej_1=1;}
    /* ile_w_podziale - liczba miast w polowce nr 1
       roznica - roznica pomieszy ta liczba a n/2
       wiecej_1 - bool okreslajacy czy jest za duzo jedynek, czy zer */

    REP(t,roznica){
        mn=-1000;        /* mn - znalezione minimum , gd - co to minimum realizuje */
        REP(i,n)
            if (present[i]==wiecej_1){
                int k=0;
                REP(j,degree[i]){
                    k+=(present[sasiedzi[i][j]]!=wiecej_1);
                }
                k=(degree[i]-(k<<1));
                if (k>mn){k=mn; gd=i;}
            }
        present[gd]^=1;
    }
    /* zachlanne przerabianie podzialu do polowienia */
}
/* drugi bfs-y wracajac do zlego koloru przerabiamy go */

void perf(){
    REP(t,n){
        losuj1(t);
        akt=przelicz();
        if (akt<opt){
            opt=akt;
            opt_subset=0;
            REP(i,n) opt_subset^=(present[i]<<i);
        }
        losuj2(t);
        akt=przelicz();
        if (akt<opt){
            opt=akt;
            opt_subset=0;
            REP(i,n) opt_subset^=(present[i]<<i);
        }
    }
}
/* funkcja znajdujaca optimum - odpala oba bfs-y z kazdego wierzcholka */

int main(){
    scanf("%d%d",&n,&m);
    n2=n/2;
    REP(i,n) REP(j,n) mat[i][j]=1;
    REP(i,m){
        scanf("%d%d",&a,&b); a--; b--;
        sasiedzi[a][degree[a]++]=b;
        sasiedzi[b][degree[b]++]=a;
        mat[a][b]=mat[b][a]=0;
    }
    /* wczytywanie wejscia */
    REP(i,n){present[i]=((i<n/2)?1:0);}
    opt=1000;
    opt_subset=(1<<(n/2))-1;
    /* ustawienie poczatkowego polowienia */
    perf();
    int v=opt_subset&1;        /* v - zmienna sygnujaca przynaleznosc miasta 1 */
    REP(i,n){
        if (((opt_subset&(1<<i))!=0)==v){printf("%d ",i+1);}
    }
    printf("\n");
    return 0;
}
