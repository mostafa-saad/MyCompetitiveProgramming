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

int main() {
    std::iostream::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // code here
    int n = input<int>();
    int q = input<int>();

    vector<char> state0(n);
    for (int i = 0; i != n; ++i)
        state0[i] = int(input<char>() == '1');

    vector<tuple<int, int, int>> queries(q);
    for (int i = 0; i != q; ++i) {
        if (input<string>() == "toggle")
            queries[i] = make_tuple(0, input<int>() - 1, -228);
        else {
            int a = input<int>() - 1;
            int b = input<int>() - 1;
            queries[i] = make_tuple(1, a, b);

            auto state = state0;

            int ans = 0;
            
            for (int moment = 0; moment <= i; ++moment) {
                if (std::find(state.begin() + a, state.begin() + b, false) == state.begin() + b)
                    ++ans;
                
                if (moment != i and get<0>(queries[moment]) == 0) {
                    state[get<1>(queries[moment])] ^= 1;
                }
            }

            cout << ans << "\n";
        }
    }
    
    return 0;
}
