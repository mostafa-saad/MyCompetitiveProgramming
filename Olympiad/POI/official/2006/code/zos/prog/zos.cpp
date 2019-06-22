/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ZOS (Zosia)                                    *
 *   Plik:                zos.cpp                                        *
 *   Autor:               Krzysztof Dulêba                               *
 *   Opis:                Rozwiazanie wzorcowe.                          *
 *                                                                       *
 * Cel: znalezc minimalne pokrycie wierzcholkowe w grafie,               *
 * z gornym ograniczeniem na rozmiar tego pokrycia wynoszacym 10.        *
 *                                                                       *
 * Rozwiazanie: nalezy wziac wszystkie wierzcholki duzych stopni,        *
 * a na reszcie puscic backtracking.                                     *
 *                                                                       *
 * Dane: graf o n <= 1000000 wierzcholkach i m <= 4000000 krawedziach    *
 * oraz k, liczba wierzcholkow ktore maja byc poza pokryciem.            *
 *                                                                       *
 * Dla wygody przyjmijmy l := n - k, l oznacza wiec maksymalny           *
 * dopuszczalny rozmiar minimalnego pokrycia wierzcholkowego.            *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#define GRAPH_SIZE 1000000
#define MAX_L 11
#define REDUCED_GRAPH_SIZE (MAX_L * MAX_L * 2 + 1)

using namespace std;

vector<int> graph[GRAPH_SIZE];

/**
 * Ktore wierzcholki sa w pokryciu
 */
bool result[GRAPH_SIZE];

int n, k, m, l;
int curr_n;


/**
 * W pierwszym kroku bierzemy do pokrycia wierzcholki o duzym stopniu
 * i usuwamy ich krawedzie. Po tej operacji juz tylko niewiele pozostalych 
 * wierzcholkow moze miec stopien dodatni.
 *
 * Ich indeksy trzymamy w tablicy avail_nodes,
 * id2pos pozwala z numeru wierzcholka uzyskac indeks w tablicy avail_nodes.
 * erased_nodes pamieta, ktore elementy avail_nodes usunelismy z grafu,
 * a wzielismy do pokrycia.
 */
bool erased_nodes[REDUCED_GRAPH_SIZE];
int avail_nodes[REDUCED_GRAPH_SIZE];
int id2pos[GRAPH_SIZE];

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
    if(depth < 0)return -1;
    if(pos >= curr_n)return 0;

    int real_pos = avail_nodes[pos];
    if(! erased_nodes[pos]){
        for(int i = epos; i < (int)graph[real_pos].size(); ++i){
            int end = graph[real_pos][i];
            if(erased_nodes[id2pos[end]] == true)continue;

            /**
             * Mamy niezalatwiona krawedz.
             *
             * Bierzemy pierwszy koniec, zapamietujemy rozwiazanie.
             * Bierzemy drugi, porownujemy rozwiazanie z pierwszym,
             * zwracamy lepsze.
             */
            bool orig_erased_nodes[REDUCED_GRAPH_SIZE];
            memcpy(orig_erased_nodes, erased_nodes, sizeof(orig_erased_nodes));
            
            erased_nodes[pos] = true;
            int c1 = backtrack(pos + 1, 0, depth - 1);
            bool sol_1[REDUCED_GRAPH_SIZE];
            memcpy(sol_1, erased_nodes, sizeof(sol_1));

            memcpy(erased_nodes, orig_erased_nodes, sizeof(erased_nodes));
            erased_nodes[id2pos[end]] = true;
            int c2 = backtrack(pos, i + 1, depth - 1);

            if(c1 > c2){
                c2 = c1;
                memcpy(erased_nodes, sol_1, sizeof(erased_nodes));
            }
            return c2;
        }
    }
    int res = backtrack(pos + 1, 0, depth);
    if(res >= 0 && ! erased_nodes[pos])++res;
    return res;
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
    curr_n = 0;
    
    /**
     * Bierzemy do pokrycia wierzcholki o duzym stopniu. Jesli mozemy
     * wziac co najwyzej l wierzcholkow, a jakis wierzcholek ma stopien > l,
     * to musimy go wybrac.
     */
    int erased = 0;
    for(int i = 0; i < n; ++i){
        if((int)graph[i].size() > l){
            result[i] = true;
            ++erased;
        }
    }

    /**
     * Usuwamy krawedzie o koncach w pokryciu, a nastepnie
     * wierzcholki o dodatnim stopniu zaznaczamy jako dostepne
     * (innych nie ma sensu brac do pokrycia).
     *
     * Jesli okazalo sie, ze dostepnych wierzcholkow jest ponad l * l * 2,
     * to nieusunietych krawdzi jest ponad l * l (bo kazdy dostepny
     * wierzcholek ma stopien dodatni), a wiec biorac do pokrycia l
     * wierzcholkow stopnia <= l nie pokryjemy wszystkiego.
     */
    for(int i = 0; i < n; ++i){
        if(result[i] == true)continue;
        for(int j = 0; j < (int)graph[i].size(); ++j){
            if(result[graph[i][j]] == true){
                if(j + 1 < (int)graph[i].size()){
                    swap(graph[i][j], graph[i].back());
                }
                graph[i].pop_back();
                --j;
            }
        }
        if(graph[i].size() > 0){
            avail_nodes[curr_n] = i;
            id2pos[i] = curr_n;
            ++curr_n;
            if(curr_n > l * l * 2){
                printf("NIE\n");
                exit(0);
            }
        }
    }

    l -= erased;

    /**
     * Zostal nam graf, w ktorym jest co najwyzej l * l * 2 wierzcholkow
     * i krawedzi. Na nim odpalamy backtracking szukajac pokrycia
     * wierzcholkowego.
     */

    memset(erased_nodes, 0, sizeof(erased_nodes));
    
    backtrack(0, 0, l);

    for(int i = 0; i < curr_n; ++i){
        if(erased_nodes[i] == true){
            result[avail_nodes[i]] = true;
        }
    }

    int res = n;
    for(int i = 0; i < n; ++i){
        if(result[i])--res;
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
