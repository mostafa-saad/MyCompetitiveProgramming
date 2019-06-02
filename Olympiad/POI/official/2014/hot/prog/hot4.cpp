/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Hotele                                        *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(n log n)                                    *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie lepsze niz wzorcowe               *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>
#ifdef DEBUG
    #define DEB printf
#else
    #define DEB(...)
#endif
#define REP(x, n) for(int x = 0; x < (n); x++)
using namespace std;

typedef long long LL;

const int N = 1000 * 1000;

LL result = 0;
vector<int> neighbors[N];
vector<pair<int, LL>> queries[N];

bool children_paths_comp(vector<int>* a, vector<int>* b) {
    return a->size() > b->size();
}

template<class C>
C& get(vector<C> &vec, size_t idx) {
    return vec[vec.size() - 1 - idx];
}

// Zwraca wskaznik na wektor glebokosci
// Aktualizuje wynik o rownoodlegle trojki o srodku w v
// Zapisuje zapytania potrzebne do sfinalizowania wyniku
// Uwaga! Liczby wierzcholkow na podanej glebokosci sa podane
// w odwrotnej kolejnosci. Dlatego trzeba uzywac funkcji get.

vector<int>* dfs(int v, int parent) {
    vector<vector<int>*> children_paths;
    for(int child : neighbors[v]) if(child != parent) {
        auto child_path = dfs(child, v);
        children_paths.push_back(child_path);
    }

    if(children_paths.size() == 0) { // Jestesmy w lisciu
        return new vector<int>(1, 1);
    }

    sort(children_paths.begin(), children_paths.end(), children_paths_comp);
    vector<int>* paths = children_paths[0]; // Jeden z najdluzszych vectorów
    paths->push_back(1); // Dorzucamy informacje o korzeniu
    
    if(children_paths.size() == 1) { // Nic wiecej nie trzeba robic
        return paths;
    }

    vector<LL> paths_double; // Liczba par sciezek odchodzacych od v o danej dlugosci
    paths_double.resize(children_paths[1]->size() + 1, 0); // Najdluzsza z nich nie moze
    // byc dluzsza niz druga najdluzsza sciezka

    for(size_t i = 1; i < children_paths.size(); i++) {
        vector<int> *child_paths = children_paths[i];
        for(size_t depth = 1; depth <= child_paths->size(); depth++) {
            // Uaktualnij wynik
            int child_num = get(*child_paths, depth - 1); // liczba wierzcholkow w poddrzewie child na glebokosci depth
            int& root_num = get(*paths, depth); // liczba wiercholkow w naszym drzewie na glebokosci depth
            LL& root_double = get(paths_double, depth); // liczba par sciezek w naszym drzewie na glebokosci depth

            result += (LL)child_num * root_double;
            root_double += (LL)child_num * (LL)root_num;
            root_num += child_num;
        }
    }

    for(size_t depth = 1; depth < paths_double.size(); depth++) {
        queries[v].push_back({depth, get(paths_double, depth)}); // pozniej przemnozymy
        // liczbe par sciezek o dlugosci depth przez liczbe wierzcholkow odleglych od w o depth.
        result -= get(paths_double, depth) * (LL)get(*paths, depth);
        // Ale od tego trzeba jeszcze odjac trojki, ktore naleza do naszego poddrzewa (juz policzone).
    }
    return paths;
}

bool blocked[N]; // Uzywamy do krojenia na centroidy
int subtree_size[N];

// Oblicza wielkosci poddrzew
void size_dfs(int v, int parent) {
    int& size = subtree_size[v];
    size = 1;
    for(int w : neighbors[v]) if(w != parent && !blocked[w]) {
        size_dfs(w, v);
        size += subtree_size[w];
    }
}

// Zwraca centroid drzewa
int find_centroid(int v) {
    size_dfs(v, -1);
    int n = subtree_size[v];
    bool change = false;
    int parent = -1;
    do {
        change = false;
        for(int w : neighbors[v]) if(w != parent && !blocked[w]) {
            if(2 * subtree_size[w] > n) {
                parent = v;
                v = w;
                change = true;
                break;
            }
        }
    } while(change);
    return v;
}

// Odpowiada na zapytania zadane w poddrzewach centroidu
void answer_queries(vector<vector<int>> &depths, vector<vector<pair<int, LL>>> &lqueries, int direction,
        bool include_centroid, int centroid) {
    size_t be = direction == 1 ? 0 : depths.size() - 1;
    size_t en = direction == 1 ? depths.size() : -1;

    
    vector<int> all_depths(1, include_centroid); 
    for(size_t i = be; i != en; i += direction) {
        auto current_depths = depths[i];
        auto current_queries = lqueries[i];
        for(auto p : current_queries) {
            size_t depth = p.first;
            if(depth < all_depths.size()) {
                result += (LL)all_depths[depth] * (LL)p.second;
            }
        }
        
        all_depths.resize(max(all_depths.size(), current_depths.size()), 0);
        for(size_t depth = 0; depth < current_depths.size(); depth++) {
            all_depths[depth] += current_depths[depth];
        }
    }

    // Odpowiada jeszcze na pytania zadane w centroidzie
    if(include_centroid) {
        for(auto p : queries[centroid]) {
            size_t depth = p.first;
            if(depth < all_depths.size()) {
                result += (LL)all_depths[depth] * (LL)p.second;
            }
        }
    }
}

void depth_dfs(int v, int parent, size_t depth, vector<int>& depths) {
    if(depth == depths.size()) {
        depths.push_back(1);
    } else {
        assert(depth < depths.size());
        depths[depth]++;
    }
    for(int w : neighbors[v]) if(w != parent && !blocked[w]) {
        depth_dfs(w, v, depth + 1, depths);
    }
}

// zwraca liczbe wierzcholkow na danej glebokosci w poddrzewie
vector<int> get_depths(int v) {
    vector<int> depths(1, 0);
    depth_dfs(v, -1, 1, depths);
    return depths;
}

void query_dfs(int v, int parent, size_t depth, vector<pair<int, LL>>& lqueries) {
    for(auto q : queries[v]) {
        int new_range = q.first - depth;
        if(new_range >= 0) {
            lqueries.push_back({new_range, q.second});
        }
    }

    for(int w : neighbors[v]) if(w != parent && !blocked[w]) {
        query_dfs(w, v, depth + 1, lqueries);
    }
}

vector<pair<int, LL>> get_queries(int v) {
    vector<pair<int, LL>> local_queries;
    query_dfs(v, -1, 1, local_queries);
    return local_queries;
}

// Funkcja oblicza wynik, usuwajac centroid i wywolujac sie rekurencyjnie
// w kazdym z oddzielonych poddrzew.
void centroids(int v) {
    int centroid = find_centroid(v); // od teraz zapominamy o v
    blocked[centroid] = true; // Rozbijamy drzewo
    for(int w : neighbors[centroid]) if(!blocked[w]) {
        centroids(w); // Rekurencyjnie liczymy dla dzieci
    }
    
    vector<vector<int>> depths;
    vector<vector<pair<int, LL>>> local_queries;

    for(int w : neighbors[centroid]) if(!blocked[w]) {
        depths.push_back(get_depths(w));
        local_queries.push_back(get_queries(w));
    }

    // Odpowiadamy na pytania zadane w poddrzewach
    // Za pierwszym razem odpowiadamy takze na pytania zadane w i dotyczace
    // centroidu.
    answer_queries(depths, local_queries, 1, true, centroid);
    answer_queries(depths, local_queries, -1, false, centroid);

    blocked[centroid] = false; // Sklejamy drzewo
}

int main() {
    int n;
    scanf("%d", &n);
    REP(i, n - 1) {
        int a, b;
        scanf("%d%d", &a, &b);
        a--, b--;
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }
    dfs(0, -1);
    centroids(0);
    printf("%lld\n", result);
    return 0;
}
