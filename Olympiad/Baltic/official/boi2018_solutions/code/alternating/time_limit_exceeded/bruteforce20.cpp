#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> a(M), b(M);
    for (int i = 0; i < M; i++) {
        cin >> a[i] >> b[i];
        --a[i]; --b[i];
    }
    for (int i = 0; i < (1<<M); i++) {
        for (int direction = 0; direction < 2; direction++) {
            for (int k = 0; k < N; k++) {
                bool ok = false;
                for (int j = 0; j < M; j++) {
                    if (((i&(1<<j)) == 0) == direction) {
                        if ((k >= a[j] && k <= b[j]) || (a[j] > b[j] && (k <= b[j] || k >= a[j]))) {
                            ok = true;
                            break;
                        }
                    }
                }
                if (!ok)
                    goto failed;
            }
        }
        for (int j = 0; j < M; j++) {
            if (i&(1<<j)) {
                cout << "1";
            }
            else {
                cout << "0";
            }
        }
        cout << endl;
        return 0;
        failed:;
    }
    cout << "IMPOSSIBLE" << endl;
}
