#include <string>
#include <iostream>
#include <cctype>

using namespace std;

int main() {
	string a;
	cin >> a;
	for (int i = 0; i < (int)(a.size()); i++){
		if (isupper(a[i]))
			cout << a[i];
	}
	cout << endl;
	return 0;
}
