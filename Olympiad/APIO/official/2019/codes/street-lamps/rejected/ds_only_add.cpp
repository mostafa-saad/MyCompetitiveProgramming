// Dmitry _kun_ Sayutin (2019)

#include <bits/stdc++.h>

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

template <typename T>
T input() {
    T res;
    cin >> res;
    LASSERT(cin);
    return res;
}

template <typename IT>
void input_seq(IT b, IT e) {
    std::generate(b, e, input<typename std::remove_reference<decltype(*b)>::type>);
}

#define SZ(vec)         int((vec).size())
#define ALL(data)       data.begin(),data.end()
#define RALL(data)      data.rbegin(),data.rend()
#define TYPEMAX(type)   std::numeric_limits<type>::max()
#define TYPEMIN(type)   std::numeric_limits<type>::min()

// RMaxQ
vector<int> tree;
void build(int v, int l, int r, vector<int>& arr) {
    if (l == r - 1) {
        tree[v] = arr[l];
        return;
    }

    int m = l + (r - l) / 2;
    build(2 * v + 1, l, m, arr);
    build(2 * v + 2, m, r, arr);

    tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
}

int get_max(int v, int vl, int vr, int l, int r) {
    if (vr <= l or r <= vl)
        return TYPEMIN(int);

    if (l <= vl and vr <= r)
        return tree[v];

    int m = vl + (vr - vl) / 2;
    return max(get_max(2 * v + 1, vl, m, l, r),
               get_max(2 * v + 2, m, vr, l, r));
}

void change(int v, int vl, int vr, int i, int val) {
    if (vl == vr - 1) {
        tree[v] = val;
        return;
    }

    int m = vl + (vr - vl) / 2;
    if (i < m)
        change(2 * v + 1, vl, m, i, val);
    else
        change(2 * v + 2, m, vr, i, val);
    
    tree[v] = max(tree[2 * v + 1], tree[2 * v + 2]);
}

int main() {
    std::iostream::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // code here
    int n = input<int>();
    int q = input<int>();

    vector<int> arr(n);
    for (int i = 0; i != n; ++i)
        if (input<char>() == '1')
            arr[i] = 0;
        else
            arr[i] = TYPEMAX(int);

    tree.resize(4 * n);
    build(0, 0, n, arr);
    
    for (int i = 1; i <= q; ++i) {
        if (input<string>() == "toggle") {
            int pos = input<int>() - 1;
            assert(arr[pos] == TYPEMAX(int));
            arr[pos] = i;

            change(0, 0, n, pos, i);
        } else {
            int a = input<int>() - 1;
            int b = input<int>() - 1;

            int tm = get_max(0, 0, n, a, b);

            int ans = 0;
            if (tm != TYPEMAX(int))
                ans = i - tm;

            cout << ans << "\n";
        }
    }
    
    return 0;
}
