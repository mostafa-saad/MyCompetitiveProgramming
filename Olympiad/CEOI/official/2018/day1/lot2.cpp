#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
	int n, l, q;
	vector<int> tab;
	cin >> n >> l;
	tab.resize(n);
	for (int i = 0; i < n; i ++) cin >> tab[i];
	cin >> q;
	vector<pair<int,int>> que;
	for (int i = 0; i < q; i ++) {
		int x;
		cin >> x;
		que.emplace_back(x, i);
	}
	vector<vector<short int>> res(n, vector<short int>(q + 1));
	sort(que.begin(), que.end());
	for (int diff = 1; diff + l <= n; diff ++) {
		int sum = 0;
        int gdzie = q;
		for (int i = 0; i + diff < n; i ++) {
            int delta = 0;
			delta = (tab[i] == tab[i + diff]);
			if (i - l >= 0) {
				delta -= (tab[i - l] == tab[i - l + diff]);
			}
            sum += delta;
            if (i - l + 1 > 0) {
                if (delta > 0) {
                    while (gdzie > 0 && que[gdzie - 1].first >= l - sum) {
                        gdzie --;
                    }
                }
                if (delta < 0) {
                    while (gdzie < q && que[gdzie].first < l - sum) {
                        gdzie ++;
                    }
                }
                if (gdzie == q) continue;
                res[i - l + 1][q] ++;
                res[i - l + 1 + diff][q] ++;
                if (gdzie) {
                    res[i - l + 1][gdzie - 1] --;
                    res[i - l + 1 + diff][gdzie - 1] --;
                }
            } else if (i - l + 1 == 0) {
                while (gdzie > 0 && que[gdzie - 1].first >= l - sum) gdzie --;
                while (gdzie < q && que[gdzie].first < l - sum) gdzie ++;
                if (gdzie == q) continue;
                res[i - l + 1][q] ++;
                res[i - l + 1 + diff][q] ++;
                if (gdzie) {
                    res[i - l + 1][gdzie - 1] --;
                    res[i - l + 1 + diff][gdzie - 1] --;
                }
            }
		}
	}
    for (int j = q - 1; j >= 0; j--)
        for (int i = 0; i <= n - l; i ++)
            res[i][j] += res[i][j + 1];
    for (int i = 0; i < q; i ++) {
        for (int k = 0; k < q; k ++) {
            if (que[k].second == i) {
                for (int j = 0; j <= n - l; j ++) {
                    cout << res[j][k] << " ";
                }
            }
        }
        cout << "\n";
    }
}
