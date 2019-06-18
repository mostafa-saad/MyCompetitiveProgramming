#include <cstdio>
#include <algorithm>
using namespace std;

int vis[5005][160]; 
short pan[5005][5005];
int r, c, n;
int x[5005], y[5005];

int f(int pa, int p){
	vis[pa][p >> 5] |= (1 << (p & 31));
	int nx = 2 * x[p] - x[pa];
	int ny = 2 * y[p] - y[pa];
	if(nx <= 0 || ny <= 0 || nx > r || ny > c) return 2;
	if(pan[nx][ny] == 0) return -1e9;
	return 1 + f(p, pan[nx][ny]);
}

int main(){
	scanf("%d %d %d",&r,&c,&n);
	for (int i=1; i<=n; i++) {
		scanf("%d %d",&x[i],&y[i]);
		pan[x[i]][y[i]] = i;
	}
	int res = 0;
	for (int i=1; i<=n; i++) {
		for (int j=1; j<=n; j++) {
			int px = 2 * x[i] - x[j];
			int py = 2 * y[i] - y[j];
			if((px <= 0 || py <= 0) && (vis[i][j>>5]>>(j&31)) % 2 == 0) res = max(res, f(i, j));
		}
	}
	printf("%d",res == 2 ? 0 : res);
}