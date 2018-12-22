#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {

	vector<string> a;
	a.resize(6);
	bool ok = false;

	for (int i = 0; i < 6; ++i)
		cin >> a[i];
	
	do {
		string stupci[3];
		
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				stupci[j] += a[i][j];
				
		ok = true;
		for (int i = 0; i < 3; i++)
			if (stupci[i] != a[i + 3])
				ok = false;

		if (ok) {
			for (int i = 0; i < 3; ++i)
				cout << a[i] << endl;
			break;
		}
			
	} while (next_permutation(a.begin(), a.end()));
	
	if (!ok)
		cout << 0 << endl;
}
