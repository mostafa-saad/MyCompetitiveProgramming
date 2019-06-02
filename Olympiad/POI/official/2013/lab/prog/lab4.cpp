/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Labirynt                                      *
 *   Autor:                Dawid Dabrowski                               *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MX = 100005;

int n;
string s;

#define val(c) ((c) == 'L' ? 1 : -1)

int min_level_a[MX], min_level_b[MX];
int min_level_rot[MX];
int sum[MX];
void findrot() {
    min_level_b[n-1] = sum[n-1] = val(s[n-1]);
    for (int i = n-2; i >= 0; --i) {
        min_level_b[i] = (val(s[i]) == -1) ? (-1 + min(0, min_level_b[i+1])) : (1 + min_level_b[i+1]);
        sum[i] = val(s[i]) + sum[i+1];
    }
    int sum_a = 0;
    for (int i = 0; i < n; ++i) {
        sum_a += val(s[i]);
        min_level_a[i] = sum_a;
        if (i > 0) min_level_a[i] = min(min_level_a[i], min_level_a[i-1]);
    }
    // cout << s << endl;
    for (int i = 0; i < n; ++i) {
        int mlevel = min_level_b[i];
        if (i > 0) mlevel = min(mlevel, sum[i] + min_level_a[i-1]);
        min_level_rot[i] = mlevel;
        // cout << min_level_rot[i] << endl;
    }
    for (int i = 0; i < n; ++i) {
        if (min_level_rot[i] >= 0 && min_level_rot[(i+1) % n] == 0 && s[i] == 'L') {
            s = s.substr(i) + s.substr(0, i);
            break;
        }
    }
}

int sum_a[MX];
string part[4];
void partition() {
    sum_a[0] = val(s[0]);
    for (int i = 1; i < n; ++i) sum_a[i] = sum_a[i-1] + val(s[i]);
    int beg = 0;
    for (int d = 1; d <= 4; ++d) {
        for (int i = n-1; i >= beg; --i) if (sum_a[i] == d) {
                if (i-beg > 0) part[d-1] = s.substr(beg+1, i-beg);
                beg = i+1;
                break;
            }
    }
}

bool check() {
    int sum = 0;
    for (int i = 0; i < n; ++i) sum += val(s[i]);
    return sum == 4;
}

vector<int> lengths[4];
pair<int, int> results[4][MX];
int ind;

pair<int, int> rec(int d) {
    int beg = ind;
    pair<int, int> res = make_pair(0, 0);
    while (ind < (int)part[d].size() && part[d][ind] == 'L') {
        ++ind;
        pair<int, int> to_add;
        if (part[d][ind] == 'P') {
            to_add = make_pair(0, 1);
            ++ind;
        } else to_add = rec(d);
        swap(to_add.first, to_add.second);
        to_add.second += 2;
        res.first += to_add.first;
        res.second += to_add.second;
    }
    results[d][beg] = res;
    ++ind;
    return res;
}

void rec2(int d) {
    int add_ind = -1;
    while (ind < (int)part[d].size() && part[d][ind] == 'L') {
        ++ind;
        if (part[d][ind] == 'P') {
            lengths[d].push_back(1);
            lengths[d].push_back(1);
            lengths[d].push_back(1);
            ++ind;
        } else {
            pair<int, int> resin = results[d][ind];
            swap(resin.first, resin.second);
            resin.second += 2;
            lengths[d].push_back(resin.second - 1);
            rec2(d);
            lengths[d].push_back(resin.second - 1);
        }
        if (add_ind != -1) {
            lengths[d][add_ind] += lengths[d][add_ind + 1];
            lengths[d][add_ind + 1] = 0;
        }
        add_ind = (int)lengths[d].size() - 1;
    }
    ++ind;
}

vector<int> resl;
int x[MX], y[MX];

int main() {
    cin >> s;
    n = (int)s.size();
    if (!check()) cout << "NIE" << endl;
    else {
        findrot();
        partition();
        vector<int> tmp;
        for (int i = 0; i < 4; ++i) {
            // cout << part[i] << endl;
            if (part[i].empty()) {
                lengths[i].push_back(1);
                results[i][0] = make_pair(0, 1);
            } else {
                ind = 0;
                rec(i);
                ind = 0;
                rec2(i);
                tmp.clear();
                for (int j = 0; j < (int)lengths[i].size(); ++j)
                    if (lengths[i][j]) tmp.push_back(lengths[i][j]);
                lengths[i] = tmp;
                //cout << "------------" << endl;
                //for (int j = 0; j < lengths[i].size(); ++j)
                //  if (lengths[i][j]) cout << lengths[i][j] << endl;
            }
        }
        //cout << "------------" << endl;
        int sep13 = results[1][0].first + results[3][0].first;
        int sep02 = results[0][0].first + results[2][0].first;
        //cout << "sep13 = " << sep13 << endl;
        //cout << "sep02 = " << sep02 << endl;
        lengths[0][0] += sep13;
        lengths[0].back() += sep13;
        lengths[2][0] += sep13;
        lengths[2].back() += sep13;
        lengths[1][0] += sep02;
        lengths[1].back() += sep02;
        lengths[3][0] += sep02;
        lengths[3].back() += sep02;
        results[0][0].second += 2*sep13;
        results[2][0].second += 2*sep13;
        results[1][0].second += 2*sep02;
        results[3][0].second += 2*sep02;
        if (results[0][0].second < results[2][0].second) {
            lengths[0][0] += results[2][0].second - results[0][0].second;
            results[0][0].second = results[2][0].second;
        }
        if (results[2][0].second < results[0][0].second) {
            lengths[2][0] += results[0][0].second - results[2][0].second;
            results[2][0].second = results[0][0].second;
        }
        if (results[1][0].second < results[3][0].second) {
            lengths[1][0] += results[3][0].second - results[1][0].second;
            results[1][0].second = results[3][0].second;
        }
        if (results[3][0].second < results[1][0].second) {
            lengths[3][0] += results[1][0].second - results[3][0].second;
            results[3][0].second = results[1][0].second;
        }
        lengths[2][0] += results[3][0].first - results[1][0].first;
        lengths[3][0] += results[0][0].first - results[2][0].first;
        for (int i = 0; i < 4; ++i) for (int j = 0; j < (int)lengths[i].size(); ++j)
                resl.push_back(lengths[i][j]);
        // cout << s << endl;
        //for (int i = 0; i < (int)resl.size(); ++i)
        //  cout << resl[i] << endl;
        x[0] = 0;
        y[0] = 0;
        x[1] = 0;
        y[1] = resl[0];
        for (int i = 1; i < n; ++i) {
            if (s[i] == 'L') {
                if (x[i] == x[i-1]) {
                    y[i+1] = y[i];
                    if (y[i] > y[i-1]) x[i+1] = x[i] - resl[i];
                    else x[i+1] = x[i] + resl[i];
                } else {
                    x[i+1] = x[i];
                    if (x[i] > x[i-1]) y[i+1] = y[i] + resl[i];
                    else y[i+1] = y[i] - resl[i];
                }
            } else {
                if (x[i] == x[i-1]) {
                    y[i+1] = y[i];
                    if (y[i] > y[i-1]) x[i+1] = x[i] + resl[i];
                    else x[i+1] = x[i] - resl[i];
                } else {
                    x[i+1] = x[i];
                    if (x[i] > x[i-1]) y[i+1] = y[i] - resl[i];
                    else y[i+1] = y[i] + resl[i];
                }
            }
        }
        for (int i = 0; i < n; ++i) cout << x[i] << " " << y[i] << endl;
    }
    return 0;
}
