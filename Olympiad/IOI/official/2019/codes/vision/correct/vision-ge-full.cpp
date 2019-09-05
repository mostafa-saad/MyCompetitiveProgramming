#include "vision.h"

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

int proxy_and(vector<int> nrs) {
    if (nrs.size() == 1u) {
        return nrs[0];
    } else {
        return add_and(nrs);
    }
}

int proxy_or(vector<int> nrs) {
    if (nrs.size() == 1u) {
        return nrs[0];
    } else {
        return add_or(nrs);
    }
}

int proxy_xor(vector<int> nrs) {
    if (nrs.size() == 1u) {
        return nrs[0];
    } else {
        return add_xor(nrs);
    }
}

int construct_xplusy(int n, int m, int k, const vector<vector<int>>& idx) {
    vector <vector <int> > diags(n + m - 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            diags[i + j].pb(idx[i][j]);
        }

    vector <int> neurons;
    for (int i = 0; i < n + m - 1; i++) {
        neurons.pb(proxy_or(diags[i]));
    }
    vector <int> prefs;
    prefs.pb(neurons[0]);
    for (int i = 1; i < n + m - 1; i++) {
        prefs.pb(proxy_or({prefs.back(), neurons[i]}));
    }
    vector <int> pairs;
    for (int i = 0; i + k < n + m - 1; i++) {
        pairs.pb(proxy_and({prefs[i], neurons[i + k]}));
    }

    return proxy_or(pairs);
}

void construct_network(int n, int m, int k) {
    vector <vector<int>> idx(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            idx[i][j] = i * m + j;
        }
    }

    int xplusy_k = construct_xplusy(n, m, k, idx);
    int xplusy_kp1 = -1;
    if (k < n + m - 2) {
        xplusy_kp1 = construct_xplusy(n, m, k + 1, idx);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m / 2; j++) {
            swap(idx[i][j], idx[i][m - 1 - j]);
        }
    }
    int xminusy_k = construct_xplusy(n, m, k, idx);
    int xminusy_kp1 = -1;
    if (k < n + m - 2) {
        xminusy_kp1 = construct_xplusy(n, m, k + 1, idx);        
    }

    if (k < n + m - 2) {
        int k_or = proxy_or({xplusy_k, xminusy_k});
        int kp1_or = proxy_or({xplusy_kp1, xminusy_kp1});

        proxy_xor({k_or, kp1_or}); 
    } else {
        proxy_or({xplusy_k, xminusy_k});
    }
}
