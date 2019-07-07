#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;

int n, m, k, maxq;

int value(int x, int y, int z){
	if(x <= 0 || x > n ||
	   y <= 0 || y > m ||
	   z <= 0 || z > k) return 0;

	cout << "? " << x << ' ' << y << ' ' << z << endl;
	int ans;
	cin >> ans;
	if (ans == -1) exit(0);
	return ans;
}

int dx[] = {1, -1, 0, 0, 0, 0};
int dy[] = {0, 0, 1, -1, 0, 0};
int dz[] = {0, 0, 0, 0, 1, -1};

int main(){
	srand(561);

	cin >> n >> m >> k >> maxq;

	int dims = 0;
	if(n > 1) dims++;
	if(m > 1) dims++;
	if(k > 1) dims++;

	int V = n*m*k;

	int samples = maxq / 2;
	// (int)sqrt( dims * 7.5 * V ); // should use > 2*samples queries with probability <= exp(-7.5) = 1/1800

	int record = 0;
	int x=-1, y=-1, z=-1;
	for(int i=0; i<samples; ++i){
		
		int a = 1+rand()%n,
		    b = 1+rand()%m,
		    c = 1+rand()%k;
		
		int res = value(a, b, c);
		if(res > record){
			record = res;
			x = a, y = b, z = c;
		}
	}

	cerr << "sampled " << samples << ", now expecting walk of length ~" << (V / samples) << endl;
	
	int walked = 0;
	vector<bool> tried(6, false);
	while (true) {

		int left = 0;
		for(int i=0; i<6; ++i)
			left += (int)!tried[i];

		if(left == 0){
			cerr << "walked " << walked << endl;
			cout << "! " << x << ' ' << y << ' ' << z << endl;
			return 0;
		}
		
		int r = rand() % left;

		for(int i=0; i<6; ++i) if(!tried[i]){
			if(r == 0){
				int x1 = x + dx[i],
					y1 = y + dy[i],
					z1 = z + dz[i];

				int res = value(x1, y1, z1);

				if(res > record){
					record = res;
					x = x1;
					y = y1;
					z = z1;
					for(int j=0; j<6; ++j)
						tried[j] = false;
					tried[i ^ 1] = true;
					walked++;
					break;
				} else {
					tried[i] = true;
					break;
				}
			}
			--r;
		}
	}
}
