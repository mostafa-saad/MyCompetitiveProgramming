#include <bits/stdc++.h>
using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " <<

#define fi first
#define se second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
  
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    for (n--; n >= 0; ) {
        int x = m;
        while ((x & n) != n) x++;
        for (int i = x; i >= m; i--)
            cout << n-- << " " << i << "\n";
        m = x + 1;
    }

    return 0;
}

