/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ZOS (Zosia)                                    *
 *   Plik:                zosb.cpp                                       *
 *   Autor:               Krzysztof Dulêba                               *
 *   Opis:                Rozwiazanie niepoprawne.                       *
 *                                                                       *
 *                        Bierzemy zachlannie wierzcholki o najwiekszych *
 *                        stopniach. W pierwszym przebiegu bierzemy      *
 *                        w ogole wszystkie wierzcholki duzego stopnia.  *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#define GRAPH_SIZE 1000000

using namespace std;

vector<int> graph[GRAPH_SIZE];

/**
 * Ktore wierzcholki sa w pokryciu
 */
bool result[GRAPH_SIZE];

int n, k, m, l;

int main(){
    scanf("%d %d %d", &n, &k, &m);

    memset(result, 0, sizeof(result));
    
    /**
     *  wczytujemy graf
     */
    for(int i = 0; i < m; ++i){
        int x, y;
        scanf("%d %d", &x, &y);
        --x; --y;

        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    /**
     * Niestety mogly sie pojawic krawedzie wielokrotne, wiec trzeba je usunac
     */
    for(int i = 0; i < n; ++i){
        sort(graph[i].begin(), graph[i].end());
        graph[i].erase(unique(graph[i].begin(), graph[i].end()), graph[i].end());
    }

    l = n - k;
    int res = n;
    
    /**
     * Bierzemy do pokrycia wierzcholki o duzym stopniu. Jesli mozemy
     * wziac co najwyzej l wierzcholkow, a jakis wierzcholek ma stopien >= l,
     * to musimy go wybrac.
     */
    for(int i = 0; i < n; ++i){
        if((int)graph[i].size() > l){
            --res;
            result[i] = true;
        }
    }

    if(res < k){
        printf("NIE\n");
        exit(0);
    }
    
    /**
     * Usuwamy krawedzie o koncach w pokryciu.
     */
    for(int i = 0; i < n; ++i){
        if(result[i] == true){
            graph[i] = vector<int>();
            continue;
        }
        for(int j = 0; j < (int)graph[i].size(); ++j){
            if(result[graph[i][j]] == true){
                if(j + 1 < (int)graph[i].size()){
                    swap(graph[i][j], graph[i].back());
                }
                graph[i].pop_back();
                --j;
            }
        }
    }

    /**
     * Dopoki sa jakies krawedzie, usuwamy wierzcholek najwiekszego stopnia
     */
    m = 0;
    for(int i = 0; i < n; ++i){
        m += graph[i].size();
    }
    while(m > 0){
        int next = 0;
        for(int i = 0; i < n; ++i){
            if(graph[i].size() > graph[next].size()){
                next = i;
            }
        }
        m -= graph[next].size() * 2;
        result[next] = true;
        --res;
        if(res < k){
            printf("NIE\n");
            exit(0);
        }

        /**
         * Usuwamy krawedzie sasiednie z wierzcholkiem next
         */
        for(int i = 0; i < (int)graph[next].size(); ++i){
            vector<int> & ngh = graph[graph[next][i]];
            for(int j = 0; j < (int)ngh.size(); ++j){
                if(ngh[j] == next){
                    if(j + 1 < (int)ngh.size()){
                        swap(ngh[j], ngh.back());
                    }
                    ngh.pop_back();
                }
            }
        }
        graph[next] = vector<int>();
    }

    printf("%d\n", res);
    bool space = false;
    for(int i = 0; i < n; ++i){
        if(result[i] == false){
            if(space)printf(" ");
            else space = true;
            printf("%d", i + 1);
        }
    }
    printf("\n");
}
