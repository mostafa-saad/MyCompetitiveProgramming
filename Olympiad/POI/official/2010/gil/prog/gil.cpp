/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Gildie (GIL)                                              *
 *   Plik:     gil.cpp                                                   *
 *   Autor:    Bartlomiej Wolowiec                                       *
 *   Opis:     Rozwiazanie wzorcowe.                                     *
 *                                                                       *
 *************************************************************************/


#include <iostream>
#include <list>
#include <cstdio>
#define VAR(i,a) __typeof(a) i = (a)
#define FORE(i,a) for(VAR(i,(a).begin()); i!=(a).end(); ++i)
using namespace std;

#define MAXN 200100

list<int> G[MAXN];
int odw[MAXN];
void go(int a, int gildia){
    if(odw[a]) return;
    odw[a]=gildia;
    FORE(it, G[a])
        go(*it, 3-gildia);
}

int main(void){
    int n,m,a,b;
    scanf("%i%i", &n, &m);
    for(int i=0; i<m; i++){
        scanf("%i%i", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
    }
    for(int i=1; i<=n; i++){
        if(G[i].empty()){
            printf("NIE\n");
            return 0;
        }
        go(i, 1);
    }
    printf("TAK\n");
    for(int i=1; i<=n; i++)
        printf("%c\n", odw[i]==1?'K':'S');

    return 0;
}
