#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int n, x, y;

bool query(lint x, lint y){
	if(x < 1 || y < 1 || x > n || y > n) return false;
	printf("examine %lld %lld\n", x, y);
	fflush(stdout);
	char buf[10];
	scanf("%s", buf);
	return (*buf == 't');
}

int main(){
	scanf("%d %d %d",&n,&x,&y);
	int lim[4];
	for(int i=0; i<4; i++){
		for(int j=0; j<30; j++){
			if(!query(x + (1ll << j) * dx[i], y + (1ll << j) * dy[i])){
				lint st = (j ? (1ll << (j-1)) : 0);
				lint ed = (1ll << j);
				while(st != ed){
					lint m = (st + ed + 1) / 2;
					if(query(x + m * dx[i], y + m * dy[i])) st = m;
					else ed = m-1;
				}
				lim[i] = st;
				break;
			}
		}
	}
	x = x + (lim[0] - lim[2]) / 2;
	y = y + (lim[1] - lim[3]) / 2;
	lint m = (lim[2] + lim[0] + 1);
	int lu = 0, ld = 0, ru = 0, rd = 0;
	while(query(x - m * (lu + 1), y - m * (lu + 1))) lu++;
	while(query(x - m * (ld + 1), y + m * (ld + 1))) ld++;
	while(query(x + m * (ru + 1), y - m * (ru + 1))) ru++;
	while(query(x + m * (rd + 1), y + m * (rd + 1))) rd++;
	for(int i=-2; i<=2; i++){
		for(int j=-2; j<=2; j++){
			if((i + j) & 1) continue;
			int tlu = min(i + 2, j + 2);
			int tld = min(i + 2, 2 - j);
			int tru = min(2 - i, j + 2);
			int trd = min(2 - i, 2 - j);
			if(tie(tlu, tld, tru, trd) == make_tuple(lu, ld, ru, rd)){
				printf("solution %lld %lld\n", x - m * i, y - m * j);
				return 0;
			}
		}
	}
}
