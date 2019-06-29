/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  BBB (BBB)                                                 *
 *   Plik:     bbbs3.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie nieefektywne O(n^3) - kwadratowy dynamik      *
 *             odpalony n razy.                                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>

#define REP(i,n) for( int i = 0; i<int(n); ++i)
#define FOR(i,a,b) for (int i = a ;i<=int(b); ++i)
#define FORD(i,a,b) for (int i = a ;i>=int(b); --i)

const int MAX=1100*1000;
const int inf=1000*1000*1000+100;

int n,p,q,x,y,opt=inf,k;
/*  opt - znalezione optimum */

char input[MAX];        /* wejsciowe slowo +- */

void przesun(){
    char l=input[n];
    FORD(i,n-1,1) input[i+1]=input[i];
    input[1]=l;
}
/* funkcja przesuwajaca wejsciowe slowo cyklicznie o jeden */

int nowy[MAX];                /* tablica do dynamika w ktorej trzymamy wartosci dla nastepenego prefiksu bilansu */
int stary[MAX];                /* tablica z zapamietanymi wartosciami dla starego */

int zrob_prosty(){
    REP(i,n) stary[i]=inf;
    stary[0]=0;
    /* ustalenie sytuacji poczatkowej */
    REP(i,n){
        if (input[i+1]=='+'){
            REP(j,n){
                if ((i+1-2*j)>p) nowy[j]=inf; else {
                    nowy[j]=stary[j]+1;
                    if ((j>0)&&(nowy[j]>stary[j-1])) nowy[j]=stary[j-1];
                }
            }
        } else {
            REP(j,n){
                if ((i+1-2*j)>p) nowy[j]=inf; else {
                    nowy[j]=stary[j];
                    if ((j>0)&&(nowy[j]>stary[j-1]+1)) nowy[j]=stary[j-1]+1;
                }
            }
        }
        /* uaktualnienie dynamika dla odpowiednio + i - w wejsciowym ciagu */
        REP(j,n) stary[j]=nowy[j];
        /* zapamietujemy nowy prefiks */
    }
    return stary[(n+q-p)/2];
}
/* funkcja wykonujaca kwadratowo prosty przypadek - zwraca potrzebna liczbe zmian znaku */

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

