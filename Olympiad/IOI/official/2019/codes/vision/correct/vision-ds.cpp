// Dmitry _kun_ Sayutin (2019)

#include <bits/stdc++.h>
#include "vision.h"

using std::cin;
using std::cout;
using std::cerr;

using std::vector;
using std::map;
using std::array;
using std::set;
using std::string;

using std::pair;
using std::make_pair;

using std::tuple;
using std::make_tuple;
using std::get;

using std::min;
using std::abs;
using std::max;
using std::swap;

using std::unique;
using std::sort;
using std::generate;
using std::reverse;
using std::min_element;
using std::max_element;

#ifdef LOCAL
#define LASSERT(X) assert(X)
#else
#define LASSERT(X) {}
#endif

#define SZ(vec)         int((vec).size())
#define ALL(data)       data.begin(),data.end()
#define RALL(data)      data.rbegin(),data.rend()
#define TYPEMAX(type)   std::numeric_limits<type>::max()
#define TYPEMIN(type)   std::numeric_limits<type>::min()

void construct_network(int n, int m, int k) {
    vector<int> sumgates(n + m - 1, -1), sumgates2(n + m - 1, -1); // [0; (n-1)+(m-1)].

    vector<vector<int>> lst(n + m - 1), lst2(n + m -1);

    for (int i = 0; i != n; ++i)
        for (int j = 0; j != m; ++j) {
            lst[i + j].push_back(i * m + j);
            lst2[i + j].push_back(i * m + (m - 1 - j));
        }
    
    for (int sm = 0; sm < n + m - 1; ++sm) {
        sumgates[sm] = add_or(lst[sm]);
        sumgates2[sm] = add_or(lst2[sm]);
    }

    vector<int> pref(n + m - 1, -1), pref2(n + m - 1, -1);

    pref[0] = sumgates[0];
    pref2[0] = sumgates2[0];

    for (int sm = 1; sm < SZ(pref); ++sm) {
        pref[sm] = add_or({sumgates[sm], pref[sm - 1]});
        pref2[sm] = add_or({sumgates2[sm], pref2[sm - 1]});
    }

    int node_k = -1, node_kplus1 = -1;

    for (int iter = 0; iter != 2; ++iter) {
        int the_k = (iter == 0 ? k : k + 1);
        int& res_node = (iter == 0 ? node_k : node_kplus1);

        vector<int> or_lst;
        for (int s = 0; s + the_k < SZ(sumgates); ++s)
            or_lst.push_back(add_and({pref[s], sumgates[s + the_k]}));

        for (int s = 0; s + the_k < SZ(sumgates2); ++s)
            or_lst.push_back(add_and({pref2[s], sumgates2[s + the_k]}));

        if (not or_lst.empty())
            res_node = add_or(or_lst);
    }

    if (node_kplus1 == -1)
        add_or({node_k, node_k});
    else
        add_xor({node_k, node_kplus1});
}
