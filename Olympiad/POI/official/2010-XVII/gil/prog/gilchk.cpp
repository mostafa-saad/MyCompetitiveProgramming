/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Gildie (GIL)                                              *
 *   Plik:     gilchk.cpp                                                *
 *   Autor:    Bartlomiej Wolowiec                                       *
 *   Opis:     Weryfikator wyjsc.                                        *
 *                                                                       *
 *************************************************************************/



/*
 * Weryfikator danych wyjściowych do zadania gil
 * Autor: Bartłomiej Wołowiec
 */

/* - */
#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <cstdio>
#define VAR(i,a) __typeof(a) i = (a)
#define FORE(i,a) for(VAR(i,(a).begin()); i!=(a).end(); ++i)
using namespace std;
/* * */

#define MAXN 200100
list<int> G[MAXN];
int kolory[MAXN];
int main(int argc, char *argv[]){
    if(argc!=4){
        printf("?\n");
        return 1;
    }
    ifstream wej, odp, wyj;
    wej.open(argv[1]);
    odp.open(argv[2]);
    wyj.open(argv[3]);

    int n, m, a, b;
    string taknie, stmp;
    wej >> n >> m;
    for(int i=0; i<m; i++){
        wej >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    wyj >> taknie;
    odp >> stmp;
    if(stmp!=taknie){
        cout << "WRONG" << endl;
        cout << "Oczekiwano " << taknie << " a wczytano " << stmp << endl;
        goto koniec;
    }
    if(taknie=="NIE")
        goto ok;
    for(int i=1; i<=n; i++){
        odp >> stmp;
        if(stmp=="K"){
            kolory[i]=1;
        }else if(stmp=="S"){
            kolory[i]=2;
        }else if(stmp=="N"){
            kolory[i]=0;
        }else{
            cout << "WRONG" << endl;
            cout << "Oczekiwano litery 'K' 'S' lub 'N' a wczytano " << stmp << endl;
            goto koniec;
        }
    }
    if(!odp){
            cout << "WRONG" << endl;
            cout << "Zly format odpowiedzi" << endl;
            goto koniec;
    }
    for(int i=1; i<=n; i++){
        int t[3]={0,0,0};
        t[kolory[i]] = 1;
        FORE(it, G[i]) t[kolory[*it]]=1;
        //fprintf(stderr, "%i %i %i\n", t[0], t[1], t[2]);
        if(!t[1] || !t[2]){
            cout << "WRONG" << endl;
            cout << "Wyjscie nie spelnia postulatów gildii" << endl;
            goto koniec;
        }
    }
ok:
    printf("OK\n");

koniec:
    wyj.close();
    odp.close();
    wej.close();
    return 0;
}
