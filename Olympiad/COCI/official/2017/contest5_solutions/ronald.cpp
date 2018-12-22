#include <iostream>
using namespace std;

const int N = 1000;
int n, m;
int a[N][N];
int b[N][N];

void flip(int a[N][N], int x) {
    for (int i = 0; i < n; ++i)
        a[i][x] = a[x][i] = 1 - a[i][x];
}

bool probaj(int a[N][N]) {
    for (int x = 1; x < n; ++x)
        if (a[x][0] == 0)
            flip(a, x);
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (a[i][j] == 0)
                return false;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        --x;
        --y;
        a[x][y] = a[y][x] = 1;
        b[x][y] = b[y][x] = 1;
    }
    if (probaj(a)) {
        cout << "DA" << endl;
        return 0;
    }
    flip(b, 0);
    if (probaj(b))
        cout << "DA" << endl;
    else
        cout << "NE" << endl;
}
