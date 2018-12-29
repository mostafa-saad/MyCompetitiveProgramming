/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  BBB (BBB)                                                 *
 *   Plik:     bbbb1.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie niepoprawne O(n), nie przejmuje sie           *
 *             schodzeniem ponizej 0                                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>

#define REP(i,n) for( int i = 0; i<int(n); ++i)

const int MAX=1100*1000;

char input[MAX];	/* wejsciowe slowo +- */

int n,p,q,x,y,h;

int main(){
    scanf("%d %d %d %d %d\n",&n,&p,&q,&x,&y);
    fgets(input,MAX,stdin);
    REP(i,n) if (input[i]=='+') h++; else h--;
    printf("%d\n",x*abs((q-p-h)/2));
    return 0;
}
