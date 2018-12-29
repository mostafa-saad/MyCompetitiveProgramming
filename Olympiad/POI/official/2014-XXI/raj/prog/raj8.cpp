/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Rajd                                          *
 *   Autor:                Bartosz Tarnawski                             *
 *   Zlozonosc czasowa:    O(m log* n + n)                               *
 *   Uwaga:                Na podstawie rozwiazania Marka Sokolowskiego  *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#define REP(x, n) for (int x = 0; x < (n); x++)

using namespace std;

const int N = 500005;

// ------------------------------- FIND & UNION ---------------------------- //

// Liczby 0, ..., n-1 sa podzielone na rozlaczne grupy. Liczby moga tez nie nalezec
// do zadnej grupy. 

// right[x] oznacza najwiekszy numer w grupie "x" lub -1, jesli "x" nie nalezy
// do zadnej grupy
int p[N], w[N], right[N];

// Na poczatku nie ma zadnej grupy.
void init_fu(int n) {
    REP(i, n) {
        p[i] = i;
        right[i] = -1;
        w[i] = 0;
    }
}

// Reprezentant grupy "x" lub "x", jesli "x" nie nalezy do zadnej grupy.
int find_fu(int x) {
    if (p[x] == x) return x;
    return p[x] = find_fu(p[x]);
}

// Jesli "x" nie nalezy do zadnej grupy, tworzy jednoelementowa grupe z "x",
// w przeciwnym razie nic nie robi.
void mark_fu(int x) {
    if(p[x] == x && right[x] == -1) {
        right[x] = x;
    }
}

// Laczy grupy "x" i "y", w razie potrzeby napierw tworzy dla nich
// jednoelementowe grupy.
void union_fu(int x, int y) {
    mark_fu(x), mark_fu(y);
    x = find_fu(x), y = find_fu(y);
    if (x != y) {
        if (w[x] > w[y]) {
            p[y] = x;
        } else if (w[x] < w[y]) {
            p[x] = y;
        } else {
            w[x]++;
            p[y] = x;
        }
    }
    right[find_fu(x)] = max(right[x], right[y]);
}

// zwraca najwieksza liczbe w grupie z "x"
int rightmost_fu(int x) {
    return right[find_fu(x)];
}

// ------------------------------- KONIEC F & U ---------------------------- //

vector<int> g[N];
vector<pair<int, int>> bad_int[N];
int order[N], oldnum[N];
int len[2][N];
int n, m;
int a, b;
int best_v, best_d;

int t;

void dfs(int v) {
	order[v] = 1;
	for (int w : g[v]) if (order[w] == -1) dfs(w);
	order[v] = t--;
}


// Sortuje graf "g" topologicznie, zapisuje stare numery wierzcholkow
// w tablicy "oldnum"
void toposort() {
    t = n - 1;
	REP(i, n) order[i] = -1;
	REP(i, n) if (order[i] == -1) dfs(i);
	REP(i, n) oldnum[order[i]] = i;

	vector<int> g_tmp[n]; 
	REP(i, n) for (int w : g[i]) g_tmp[order[i]].push_back(order[w]);
    
	REP(i, n) g[i] = g_tmp[i];
}

// Liczy najdluzsze sciezki zaczynajace i konczace sie w kazdym z wierzcholkow
void count_len() {
    // zaczynajace sie
	for (int i = n - 1; i >= 0; i--) {
		for (int w : g[i]) len[0][i] = max(len[0][i], 1 + len[0][w]);
	}
    
    vector<int> rev[n];
	REP(i, n) for (int w : g[i]) rev[w].push_back(i);
    // konczace sie
	REP(i, n) {
	    for (int w : rev[i]) len[1][i] = max(len[1][i], 1 + len[1][w]);
	}
}


// Zapisuje zle przedzialy na odpowiednich poziomach "bad_int"
void add_bad_intervals() {
    REP(i, n) {
        for (int w : g[i]) bad_int[len[1][i] +  1 + len[0][w]].push_back({i + 1, w - 1});
        bad_int[len[0][i]].push_back({0, i - 1});
        bad_int[len[1][i]].push_back({i + 1, n - 1});
    }
}


// Znajduje szukana dlugosc, zapisuje ja jako "best_d", a wierzcholek, ktory
// nalezy usunuac -- jako "best_v"
void find_res() {

    add_bad_intervals();

    init_fu(n); // Struktura bedzie reprezentowac wierzcholki (0, ..., n - 1)
    for (int d = n + 1; d >= 0; d--) {
        for (auto in : bad_int[d]) {
            int l = in.first, r = in.second;
            if (l > r) continue;
            
            mark_fu(l);
            if (l - 1 >= 0 && rightmost_fu(l - 1) != -1) {
                union_fu(l - 1, l);
            }
            while (l < r) {
                union_fu(l, l + 1);
                l = rightmost_fu(l + 1);
            }
            if (l + 1 < n && rightmost_fu(l + 1) != -1) {
                union_fu(l, l + 1);
            }
        }
        if (rightmost_fu(0) == n - 1) {
            best_d = d;
            return;
        } else {
            best_v = rightmost_fu(0) + 1;
        }
    }
}

int main() {
	scanf("%d%d", &n, &m);
	REP(i, m) {
		scanf("%d%d", &a, &b);
		a--, b--;
		g[a].push_back(b);
	}
    
    // Sortujemy graf g topologicznie
    toposort();
    // Liczymy dlugosci najdluzszych sciezek o poczatku i koncu w kazdym
    // z wierzcholkow
    count_len();
    // Na tej podstawie wyznaczamy wynik
    find_res();

	printf("%d %d\n", oldnum[best_v] + 1, best_d);
	return 0;
}
