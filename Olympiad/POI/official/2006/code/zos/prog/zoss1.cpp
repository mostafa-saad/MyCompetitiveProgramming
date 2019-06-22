/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ZOS (Zosia)                                    *
 *   Plik:                zoss1.cpp                                      *
 *   Autor:               Krzysztof Dulêba                               *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                                                                       *
 *                        Czysty backtracking.                           *
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

/**
 * backtrack kolejno bierze krawedzie w grafie. Ktorys z koncow
 * musi byc w pokryciu, wiec sprawdzimy oba i wezmiemy lepszy
 * rezultat.
 * Przeszukiwanie przerywamy, gdy depth spadnie ponizej 0.
 * depth w istocie oznacza, ile jeszcze wierzcholkow mozemy wziac do pokrycia.
 * pos i epos wyznaczaja kolejna krawdz, ktora ma byc sprawdzona
 * (pos to numer indeks wierzcholka w avail_nodes, epos to indeks
 * krawedzi na jego liscie sasiedztwa).
 */
int backtrack(int pos, int epos, int depth){
    int acc = 0;
    while(true){
        if(depth < 0)return -1;
        if(pos >= n)return acc;
        if(erased_nodes_count >= MAX_L)return -1;

        bool is_pos_erased = false;
        for(int i = 0; i < erased_nodes_count; ++i){
            if(erased_nodes[i] == pos){
                is_pos_erased = true;
                break;
            }
        }
        if(! is_pos_erased){
            for(int i = epos; i < (int)graph[pos].size(); ++i){
                int end = graph[pos][i];
                bool is_end_erased = false;
                for(int j = 0; j < erased_nodes_count; ++j){
                    if(erased_nodes[j] == end){
                        is_end_erased = true;
                        break;
                    }
                }
                if(is_end_erased)continue;

                if(end < pos){
                    fprintf(stderr, "to juz powinno byc zrobione\n");
                    abort();
                }

                /**
                 * Mamy niezalatwiona krawedz.
                 *
                 * Bierzemy pierwszy koniec, zapamietujemy rozwiazanie.
                 * Bierzemy drugi, porownujemy rozwiazanie z pierwszym,
                 * zwracamy lepsze.
                 */
                int orig_erased_nodes[MAX_L];
                int orig_erased_nodes_count = erased_nodes_count;
                memcpy(orig_erased_nodes, erased_nodes, sizeof(orig_erased_nodes));

                erased_nodes[erased_nodes_count++] = pos;
                int c1 = backtrack(pos + 1, 0, depth - 1);
                int sol_1[MAX_L];
                memcpy(sol_1, erased_nodes, sizeof(sol_1));
                int sol_1_count = erased_nodes_count;

                memcpy(erased_nodes, orig_erased_nodes, sizeof(erased_nodes));
                erased_nodes_count = orig_erased_nodes_count;
                erased_nodes[erased_nodes_count++] = end;
                int c2 = backtrack(pos, i + 1, depth - 1);

                if(c1 > c2){
                    c2 = c1;
                    memcpy(erased_nodes, sol_1, sizeof(erased_nodes));
                    erased_nodes_count = sol_1_count;
                }
                if(c2 >= 0)c2 += acc;
                return c2;
            }
        }
        if(! is_pos_erased)++acc;
        ++pos;
        epos = 0;
        continue;
    }
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

    memset(erased_nodes, 0, sizeof(erased_nodes));
    erased_nodes_count = 0;

    backtrack(0, 0, l);

    int res = n;
    for(int i = 0; i < erased_nodes_count; ++i){
        result[erased_nodes[i]] = true;
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
