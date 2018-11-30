#include <iostream>
#include <algorithm>

using namespace std;

int N;
string S;
int n;

int main() {
	int NN;
	cin >> NN;
cin >> S;
	N = S.size();
	
	if(N % 2 == 0) {
		cout << "NOT POSSIBLE\n";
		return 0;
	}
	int n = N / 2;
	
	bool found = false;
	string val;
	for(int i = 0; i < N; ++i) {
		string S2 = S.substr(0, i) + S.substr(i + 1);
		bool ok = true;
		for(int i = 0; i < n; ++i) {
			if(S2[i] != S2[i + n]) ok = false;
		}
		if(ok) {
			S2.resize(n);
			if(found && S2 != val) {
				cout << "NOT UNIQUE\n";
				return 0;
			} else {
				found = true;
				val = S2;
			}
		}
	}
	
	if(found) {
		cout << val << "\n";
	} else {
		cout << "NOT POSSIBLE\n";
	}
	
	return 0;
}
