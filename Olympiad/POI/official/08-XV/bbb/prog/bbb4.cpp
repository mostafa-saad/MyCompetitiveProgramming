/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  BBB (BBB)                                                 *
 *   Plik:     bbb4.cpp                                                  *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie autorskie, zlozonosc O(n).                    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

#define REP(i,n) for( int i = 0; i<int(n); ++i)
#define FOR(i,a,b) for (int i = a ;i<=int(b); ++i)

const int MAX=1100*1000;
const int inf=2*1000*1000*1000+100;

char input[MAX];        // wejsciowe slowo +-
int height[MAX];        // wysokosci bilansu
int licz[4*MAX];        // tablica licznikowa dla wystapien kolejnych wysokosci bilansu (indeksowana wzgledem p-2*n)
int minimum[MAX];        // tablica minimow okien (indeksowana poczatkami)
int n,p,q,x,y,h=0,k,M,opt=inf,r,akt_minimum=inf;
/*         h - wysokosc w trakcie obliczania kolejnych bilansow
        M - 2m z wzorcowego rozwiazania
        opt - znalezione optimum
        akt_minimum - aktualne minimum w trakcie przesuwania okna */
        
char ch;

int main(){
    scanf("%d %d %d %d %d\n",&n,&p,&q,&x,&y);
    fgets(input,MAX,stdin);
    height[0]=0;
    licz[2*n]=1;
    REP(i,n){
        if (input[i]=='+') h++; else h--;
        ++licz[h+2*n];
        if (akt_minimum>h) akt_minimum=h;
        height[i+1]=h;
    }
    /* przetworzenie slowa z wejscia */
    FOR(i,n,2*n-1){
        if (input[i-n]=='+') h++; else h--;
        --licz[height[i-n]+2*n];
        if (licz[akt_minimum+2*n]==0) akt_minimum++;
        ++licz[h+2*n];
        if (akt_minimum>h) akt_minimum=h;
        minimum[i-n+1]=p+akt_minimum-height[i-n+1];
    }
    /* przetworzenie zdublowanego slowa i inicjalizacja tablicy minimow */
    FOR(i,1,n){
        M=(minimum[i]>0)?0:(-minimum[i]);
        M+=(M&1); //M=2m
        if (q-p>height[n]+M) k=(q-p-height[n])>>1; else k=M+((height[n]-(q-p))>>1);
        /* obliczenie potrzebnej liczby zmian znaku */
        r=y*(n-i)+x*k;
        if (r<opt) opt=r;
        /* aktualizacja optimum */
    }
    printf("%d\n",opt);
    return 0;
}
