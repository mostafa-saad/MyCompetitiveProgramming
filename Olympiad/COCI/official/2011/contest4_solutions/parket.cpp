#include <iostream>

using namespace std;

int main()
{
    int edge, middle;
    
	cin >> edge >> middle;
	
	for(int x = 3; x < 5000; x++) {
		for(int y = x; y >= 3; y--) {
			if( edge+middle == x*y && edge == 2*x+2*y-4 ) {
                cout << x << " " << y << endl;
			}
		}
	}

    return 0;
}
