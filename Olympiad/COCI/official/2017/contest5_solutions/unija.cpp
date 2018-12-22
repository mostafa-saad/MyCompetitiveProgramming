#include <iostream>
using namespace std;

const int MAX_X = 5 * 1000 * 1000;
int h[MAX_X + 2];

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        if (h[x / 2] < y)
            h[x / 2] = y;
    }
    long long p = 0;
    for (int i = MAX_X; i > 0; --i) {
        if (h[i] < h[i + 1])
            h[i] = h[i + 1];
        p += h[i];
    }
    cout << 2 * p << endl;
}
