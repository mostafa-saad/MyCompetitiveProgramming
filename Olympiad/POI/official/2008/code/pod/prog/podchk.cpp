/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Podzial krolestwa (POD)                                   *
 *   Plik:     podchk.cpp                                                *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Program weryfikujacy poprawnosc wyjscia wygenerowanego    *
 *             przez program zawodnika, format:                          *
 *             ./podchk.e in out_zawodnika out_wzorcowy                  *
 *                                                                       *
 *************************************************************************/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace std;

typedef long long LL;

#define REP(i,n) for(int i=0;i<(n);++i)

#define MP make_pair
#define PB push_back
#define F first
#define S second

const int N = 26;
FILE *in, *out, *sol;
int wynik[N];

void cl(){
    fclose(in);
    fclose(out);
    fclose(sol);
}

void WA(char *txt){
    printf("WRONG_ANSWER\n%s\n", txt);
    cl();
    exit(0);
}

/* Wczytywanie wejscia */
int n,m,k;
vector<pair<int,int> > kra;

void wczytaj(){
    fscanf(in,"%d%d",&n,&m);
    int a,b;
    REP(i,m){
        fscanf(in,"%d%d\n",&a,&b); a--; b--;
        kra.PB(MP(a,b));
    }
}

/* Wczytywanie wyjscia zawodnika */

char txt[1000];
int txtpoz;
int czytaj_znak(void){
    while(txt[txtpoz] == 0){
        if (!fgets(txt, 999, out)) return 1000;
        txtpoz = 0;
    }
    return txt[txtpoz++];
}

bool puste(int x){ return x==' ' || x=='\n' || x=='\r' || x == '\t'; }
bool byl_eof = false;
int czytaj_int(void){
    LL liczba = 0LL;
    int w;
    do{ w = czytaj_znak(); } while(puste(w));
    if (w == 1000) WA("Za krotki plik.");
    while(w >= '0' && w <= '9'){
        if (liczba > (1000LL * 1000LL * 1000LL))
            WA("Za duza liczba w pliku.");
        liczba = 10LL * liczba + (LL)(w-'0');
        w = czytaj_znak();
    }
    if (w != 1000 && !puste(w) && !(w >= '0' && w<= '9')) WA("Smieci w pliku.");
    if (w == 1000) byl_eof = true;
    return liczba;
}

bool czy_eof(void){
    if (byl_eof) return true;
    int w; do { w = czytaj_znak(); }while(puste(w));
    return w == 1000;
}

int bylo[N];        // tablica z 1 w miastach ktore zostaly podane przez zawodnika
int res;        // poprawny koszt

void wczytaj_kolka(){
    int g=-1,h;                // g - ostatnie miasto, h - nowowczytane miasto
    REP(i,n/2){
        h=czytaj_int();
        if (!((h>0)&&(h<=n))) WA("Niewlasciwa etykieta miasta.");
        h--;
        if (bylo[h]) WA("Powtorzenie miasta.");
        if (h<g) WA("Niewlasciwa kolejnosc wypisywania miast.");
        g=h;
        bylo[g]=1;
    }
    if (!bylo[0]) WA("Brak miasta nr 1");
    if (!czy_eof()) WA("Smieci na koncu pliku.");
}

char WA_txt[1000];

void sprawdz_kolka(){
    int ret=0;        // koszt zawodnika
    REP(i,m){
        if (bylo[kra[i].F]^bylo[kra[i].S]) ret++;
    }        // liczenie kosztu
    if (ret!=res) {
        sprintf(WA_txt,"Nieoptymalna liczba straznic: oczekiwana: %d, wyliczona na podstawie rozwiazania: %d.",res,ret);
        WA(WA_txt);
    }
}

/* Wczytywanie poprawnego outa */

int bb[N];                //

void wczytaj_sol(){
    int a;
    res=0;
    REP(i,n/2){
        fscanf(sol,"%d\n",&a); a--;
        bb[a]=1;
    }
    REP(i,m){
        if (bb[kra[i].F]^bb[kra[i].S]) res++;
    }        // przeliczenie optymalnego kosztu
}

int main(int argc, char *argv[]){
    if ((in = fopen(argv[1], "r")) == NULL || 
        (out = fopen(argv[2], "r")) == NULL ||
        (sol = fopen(argv[3], "r")) == NULL)
        WA("Brak pliku.");
    wczytaj();
    wczytaj_sol();
    wczytaj_kolka();
    sprawdz_kolka();
    printf("OK\n");
    cl();
    return 0;
}
