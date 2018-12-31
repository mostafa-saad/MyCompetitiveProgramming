#include <cstdio>
#include <algorithm>
using namespace std;

int n, m, pnt[3000][2], ans;

int sq(int a)
{
	return a*a;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int x, y, i = 0; i < n; i++) {
		scanf("%d%d", &x, &y);
		x+=1500;
		y+=1501;
		if (pnt[x][0]) {
			pnt[x][0] = min(pnt[x][0], y);
			pnt[x][1] = max(pnt[x][1], y);
		}
		else {
			pnt[x][0] = y;
			pnt[x][1] = y;
		}
	}

	for (int i = 0; i < 3000; i++) {
		if (pnt[i][0]) {
			ans = max(ans, sq(pnt[i][1]-pnt[i][0]));
			for (int j = i+1; j < 3000; j++) {
				if (pnt[j][0]) {
					ans = max(ans, sq(j-i) + max(sq(pnt[i][1]-pnt[j][0]), sq(pnt[i][0]-pnt[j][1])));
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
