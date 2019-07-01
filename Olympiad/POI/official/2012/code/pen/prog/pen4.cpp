/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Pensje                                           *
 *   Autor:             Jakub Pachocki                                   *
 *   Zlozonosc czasowa: O(n log n)                                       *
 *   Opis:              Rozwiazanie weryfikujace                         *
 *                                                                       *
 *************************************************************************/


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = (int) 1e6;

int n;

vector<int> sons[N + 1];
int parent[N + 1];
int salary[N + 1];
bool salary_taken[N + 1];

struct Subtree {
    int path_bottom;
    int size;

    int upper_limit;

    bool operator < (const Subtree& other) const {
        return upper_limit < other.upper_limit;
    }
};

int find_path_bottom(int x) {
    if (sons[x].size() != 1) {
        return x;
    } else {
        return find_path_bottom(sons[x].front());
    }
}

int find_subtree_size(int x) {
    int result = 1;
    for (vector<int>::iterator it = sons[x].begin(); it != sons[x].end(); ++it) {
        result += find_subtree_size(*it);
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    salary[0] = n + 1;
    for (int i = 1; i <= n; ++i) {
        cin >> parent[i] >> salary[i];
        salary_taken[salary[i]] = true;
        if (parent[i] == i) {
            parent[i] = 0;
        }
        sons[parent[i]].push_back(i);
    }
    vector<Subtree> subtrees;
    for (int i = 1; i <= n; ++i) {
        if (salary[i] == 0 && salary[parent[i]] != 0) {
            Subtree subtree;
            subtree.path_bottom = find_path_bottom(i);
            subtree.size = find_subtree_size(i);
            subtree.upper_limit = salary[parent[i]];
            subtrees.push_back(subtree);
        }
    }
    sort(subtrees.begin(), subtrees.end());
    vector<int> not_taken;
    int sum_waiting = 0;
    int last = 0;
    for (vector<Subtree>::iterator it = subtrees.begin(); it != subtrees.end(); ++it) {
        int prev_last = last;
        while (last < it->upper_limit - 1) {
            ++last;
            if (!salary_taken[last]) {
                not_taken.push_back(last);
            }
        }

        vector<int> on_path;
        int c = it->path_bottom;
        while (salary[c] == 0) {
            on_path.push_back(c);
            c = parent[c];
        }

        if (sum_waiting == 0 && it->size == (int) not_taken.size()) {
            while (!on_path.empty()) {
                salary[on_path.back()] = not_taken.back();
                on_path.pop_back();
                not_taken.pop_back();
            }
            not_taken.clear();
        } else {
            sum_waiting += it->size;
            if (sum_waiting == (int) not_taken.size()) {
                while (!on_path.empty() && not_taken.back() > prev_last) {
                    salary[on_path.back()] = not_taken.back();
                    not_taken.pop_back();
                    on_path.pop_back();
                }
                not_taken.clear();
                sum_waiting = 0;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << salary[i] << "\n";
    }
}
