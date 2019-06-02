/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ZOS (Zosia)                                    *
 *   Plik:                zosb1.cpp                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie niepoprawne.                       *
 *                                                                       *
 *                        Rozwiazanie: jezeli jest > 100 krawedzi, to    *
 *                        uruchamiamy rozwiazanie niepoprawne, biorace   *
 *                        wierzcholki od najwiekszych stopni,            *
 *                        a w przeciwnym przypadku lepsze rozwiazanie    *
 *                        brutalne.                                      *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

#define GRAPH_SIZE 1000000
#define MAX_L 11


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

void doit(){
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
}




int main(){
    scanf("%d %d %d", &n, &k, &m);
    int ile = 0;

    memset(result, 0, sizeof(result));
    
    /**
     *  wczytujemy graf
     */
    for(int i = 0; i < m; ++i){
        int x, y;
        scanf("%d %d", &x, &y);
        ile++;
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
    
    if (ile <= 100)
    {
      doit();
    } else
    {
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
    return 0;
}
