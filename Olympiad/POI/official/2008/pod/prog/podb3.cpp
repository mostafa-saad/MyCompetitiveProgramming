/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     podb3.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm heurystyczny, o zlozonosci: O(duzo * E * V).     *
 *             Losuje wierzcholek, dobiero do niego zachlannie dobre     *
 *             polowienie i wypisuje najmniejszy znaleziony.             *
 *                                                                       *
 *************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)
#define PB push_back

const int MAX=26;

int present[MAX];                // reprezentacja polowienia (dla kolejnych miast 0 lub 1)
int sasiedzi[MAX][MAX];                // tablica list sasiedztwa
int degree[MAX];                // tablica stopni wierzcholkow

int n,m,a,b,n2,duzo;
int opt,opt_sub;
int akt=0;

int przelicz(){
    int ret=0;
    REP(i,n)
        REP(j,degree[i])
            ret+=(present[i]^present[sasiedzi[i][j]]);
    return ret;
}
// przeliczenie kosztu polowienia

void losuj(){
    int pocz=rand()%n;        // wierzcholek poczatkowy
    REP(i,n) present[i]=0;
    present[pocz]=1;
    int min_cost_diff;        // minimalna zmiana kosztu
    vector<int> kand;        // vector rownoprawnych kandydatow
    REP(i,n/2-1){
        min_cost_diff=1000;
        REP(j,n){
            if (!present[j]){
                int s=0;        // s - zmiana kosztu przy dobraniu wierzcholka j
                REP(t,degree[j]) s+=present[sasiedzi[j][t]];
                s=(degree[j]-(s<<1));
                if (s<min_cost_diff){kand.clear(); kand.PB(j); min_cost_diff=s; continue;}
                    // istotnie lepsze rozwiazanie
                if (s==min_cost_diff){kand.PB(j);}
                    // rownorzedne rozwiazanie
            }
        }
        int v=rand()%kand.size();        // wybieramy losowego kandydata
        present[kand[v]]=1;
    }
}
// losowanie polowienia - losujemy poczatkowy wierzcholek i dobieramy w kazdym kroku kolejne minimalizujac koszt podzialu
// sposrod rownoprawnych kandydatow losujemy

void perf(){
    REP(t,duzo){
        losuj();
        akt=przelicz();
        if (akt<opt){
            opt=akt;
            opt_sub=0;
            REP(i,n) opt_sub^=(present[i]<<i);
        }
    }
}
// funkcja znajdujaca optimum - losuje duzo razy, przelicza i wybiera najlepszy wynik

int main(){
    srand(time(NULL));
    scanf("%d%d",&n,&m);
    n2=n/2;
    REP(i,m){
        scanf("%d%d",&a,&b); a--; b--;
        sasiedzi[a][degree[a]++]=b;
        sasiedzi[b][degree[b]++]=a;
    }
    // wczytywanie wejscia
    duzo=20000+150*m;
    // liczba iteracji
    REP(i,n){present[i]=((i<n/2)?1:0);}
    opt=1000;
    opt_sub=(1<<(n/2))-1;
    // ustawienie poczatkowego optimum
    perf();
    int v=opt_sub&1;        // v - zmienna sygnujaca przynaleznosc miasta 1
    REP(i,n){
        if (((opt_sub&(1<<i))!=0)==v){printf("%d ",i+1);}
    }
    printf("\n");
    return 0;
}
