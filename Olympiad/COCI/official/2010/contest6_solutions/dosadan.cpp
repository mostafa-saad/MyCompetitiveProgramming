#include <iostream>

using namespace std;

int main(){
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		int a;
		cin >> hex >> a;
		if ( a < 0x20 ) {
			cout << ".";			
		}
		else
			cout << "-";		
	}
	cout << endl;
	return 0;
}
