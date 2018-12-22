#include <iostream>
#include <string>
using namespace std;

int main () {
	string s;
	cin >> s;
	int sol = 0;
	string prva_slova = "nnADGJMPTW";
	for (int i = 0; i < s.size(); i++) {
		int tipka = 0;
		for (int j = 2; j < 10; j++)
			if (s[i] >= prva_slova[j])
				tipka = j;
		sol += tipka + 1;
	}
	cout << sol << endl;
}
