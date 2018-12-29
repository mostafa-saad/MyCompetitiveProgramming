/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Superkomputer                                 *
 *   Autor:                Adam Polak                                    *
 *   Zlozonosc czasowa:    O(qn)                                         *
 *   Zlozonosc pamieciowa: O(q+n)                                        *
 *   Opis:                 Rozwiazanie bledne                            *
 *                         Wykonuje zadania w losowej (poprawnej,        *
 *                         ale niekoniecznie optymalnej) kolejnosci.     *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

const int N = 1000000;
const int Q = 1000000;

int n, queries, _k[Q];
vector<int> sons[N];

int compute(int k) {
    vector<int> todo;
    todo.push_back(0);
    int result = 0;
    while(!todo.empty()) {
        vector<int> this_turn;
        for (int i = 0; i < k && !todo.empty(); ++i) {
            swap(todo[todo.size()-1], todo[rand() % todo.size()]);
            this_turn.push_back(todo.back());
            todo.resize(todo.size() - 1);
        }
        for (unsigned i = 0; i < this_turn.size(); ++i) {
            int u = this_turn[i];
            for (unsigned j = 0; j < sons[u].size(); ++j)
                todo.push_back(sons[u][j]);
        }
        result++;
    }
    return result;
}

int main() {
    srand(17);  // szczesliwa liczba ;)

    int ret;
    ret = scanf("%d%d", &n, &queries);
    for (int i = 0; i < queries; ++i)
        ret = scanf("%d", &_k[i]);
    for (int i = 1; i < n; i++) {
        int a;
        ret = scanf("%d", &a);
        sons[a - 1].push_back(i);
    }
    for (int qi = 0; qi < queries; ++qi) {
        int result = compute(_k[qi]);
        printf(qi > 0 ? " %d" : "%d", result);
    }
    printf("\n");
    if(ret<0) return 0;
    return 0;
}

