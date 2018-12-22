#include <iostream>
#include <vector>
using namespace std;

int abs(int x) { return x > 0 ? x : -x; }

int main() {
    int a, b;
    cin >> a >> b;
    int M = b + 1;
    vector<int> v(M);
    for (int d = 1; d < M; ++d) {
        int dd = d + d;
        while (dd < M) {
            v[dd] += d;
            dd += d;
        }
    }
    long long s = 0;
    for (int i = a; i <= b; ++i)
        s += abs(v[i] - i);
    cout << s << endl;
    return 0;
}
