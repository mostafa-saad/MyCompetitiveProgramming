#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main(){
	int n;
	cin >> n;
	vector<int> a(2*n), b(n), jump(n);
	for(int i = 0; i < n; i++){
		cin >> a[i];
		a[n+i] = a[i];
	}
	for(int i = 0; i < n; i++){
		cin >> b[i];
	}

	jump[0] = -1;
	for(int i = 0, j = -1; i < n;){
		while(j >= 0 && b[i] != b[j]) j = jump[j];
		i++; j++;
		jump[i] = j;
	}

	for(int i = 0, j = 0; i < 2*n;){
		while(j >= 0 && a[i] != b[j])j = jump[j];

		i++; j++;

		if(j == n){
			cout << "YES" << endl;
			return 0;
		}
	}

	cout << "NO" << endl;
	return 0;
}
