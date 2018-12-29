/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     pods2.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm nieoptymalny, o zlozonosci:                      *
 *             O(2^V * E / sqrt(V) + V * 2^V).                           *
 *             Przeliczanie kazdego przedzialu.                          *
 *                                                                       *
 *************************************************************************/
#include <cstdio>

#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)

const int MAX=26;

int present[MAX];                // aktualne polowienie (przynaleznosc miast zerojedynkowo)
int sasiedzi[MAX][MAX];                // tablica list sasiedztwa
int degree[MAX];                // stopnie wierzcholkow

int n,m,a,b,n2;                        // n2 = n/2
int opt,opt_subset;                // znalezione rozwiazanie optymalne
int akt=0;                        // aktualny koszt

int przelicz(){
    int ret=0;
    REP(i,n)
        REP(j,degree[i])
            ret+=(present[i]^present[sasiedzi[i][j]]);
    return ret;
}
// funkcja zwracajaca koszt zapisanego w present polowienia

bool check(){
    int ret=0;
    REP(i,n) ret+=present[i];
    return (ret==n2);
}
// funkcja sprawdzajaca czy aktualny podzial jest polowieniem

void perf(int v){        // v - numer miasta ktorego przynaleznosc chcemy okreslic
    if (v<n){
        present[v]=0; perf(v+1);
        present[v]=1; perf(v+1);
        return;
    } // jesli nie okreslilismy jeszcze wszystkich przynaleznosci, robimy to na 2 sposoby

    // a jesli juz tak, to:
    if (check()){        // sprawdzamy czy mamy polowienie
        akt=przelicz();
        if (akt<opt){
            opt=akt;
            opt_subset=0;
            REP(i,n) opt_subset^=(present[i]<<i);
        }
        // a jak tak, to przeliczmy jego koszt i aktualizujemy wynik
    }
}
// (backtrack) funkcja rekurencyjnie przegladajaca wszystkie podzialy i dla kazdego polowienia obliczajaca koszt,
// wybierajaca optymalny

int main(){
    scanf("%d%d",&n,&m);
    n2=n/2;
    REP(i,m){
        scanf("%d%d",&a,&b); a--; b--;
        sasiedzi[a][degree[a]++]=b;
        sasiedzi[b][degree[b]++]=a;
    }
    // wczytanie wejscia
    REP(i,n) present[i]=(i<n2)?1:0;
    opt=przelicz();
    opt_subset=(1<<(n/2))-1;
    // ustawienie dowolnego polowienia jako optymalnego
    perf(1);
    int v=(opt_subset&1);        // v - zmienna sygnujaca przynaleznosc miasta nr 1
    REP(i,n){
        if (((opt_subset&(1<<i))!=0)==v){printf("%d ",i+1);}
    }
    printf("\n");
    return 0;
}
