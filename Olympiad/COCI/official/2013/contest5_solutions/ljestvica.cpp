#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	cin >> s;
	int Amol = 0, Cdur = 0;
	for (int i = 0; i < (int)s.size(); ++i)
		if (i == 0 || s[i - 1] == '|') {
			if (s[i] == 'A' || s[i] == 'D' || s[i] == 'E')
				Amol++;
			if (s[i] == 'C' || s[i] == 'F' || s[i] == 'G')
				Cdur++;
		}
	if (Amol == Cdur) {
		Amol += (s[(int)s.size() - 1] == 'A');
		Cdur += (s[(int)s.size() - 1] == 'C');
	}
	if (Amol == Cdur)
		cout << "Ilegalan primjer!" << endl;
	else
		cout << (Amol > Cdur? "A-mol" : "C-dur") << endl;
	return 0;
}
