/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  BBB (BBB)                                                 *
 *   Plik:     bbbb3.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie nieefektywne O(n^3) - kwadratowy dynamik      *
 *             odpalony n razy.                                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>

#define REP(i,n) for( int i = 0; i<int(n); ++i)
#define FOR(i,a,b) for (int i = a ;i<=int(b); ++i)
#define FORD(i,a,b) for (int i = a ;i>=int(b); --i)

const int MAX=1100*1000;

int n,p,q,x,y,k,min,cost,bilans,f,j,h;

char input[MAX];        /* wejsciowe slowo +- */

void przesun(){
    char l=input[n-1];
    FORD(i,n-2,0) input[i+1]=input[i];
    input[0]=l;
}
/* funkcja przesuwajaca wejsciowe slowo cyklicznie o jeden */

void aktualizuj(){
    h=p;
    min=p;
    REP(i,n) {
        if (input[i]=='+') h++; else h--;
        if (h<min) min=h;
    }
    bilans=q-h;
}

int main(){
    scanf("%d %d %d %d %d\n",&n,&p,&q,&x,&y);
    fgets(input,MAX,stdin);
    aktualizuj();
    f=0;
    while ((min<0)&&(f<n)){
        if (input[f]=='+'){f++; continue;}
        if (bilans>0){
            cost+=x;
            input[f]='+';
            aktualizuj();
            f++;
            continue;
        }        /* jak mamy miejsce, to zmieniamy - na + */
        if ((x>y)&&(input[n-1]=='+')){
            cost+=y;
            przesun();
            aktualizuj();
            f+=2;
        } else {
            cost+=x;
            input[f]='+';
            aktualizuj();
            f++;
        }        /* zmieniamy - na + lub przesuwamy */
    }
    printf("%d\n",cost+x*abs(bilans/2));
    return 0;
}

