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
            vector<bool> ok(N);
            for (int j = 0; j < M; j++) {
                if (((i&(1<<j)) == 0) == direction) {
                    for (int k = a[j]; k != b[j]; k = (k+1)%N) {
                        ok[k] = true;
                    }
                    ok[b[j]] = true;
                }
            }
            for (int j = 0; j < N; j++) {
                if (!ok[j]) {
                    goto failed;
                }
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
