/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  BBB (BBB)                                                 *
 *   Plik:     bbbs1.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie nieefektywne O(n^2) - prosty przypadek        *
 *             odpalony n razy.                                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

#define REP(i,n) for( int i = 0; i<int(n); ++i)
#define FOR(i,a,b) for (int i = a ;i<=int(b); ++i)
#define FORD(i,a,b) for (int i = a ;i>=int(b); --i)

const int MAX=1100*1000;
const int inf=2*1000*1000*1000+100;

int h,n,p,q,x,y,a,b,m,opt=inf,k;
/*  a,b,m - oznaczenia zgodne z opracowaniem
    opt - znalezione optimum
    h - wysokosc bilansu w trakcie przetwarzania */

char input[MAX];        /* wejsciowe slowo +- */

void przesun(){
    char l=input[n];
    FORD(i,n-1,1) input[i+1]=input[i];
    input[1]=l;
}
/* funkcja przesuwajaca wejsciowe slowo cyklicznie o jeden */

int zrob_prosty(){
    h=p;
    a=p;
    FOR(i,1,n){
        if (input[i]=='+') h++; else h--;
        if (h<a) a=h;
    }
    /* obliczenie a */
    b=h-p;
    /* obliczenie b */
    if (a>0) m=0; else m=((-a+1)/2);
    /* obliczenie m */
    if ((q-p)>(b+2*m)) return ((q-p-b)>>1); else return (2*m+((b-(q-p))>>1));
    /* obliczenie potrzebnej liczby zmian znaku */
}
/* funkcja wykonujaca liniowo prosty przypadek - zwraca potrzebna liczbe zmian znaku */

int main(){
    scanf("%d %d %d %d %d\n",&n,&p,&q,&x,&y);
    fgets(input+1,MAX,stdin);
    REP(i,n){
        if (i*y>=opt) break;        /* jesli koszt przesuniecia juz wiekszy niz optimum, wyjdz */
        k=i*y+zrob_prosty()*x;
        if (k<opt) opt=k;
        przesun();
    }
    /* dla kolejnych przesuniec robimy prosty przypadek */
    printf("%d\n",opt);
    return 0;
}
