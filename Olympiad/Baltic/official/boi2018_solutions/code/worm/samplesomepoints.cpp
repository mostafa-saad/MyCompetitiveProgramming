#include <iostream>
#include <map>
#include <cstdlib>
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> tri;
#define fst first
#define snd second.first
#define trd second.second

int n, m, k, maxq;
map<tri, int> mem;

int value(int x, int y, int z){
	if(x <= 0 || x>n ||
	   y <= 0 || y>m ||
	   z <= 0 || z>k) return 0;
	
	tri t(x, pii(y,z));
	int& o = mem[t];
	if (o) return o;

	cout << "? " << x << ' ' << y << ' ' << z << endl;
	cin >> o;
	if (o == -1) exit(0);
	return o;
}

int dx[] = {1,-1,0,0,0,0};
int dy[] = {0,0,1,-1,0,0};
int dz[] = {0,0,0,0,1,-1};

int main(){
	srand(561);
	cin >> n >> m >> k >> maxq;

	while(true){
		int x = 1 + rand()%n,
		    y = 1 + rand()%m,
		    z = 1 + rand()%k;

		int v = value(x, y, z);

		for(int dir = 0; dir < 6; dir++){
			int u = value(x+dx[dir], y+dy[dir], z+dz[dir]);
			if(u > v) goto fail;
		}
		cout << "! " << x << ' ' << y << ' ' << z << endl;

		fail: ;
	}
}
