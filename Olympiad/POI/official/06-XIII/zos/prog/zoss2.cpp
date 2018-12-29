/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ZOS (Zosia)                                    *
 *   Plik:                zoss2.cpp                                      *
 *   Autor:               Krzysztof Dulêba                               *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                                                                       *
 *                        Sprawdzanie wszystkich podzbiorow rozmiaru <= l*
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#define GRAPH_SIZE 1000000
#define MAX_L 11

using namespace std;

vector<int> graph[GRAPH_SIZE];

/**
 * Ktore wierzcholki sa w pokryciu
 */
bool result[GRAPH_SIZE];

int n, k, m, l;

int erased_nodes[MAX_L];
int erased_nodes_count;
int best[MAX_L];
int best_count;

/**
 * backtrack kolejno rozwaza wierzcholki grafu.
 */
void backtrack(int pos, int depth){
    if(depth < 0)return;
    if(erased_nodes_count >= best_count)return;

    bool ok = true;
    for(int i = 0; i < n; ++i){
        ok = false;
        for(int j = 0; j < erased_nodes_count; ++j){
            if(erased_nodes[j] == i){
                ok = true;
                break;
            }
        }
        if(ok)continue;
        ok = true;
        for(int j = 0; j < (int)graph[i].size(); ++j){
            ok = false;
            for(int jj = 0; jj < erased_nodes_count; ++jj){
                if(erased_nodes[jj] == graph[i][j]){
                    ok = true;
                    break;
                }
            }
            if(! ok)break;
        }
        if(! ok)break;
    }
    if(ok && erased_nodes_count < best_count){
        best_count = erased_nodes_count;
        memcpy(best, erased_nodes, sizeof(best));
    }
    if(ok)return;

    if(pos >= n)return;
    
    for(; pos < n; ++pos){
        erased_nodes[erased_nodes_count++] = pos;
        backtrack(pos + 1, depth - 1);
        --erased_nodes_count;
    }
    return;
}

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
    
    erased_nodes_count = 0;
    best_count = MAX_L;
    for(int i = 0; i < best_count; ++i)best[i] = i;
    
    backtrack(0, l);

    int res = n;
    for(int i = 0; i < best_count; ++i){
        result[best[i]] = true;
        --res;
    }

    if(res < k){
        printf("NIE\n");
        exit(0);
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
    return 0;
}
