/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     podb1.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm heurystyczny, o zlozonosci: O(duzo * E).         *
 *             Losuje podzialy i wybiera najmniejszy.                    *
 *                                                                       *
 *************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)

const int MAX=26;

int present[MAX];        // aktualny podzial (zerojedynkowo)
int sasiedzi[MAX][MAX];        // tablica list sasiedztwa
int degree[MAX];        // tablica stopni

int n,m,a,b,n2,duzo;
int mx,mx_subset;        // znalezione optymalne rozwiazanie (koszt i maska bitowa)
int akt=0;                // aktualny koszt

int przelicz(){
    int ret=0;
    REP(i,n)
        REP(j,degree[i])
            ret+=(present[i]^present[sasiedzi[i][j]]);
    return ret;
}
// przeliczenie kosztu z polowienia z present

bool check(){
    int ret=0;
    REP(i,n) ret+=present[i];
    return (ret==n2);
}
// sprawdzenie czy podzial jest polowieniem

void losuj(){
    REP(i,n){present[i]=rand()&1;}
}
// losowanie podzialu

void perf(){
    REP(t,duzo){
        losuj();
        if (check()){
            akt=przelicz();
            if (akt<mx){
                mx=akt;
                mx_subset=0;
                REP(i,n) mx_subset^=(present[i]<<i);
            }
            //aktualizacja optimum
        }
    }
}
// funkcja szukajaca optimum - losuje podzial i dla polowien oblicza koszt.

int main(){
    srand(time(NULL));
    scanf("%d%d",&n,&m);
    n2=n/2;
    REP(i,m){
        scanf("%d%d",&a,&b); a--; b--;
        sasiedzi[a][degree[a]++]=b;
        sasiedzi[b][degree[b]++]=a;
    }
    // wczytanie wejscia
    duzo=10000+5000*m;
    // duzo - liczba rozwazanych podzialow
    REP(i,n){present[i]=((i<n/2)?1:0);}
    mx=1000;
    mx_subset=(1<<(n/2))-1;
    // ustawienie dowolnego polowienia jako optymalnego
    perf();
    int v=mx_subset&1;        // v - zmienna sygnujaca przynaleznosc miasta 1
    REP(i,n){
        if (((mx_subset&(1<<i))!=0)==v){printf("%d ",i+1);}
    }
    printf("\n");
    return 0;
}
