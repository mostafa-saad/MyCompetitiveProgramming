/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     podb2.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Algorytm heurystyczny, o zlozonosci: O(duzo * E * V).     *
 *             Losuje wierzcholek, dobiero do niego losowo optycznie     *
 *             duza klike i wrzuca to jako podzial.                      *
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
int opt,opt_subset;                // znalezione optymalne rozwiazanie (koszt i polowienie jako maska bitowa)
int akt=0;                        // aktualny koszt

int przelicz(){
    int ret=0;
    REP(i,n)
        REP(j,degree[i])
            ret+=(present[i]^present[sasiedzi[i][j]]);
    return ret;
}
// przeliczenie kosztu

void losuj(){
    int pocz=rand()%n;        // poczatkowy wierzcholek - losowy
    REP(i,n) present[i]=0;
    present[pocz]=1;
    int max_deg;                // pomocnicza zmienna do trzymania maksymalnej liczby wierzcholkow z dobranego podgrafu bedacych
                        // sasiadami wierzcholka spoza
    vector<int> kand;        // wektor kandydatow na kolejnych sasiadow
    REP(i,n/2-1){
        max_deg=-1;
        REP(j,n){
            if (!present[j]){
                int s=0;        // s - ilu ma sasiadow rozwazany wiezcholek z dobranego juz podgrafu
                REP(t,degree[j]) s+=present[sasiedzi[j][t]];
                if (s>max_deg){kand.clear(); kand.PB(j); max_deg=s; continue;}
                    // istotnie lepsze rozwiazanie - zerujemy kandydatow
                if (s==max_deg){kand.PB(j);}
                    // rozwiazanie o tym samym stopniu co najlepsze znalezione
            }
        }
        int v=rand()%kand.size();        // wybieramy losowego kandydata
        present[kand[v]]=1;
    }
}
// funkcja losujaca polowienie

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
// funkcja znajdujaca optimum - duzo razy losuje polowienie i przelicza je

int main(){
    srand(time(NULL));
    scanf("%d%d",&n,&m);
    n2=n/2;
    REP(i,m){
        scanf("%d%d",&a,&b); a--; b--;
        sasiedzi[a][degree[a]++]=b;
        sasiedzi[b][degree[b]++]=a;
    }
    //wczytywanie wejscia
    duzo=20000+150*m;
    // liczba losowan
    REP(i,n){present[i]=((i<n/2)?1:0);}
    opt=1000;
    opt_subset=(1<<(n/2))-1;
    // oznaczenie poczatkowego polowienia
    perf();
    int v=opt_subset&1; // v - zmienna sygnujaca przynaleznosc miasta 1
    REP(i,n){
        if (((opt_subset&(1<<i))!=0)==v){printf("%d ",i+1);}
    }
    printf("\n");
    return 0;
}
