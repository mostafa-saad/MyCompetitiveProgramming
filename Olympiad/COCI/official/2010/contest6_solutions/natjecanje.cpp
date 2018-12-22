#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;

int main(){
	int n, s, r;
	cin >> n >> s >> r;

	vector<int> destroyed(n, 0);
	vector<int> reserve(n, 0);

	for (int i = 0; i < s; i++){
		int a;
		cin >> a;
		a--;
		destroyed[a] = 1;
	}

	for (int i = 0; i < r; i++){
		int a;
		cin >> a;
		a--;
		if ( destroyed[a] == 1 ){
			destroyed[a] = 0;
		}
		else 
			reserve[a] = 1;
	}

	int sol = 0;
	for (int i = 0; i < n; i++)
		if ( destroyed[i] == 1 ) {
			if ( i > 0 && reserve[i - 1] == 1 ){
				reserve[i - 1] = 0;
				destroyed[i] = 0;
			}
			else if ( i < n - 1 && reserve[i + 1] == 1 ){
				reserve[i + 1] = 0;
				destroyed[i] = 0;
			}
			else
				sol++;
		}
	
	cout << sol << endl;

	return 0;
}
