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

vector<pair<int, int>> points;

struct segtree_node {
    vector<int> y_points;

    vector<int> tree;

    int query(int v, int l, int r, int y) {
        int res = tree[v];

        if (l == r - 1)
            return res;
        
        int m = l + (r - l) / 2;
        
        if (y >= y_points[m])
            res += query(2 * v + 2, m, r, y);
        else
            res += query(2 * v + 1, l, m, y);

        return res;
    }

    void seg_modif(int v, int l, int r, int maxy, int val) {
        if (y_points[r - 1] <= maxy) {
            tree[v] += val;
            return;
        }

        if (y_points[l] > maxy)
            return;

        int m = l + (r - l) / 2;
        seg_modif(2 * v + 1, l, m, maxy, val);
        seg_modif(2 * v + 2, m, r, maxy, val);
    }
};

vector<segtree_node> tree;

vector<int> seg_build(int v, int l, int r) {
    if (l == r - 1) {
        tree[v].y_points = {points[l].second};
    } else {
        int m = l + (r - l) / 2;

        auto r1 = seg_build(2 * v + 1, l, m);
        auto r2 = seg_build(2 * v + 2, m, r);

        tree[v].y_points.resize(SZ(r1) + SZ(r2));
        tree[v].y_points.resize(std::set_union(ALL(r1), ALL(r2), tree[v].y_points.begin())
                                - tree[v].y_points.begin());
    }

    tree[v].tree.resize(4 * SZ(tree[v].y_points));
    return tree[v].y_points;
}

int seg_query(int v, int l, int r, int x, int y) {
    int res = tree[v].query(0, 0, SZ(tree[v].y_points), y);

    if (l == r - 1)
        return res;

    int m = l + (r - l) / 2;
    if (make_pair(x, y) >= points[m])
        res += seg_query(2 * v + 2, m, r, x, y);
    else
        res += seg_query(2 * v + 1, l, m, x, y);

    return res;
}

void seg_modif(int v, int l, int r, int minx, int maxy, int val) {
    if (points[r - 1].first < minx)
        return;
    
    if (minx <= points[l].first) {
        tree[v].seg_modif(0, 0, SZ(tree[v].y_points), maxy, val);
        return;
    }

    int m = l + (r - l) / 2;
    seg_modif(2 * v + 1, l, m, minx, maxy, val);
    seg_modif(2 * v + 2, m, r, minx, maxy, val);
}

int main() {
    std::iostream::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // code here
    int n = input<int>();
    int q = input<int>();

    vector<char> state(n);
    for (int i = 0; i != n; ++i)
        state[i] = int(input<char>() == '1');

    vector<tuple<int, int, int>> in(q);
    for (int i = 0; i != q; ++i) {
        if (input<string>() == "toggle")
            in[i] = make_tuple(0, input<int>() - 1, -228);
        else {
            int a = input<int>() - 1;
            int b = input<int>() - 1;
            in[i] = make_tuple(1, a, b);
            points.emplace_back(a, b);
        }
    }

    sort(ALL(points));
    points.resize(std::unique(ALL(points)) - points.begin());
    
    tree.resize(4 * SZ(points));
    seg_build(0, 0, SZ(points));

    
    set<pair<int, int>> segments;
        
    for (int i = 0; i <= n;) {
        int j = i;
        while (j != n and state[j])
            ++j;
            
        segments.emplace(i, j);
        i = j + 1;
        
        //plane_op(i, j, 0);
    }        

    auto plane_op = [&](int a, int b, int val) {
        seg_modif(0, 0, SZ(points), a, b, val);
    };
        
    auto toggle = [&](int i, int tm) {
        // between i and i+1.
        
        if (state[i] == 0) {
            auto it = segments.lower_bound(make_pair(i + 1, -1));
            auto prev = std::prev(it);
            
            int A = prev->first;
            int B = it->second;
            
            segments.erase(it);
            segments.erase(prev);
            segments.emplace(A, B);
            
            plane_op(A, i, +tm);
            plane_op(i + 1, B, +tm);
            plane_op(A, B, -tm);
        } else {
            auto it = segments.upper_bound(make_pair(i, TYPEMAX(int)));
            --it;
            
            int A = it->first;
            int B = it->second;
                
            segments.erase(it);
            segments.emplace(A, i);
            segments.emplace(i + 1, B);

            plane_op(A, B, +tm);
            plane_op(A, i, -tm);
            plane_op(i + 1, B, -tm);
        }

        state[i] ^= 1;
    };
    
    for (int curtime = 1; curtime <= q; ++curtime) {
        if (get<0>(in[curtime - 1]) == 0)
            toggle(get<1>(in[curtime - 1]), curtime);
        else {
            int a = get<1>(in[curtime - 1]);
            int b = get<2>(in[curtime - 1]);
            
            int ans = seg_query(0, 0, SZ(points), a, b);
            auto it = std::prev(segments.upper_bound(make_pair(a, TYPEMAX(int))));
            
            if (it->first <= a and b <= it->second)
                ans += curtime;
            
            cout << ans << "\n";
        }
    }

    return 0;
}
