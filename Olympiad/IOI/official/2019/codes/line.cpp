#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

#define pb push_back
#define mp make_pair
#define fs first
#define sc second

int n;
vector <pair <int, int> > input;
vector <pair <int, int> > answer;
bool last_volatile = false;

void continue_answer(pair <int, int> point) {
    if (answer.empty()) {
        answer.pb(point);

        return;
    }

    if (answer.size() >= 2u) {
        bool worked = false;
        int last = (int) answer.size() - 1;
        int prelast = (int) answer.size() - 2;
        if (answer[prelast].fs == answer[last].fs) {
            if ((answer[last].sc - answer[prelast].sc) * 1ll * (point.sc - answer[last].sc) > 0) {
                answer[last].sc = point.sc;
                worked = true;
            }
        } else {
            if ((answer[last].fs - answer[prelast].fs) * 1ll * (point.fs - answer[last].fs) > 0) {
                answer[last].fs = point.fs;
                worked = true;
            }
        }

        if (!worked && last_volatile) {
            int preprelast = (int) answer.size() - 3;
            answer[prelast].fs = answer[preprelast].fs;
            answer[prelast].sc = answer[last].sc;
            if (answer[prelast].fs == answer[last].fs) {
                if ((answer[last].sc - answer[prelast].sc) * 1ll * (point.sc - answer[last].sc) > 0) {
                    answer[last].sc = point.sc;
                }
            } else {
                if ((answer[last].fs - answer[prelast].fs) * 1ll * (point.fs - answer[last].fs) > 0) {
                    answer[last].fs = point.fs;
                }
            }
        }
    }

    last_volatile = (point.fs != answer.back().fs && point.sc != answer.back().sc);

    if (point.fs != answer.back().fs) {
        answer.pb(mp(point.fs, answer.back().sc));
    }
    if (point.sc != answer.back().sc) {
        answer.pb(point);
    }
}

void add_spiral(vector <pair <pair <int, int>, pair <int, int> > > spiral) {
    for (int i = 0; i < (int) spiral.size(); i++) {
        int lft = spiral[i].fs.fs;
        int up = spiral[i].fs.sc;
        int rgt = spiral[i].sc.fs;
        int down = spiral[i].sc.sc;

        pair <int, int> ldc = mp(input[lft].fs, input[down].sc);
        pair <int, int> luc = mp(input[lft].fs, input[up].sc);
        pair <int, int> rdc = mp(input[rgt].fs, input[down].sc);
        pair <int, int> ruc = mp(input[rgt].fs, input[up].sc);

        if (i == 0) {
            continue_answer(ldc);
            continue_answer(luc);
            continue_answer(ruc);
            continue_answer(rdc);
            continue_answer(ldc);
        } else {
            answer.back().fs = input[lft].fs;
            if (input[lft].sc >= answer.back().sc) {
                continue_answer(luc);
                continue_answer(ruc);
                continue_answer(rdc);
                continue_answer(ldc);
            } else {
                continue_answer(ldc);
                continue_answer(rdc);
                continue_answer(ruc);
                continue_answer(luc);
            }
        }
    }
}

void add_chain(vector <pair <int, int> > chain, bool order, bool flip, bool interleave) {
    if (chain.empty())
        return;
    int len = (int) chain.size();
    if (flip) {
        for (int i = 0; i < len; i++) {
            chain[i].fs *= -1;
        }
    }
    if (order) {
        for (int i = 0; i < len; i++) {
            chain[i].sc *= -1;
        }
    }
    sort(chain.begin(), chain.end());
    if (flip) {
        for (int i = 0; i < len; i++) {
            chain[i].fs *= -1;
        }
    }
    if (order) {
        for (int i = 0; i < len; i++) {
            chain[i].sc *= -1;
        }
    }

    continue_answer(chain[0]);
    for (int i = 1; i < len; i++) {
        if (i % 2 xor interleave) {
            continue_answer(mp(chain[i].fs, chain[i - 1].sc));
        } else {
            continue_answer(mp(chain[i - 1].fs, chain[i].sc));
        }
    }
    if (len > 1) {
        continue_answer(chain.back());
    }
}

void finalize() {
    cerr << n << ' ' << answer.size() - 1 << ' ' << answer.size() - 1 - n << '\n';
    cout << answer.size()-1 << '\n';
    for (int i = 1; i < (int) answer.size(); i++) {
        cout << answer[i].fs << ' ' << answer[i].sc << '\n';
    }
}

int main () {
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        input.pb(mp(x, y));
    }

    vector <pair <int, int> > chain1, chain2;
    vector <pair <pair <int, int>, pair <int, int> > > spiral;
    set <pair <int, int> > xs;
    set <pair <int, int> > ys;
    vector <bool> used(n, false);

    for (int i = 0; i < n; i++) {
        xs.insert(mp(input[i].fs, i));
        ys.insert(mp(input[i].sc, i));
    }

    while (true) {
        int lft = -1;
        while (!xs.empty() && used[xs.begin()->sc]) {
            xs.erase(xs.begin());
        }
        if (!xs.empty()) {
            lft = xs.begin()->sc;
        }

        int rgt = -1;
        while (!xs.empty() && used[xs.rbegin()->sc]) {
            xs.erase(*xs.rbegin());
        }
        if (!xs.empty()) {
            rgt = xs.rbegin()->sc;
        }

        int down = -1;
        while (!ys.empty() && used[ys.begin()->sc]) {
            ys.erase(ys.begin());
        }
        if (!ys.empty()) {
            down = ys.begin()->sc;
        }

        int up = -1;
        while (!ys.empty() && used[ys.rbegin()->sc]) {
            ys.erase(*ys.rbegin());
        }
        if (!ys.empty()) {
            up = ys.rbegin()->sc;
        }

        if (lft == -1 || rgt == -1 || down == -1 || up == -1) {
            break;
        }

        if (lft == down) {
            chain1.pb(input[lft]);
            used[lft] = true;
            continue;
        }
        if (lft == up) {
            chain2.pb(input[lft]);
            used[lft] = true;
            continue;
        }
        if (rgt == down) {
            chain2.pb(input[rgt]);
            used[rgt] = true;
            continue;
        }
        if (rgt == up) {
            chain1.pb(input[rgt]);
            used[rgt] = true;
            continue;
        }
        spiral.pb(mp(mp(lft, up), mp(rgt, down)));
        used[lft] = true;
        used[rgt] = true;
        used[down] = true;
        used[up] = true;
    }

    reverse(spiral.begin(), spiral.end());
    vector <pair <int, int> > best_answer;
    for (int flip1 = 0; flip1 < 8; flip1++) {
        for (int flip2 = 0; flip2 < 8; flip2++) {
            vector <int> parts = {0, 1, 2};
            do {
                answer.clear();
                last_volatile = false;
                continue_answer(mp(0, 0));
                for (int i = 0; i < (int) parts.size(); i++) {
                    if (parts[i] == 0) {
                        add_spiral(spiral);
                    } else if (parts[i] == 1) {
                        add_chain(chain1, flip1 >> 2, (flip1 >> 1) & 1, flip1 & 1);
                    } else {
                        add_chain(chain2, flip2 >> 2, (flip2 >> 1) & 1, flip2 & 1);
                    }
                }
                if (best_answer.empty() || answer.size() < best_answer.size()) {
                    best_answer = answer;
                }
            } while (next_permutation(parts.begin(), parts.end()));
        }
    }

    answer = best_answer;

    finalize();

    return 0;
}
