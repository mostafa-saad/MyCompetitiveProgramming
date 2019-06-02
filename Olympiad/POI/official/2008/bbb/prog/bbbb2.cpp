/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  BBB (BBB)                                                 *
 *   Plik:     bbbb2.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie niepoprawne O(n) - odpala prosty przypadek    *
 *             dla przesuniecia do najnizszej pozycji w ciagu.           *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <ctime>

#define REP(i,n) for( int i = 0; i<int(n); ++i)
#define FOR(i,a,b) for (int i = a ;i<=int(b); ++i)

const int MAX=1100*1000;
const int inf=2*1000*1000*1000+100;

int h,n,p,q,x,y,opt,a,b,m,shift,duzo;

char input[MAX];        /* wejsciowe slowo +- */
char temp[MAX];

void przesun(int ile){
    REP(i,n) temp[(i+ile)%n]=input[i];
    REP(i,n) input[i]=temp[i];
}
/* funkcja przesuwajaca wejsciowe slowo cyklicznie o ile */

int zrob_prosty(){
    h=p;
    a=p;
    FOR(i,0,n-1){
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
    srand(time(0));
    scanf("%d %d %d %d %d\n",&n,&p,&q,&x,&y);
    fgets(input,MAX,stdin);
    int min=0;                 /* minimalna wartosc */
    int gdzie_min=0;         /* gdzie zostala osiagnieta */
    h=0;
    REP(i,n){
        if (input[i]=='+') h++; else h--;
        if (h<min){gdzie_min=i; min=h;}
    }
    opt=zrob_prosty()*x;                        // bez przesuniecia
    przesun(gdzie_min);
    min=zrob_prosty()*x+gdzie_min*y;                // przesuniete do minimum
    if (min<opt) opt=min;

    duzo = (8000*1000)/n;                // ilosc iteracji

    REP(t,duzo){
        shift=rand()%n;
        gdzie_min+=shift; gdzie_min%=n;
        przesun(shift);
        min=zrob_prosty()*x+gdzie_min*y;
        if (min<opt) opt=min;
    }
    /* losujemy przesuniecia i sprawdzamy */
    printf("%d\n",opt);
    return 0;
}
