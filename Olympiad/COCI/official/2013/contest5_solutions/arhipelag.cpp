#include <iostream>
#include <algorithm>
using namespace std;

char mapa[12][12];
char novamapa[12][12];
int u[] = {0, 0, 1, -1};
int v[] = {1, -1, 0, 0};

int main() {
	int r, s;
	cin >> r >> s;
	int mini = 100, maxi = 0, minj = 100, maxj = 0;
	for (int i = 0; i < r; ++i)
		cin >> mapa[i];
	for (int i = 0; i < r; ++i)
		for (int j = 0; j < s; ++j) {
			int more = 0;
			for (int k = 0; k < 4; ++k) {
				int x = i + u[k];
				int y = j + v[k];
				if (x < 0 || y < 0 || x >= r || y >= s || mapa[x][y] == '.')
					more++;
			}
			if (more >= 3)
				novamapa[i][j] = '.';
			else
				novamapa[i][j] = mapa[i][j];
			if (novamapa[i][j] == 'X') {
				mini = min(mini, i);
				maxi = max(maxi, i);
				minj = min(minj, j);
				maxj = max(maxj, j);
			}
		}
	int k;
	cin >> k;
	for (int i = mini; i <= maxi; ++i) {
		for (int j = minj; j <= maxj; ++j)
			cout << novamapa[i][j];
		cout << endl;
	}
}
