#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N;
string S;
int n;

// Ranges for which S[i] == S[i + n];
vector<pair<int, bool> > short_eq;

// Ranges for which S[i] == S[i + n + 1];
vector<pair<int, bool> > long_eq;

// Is S[i] == S[i + n] true for all i = a..b.
bool shortEqAll(int a, int b) {
	auto it = upper_bound(short_eq.begin(), short_eq.end(), make_pair(a, true));
	if(it != short_eq.end() && it->first <= b) return false;
	--it;
	if(it->second == false) return false;
	return true;
}

// Is S[i] == S[i + n - 1] true for all i = a..b.
bool longEqAll(int a, int b) {
	auto it = upper_bound(long_eq.begin(), long_eq.end(), make_pair(a, true));
	if(it != long_eq.end() && it->first <= b) return false;
	--it;
	if(it->second == false) return false;
	return true;
}

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
	
	for(int i = 0; i <= n; ++i) {
		bool val = S[i] == S[i + n];
		if(short_eq.empty() || short_eq.back().second != val) {
			short_eq.emplace_back(i, val);
		}
	}
	for(int i = 0; i < n; ++i) {
		bool val = S[i] == S[i + n + 1];
		if(long_eq.empty() || long_eq.back().second != val) {
			long_eq.emplace_back(i, val);
		}
	}
	
	bool found = false;
	int val;
	for(int i = 0; i < N; ++i) {
		if(i > n && !shortEqAll(0, i - 1 - n)) continue;
		if(i < n && !shortEqAll(i + 1, N - 1 - n)) continue;
		if(i != 0 && i != N - 1 && !longEqAll(max(i - n, 0), min(i - 1, n - 1))) continue;
		
		if(found) {
			bool match = true;
			for(int j = val; j < i; ++j) {
				if(S[j] != S[j + 1]) {
					match = false;
					break;
				}
			}
			if(!match) {
				cout << "NOT UNIQUE\n";
				return 0;
			}
		}
		
		found = true;
		val = i;
	}
	
	if(found) {
		string S2 = S.substr(0, val) + S.substr(val + 1);
		S2.resize(n);
		cout << S2 << "\n";
	} else {
		cout << "NOT POSSIBLE\n";
	}
	
	return 0;
}
