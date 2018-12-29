/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  BBB (BBB)                                                 *
 *   Plik:     bbbs6.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie nieefektywne O(n^4) - zamienianie kazdej      *
 *             mozliwej liczby minusow od przodu i plusow od tylu.       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

#define REP(i,n) for( int i = 0; i<int(n); ++i)
#define FORD(i,a,b) for (int i = a ;i>=int(b); --i)

const int MAX=1100*1000;
const int inf=1000*1000*1000+100;

int h,n,p,q,x,y,opt=inf,k;
/*  h - wysokosc w czasie przetwarzania
    opt - znalezione optimum */

int pl,mn;        /* liczby plusow i minusow w calym ciagu */

char input[MAX];        /* wejsciowe slowo +- */

void przesun(){
    char l=input[n-1];
    FORD(i,n-2,0) input[i+1]=input[i];
    input[0]=l;
}
/* funkcja przesuwajaca wejsciowe slowo cyklicznie o 1 */

char changed[MAX];        /* pozmieniane wejsciowe slowo +- */

bool is_ok(){
    int f=p;        /* f - lokalny licznik wysokosci */
    REP(i,n){
        if (changed[i]=='+') f++; else f--;
        if (f<0) return false;
    }
    return (f==q);
}
/* funkcja sprawdzajaca czy ciag +- w check spelnia wlasnosci zadania */

void przepisz(int plusy,int minusy){
    REP(i,n) changed[i]=input[i];
    REP(i,n){
        if (minusy==0) break;
        if (changed[i]=='-'){minusy--; changed[i]='+';}
    }
    FORD(i,n-1,0){
        if (plusy==0) break;
        if (changed[i]=='+'){plusy--; changed[i]='-';}
    }
}
/*  funkcja przepisujaca input do changed tak, by zmienic
      pierwsze minusy minusow na plusy
    i ostatnie plusy plusow na minusy */

int zrob_prosty(){
    REP(i,pl+mn+1){
        REP(j,((i<pl)?(i+1):(pl+1))){
            przepisz(j,i-j);
            if (is_ok()) return i;
        }
    }
    return n+1;
}
/* funkcja liczaca prosty przypadek szesciennie - rozwaza wszystkie mozliwe zmiany i przelicza */

int main(){
    scanf("%d %d %d %d %d\n",&n,&p,&q,&x,&y);
    fgets(input,MAX,stdin);
    pl=0; mn=0;
    REP(i,n) if (input[i]=='+') pl++; else mn++;
    /* liczymy pl i mn */
    REP(i,n){
        if (i*y>=opt) break;
        k=i*y+zrob_prosty()*x;
        if (k<opt) opt=k;
        przesun();
    }
    /* liczymy prosty przypadek dla wszystkich przesuniec */
    printf("%d\n",opt);
    return 0;
}
