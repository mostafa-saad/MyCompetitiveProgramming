#include <iostream>
#include <string>
using namespace std;

int main() {
	string a;
	cin >> a;
	for (int i = 0; i < (int)a.size(); ++i) {
		if (string("CAMBRIDGE").find(a[i]) == string::npos) {
			cout << a[i];
		}
	}
	cout << endl;
}
