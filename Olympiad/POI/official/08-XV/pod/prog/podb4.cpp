/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     podb4.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm heurystyczny, o zlozonosci: O(duzo * E * V^2).   *
 *             Losuje podzial i poprawia tak jak we                      *
 *             "wzorcowce" autorskiej.                                   *
 *                                                                       *
 *************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)

const int MAX=26;

int present[MAX];                 // aktualne polowienie (dla kolejnych miast zapisane 0 lub 1)
int sasiedzi[MAX][MAX];           // tablica list sasiedztwa
int degree[MAX];                  // stopnie wierzcholkow
int stats[MAX][2];                // zapisane statystyki wierzcholkow - w stats[x][c] liczba sasiadow x nalezacych do polowki c
int mat[MAX][MAX];                // macierz sasiedztwa

int n,m,a,b,n2,duzo,f,v;
int opt,opt_subset;               // znalezione optymalne rozwiazanie (koszt i maska bitowa)
int akt=0;                        // aktualny koszt

int przelicz(){
    int ret=0;
    REP(i,n)
        REP(j,degree[i])
            ret+=(present[i]^present[sasiedzi[i][j]]);
    return ret;
}
// przeliczenie kosztu polowienia z present

void losuj(){
    REP(i,n) present[i]=((i<n/2)?1:0);
    REP(i,1000){
        a=rand()%n; b=rand()%n;
        swap(present[a],present[b]);
    }        /* losowanie podzialu */
    REP(i,n){
        REP(j,degree[i]){
            stats[i][present[sasiedzi[i][j]]]++;
        }
    }        /* obliczenie statystyk */
    for(;;){
        REP(i,n){
            if (present[i]) continue;
            REP(j,n){
                if (!present[j]) continue;
                v=stats[i][0]-stats[i][1]+stats[j][1]-stats[j][0]+mat[i][j]; /* sprawdzenie, czy oplaca sie wymienic */
                /* v - roznica starego i nowego kosztu */
                if (v<0){a=i; b=j; goto hell;} /* oplaca sie */
            }
        }
        break;        /* juz wiecej nie poprawimy - uciekamy */
        hell:
        REP(i,degree[a]){
            stats[sasiedzi[a][i]][0]--;
            stats[sasiedzi[a][i]][1]++;
        }
        present[a]^=1;
        
        REP(i,degree[b]){
            stats[sasiedzi[b][i]][0]++;
            stats[sasiedzi[b][i]][1]--;
        }
        present[b]^=1;
        /* poprawka statystyk i wymiana wierzcholkow */
    }
}
// pojedyncze wylosowanie i poprawienie polowienia

void perf(){
    REP(t,duzo){
        losuj();
        akt=przelicz();
        if (akt<opt){
            opt=akt;
            opt_subset=0;
            REP(i,n) opt_subset^=(present[i]<<i);
        }
    }
}
// funkcja znajdujaca optimum - losuje wiele razy, poprawia i przelicza

int main(){
    srand(time(NULL));
    scanf("%d%d",&n,&m);
    n2=n/2;
    REP(i,m){
        scanf("%d%d",&a,&b); a--; b--;
        sasiedzi[a][degree[a]++]=b;
        sasiedzi[b][degree[b]++]=a;
        mat[a][b]=mat[b][a]=2;
    }
    // wczytanie wejscia
    duzo=500+20*m;
    // liczba iteracji
    opt=1000;
    opt_subset=(1<<(n/2))-1;
    // poczatkowe optimum
    perf();
    int v=opt_subset&1;        // v - zmienna sygnujaca przynaleznosc miasta 1
    REP(i,n){
        if (((opt_subset&(1<<i))!=0)==v){printf("%d ",i+1);}
    }
    printf("\n");
    return 0;
}
