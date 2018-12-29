/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Gildie (GIL)                                              *
 *   Plik:     gilb2.cpp                                                 *
 *   Autor:    Bartlomiej Wolowiec                                       *
 *   Opis:     Rozwiazanie niepoprawne: ustawia zachlannie gildie na     *
 *             przeciwna do sasiadow, gdy nie ma gildii w sasiednich     *
 *             miastach to ustawia na zmiane.                            *
 *                                                                       *
 *************************************************************************/


#include <iostream>
#include <list>
#include <cstdio>
#define VAR(i,a) __typeof(a) i = (a)
#define FORE(i,a) for(VAR(i,(a).begin()); i!=(a).end(); ++i)
using namespace std;

#define MAXN 200100

int kolor=1;
list<int> G[MAXN];
int odw[MAXN];
void go(int a){
    FORE(it, G[a])
        if(odw[*it]){
            odw[a] = 3-odw[*it];
            return;
        }
    odw[a] = kolor;
    kolor = 3-kolor;
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
        go(i);
    }
    printf("TAK\n");
    for(int i=1; i<=n; i++)
        printf("%c\n", odw[i]==1?'K':'S');

    return 0;
}
