/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Gildie (GIL)                                              *
 *   Plik:     gil1.cpp                                                  *
 *   Autor:    Bartlomiej Wolowiec                                       *
 *   Opis:     Alternatywne rozwiazanie wzorcowe.                        *
 *                                                                       *
 *************************************************************************/


#include <iostream>
#include <list>
#include <cstdio>
#define VAR(i,a) __typeof(a) i = (a)
#define FORE(i,a) for(VAR(i,(a).begin()); i!=(a).end(); ++i)
using namespace std;

#define MAXN 200100

int odw[MAXN];
int main(void){
    int n,m,a,b;
    scanf("%i%i", &n, &m);
    for(int i=0; i<m; i++){
        scanf("%i%i", &a, &b);
        if(odw[a] && !odw[b]) odw[b] = 3-odw[a];
        else if(!odw[a] && odw[b]) odw[a] = 3-odw[b];
        else if(!odw[a] && !odw[b]) odw[a] = 1, odw[b] = 2;
    }

    for(int i=1; i<=n; i++)
        if(!odw[i]){
            printf("NIE");
            return 0;
        }

    printf("TAK\n");
    for(int i=1; i<=n; i++)
        printf("%c\n", odw[i]==1?'K':'S');

    return 0;
}
