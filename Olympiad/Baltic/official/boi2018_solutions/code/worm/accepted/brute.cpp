#include <iostream>
#include <cstdlib>
using namespace std;

int main(){
	int n, m, k, maxq;
	cin >> n >> m >> k >> maxq;

	int record = 0;
	int ansx = -1, ansy = -1, ansz = -1;

	for(int x = 1; x <= n; x++){
		for(int y = 1; y <= m; y++){
			for(int z = 1; z <= k; z++){
				int res;
				cout << "? " << x << ' ' << y << ' ' << z << endl;
				cin >> res;
				if (res == -1) exit(0);
				if(res > record){
					record = res;
					ansx = x;
					ansy = y;
					ansz = z;
				}
			}
		}
	}
	
	cout << "! " << ansx << ' ' << ansy << ' ' << ansz << endl;
}
