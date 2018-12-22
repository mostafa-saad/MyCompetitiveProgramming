#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cctype>

using namespace std;

int main(){
	int r, s;
	cin >> r >> s;
	vector<string> sat;
	for (int i = 0; i < r; i++){
		string a;
		cin >> a;
		sat.push_back(a);
	}

	map<int, int> place;
	int t = 1;

	for (int i = s - 2; i >= 1; i--){
		int x = 0;
		for (int j = 0; j < r; j++)
			if ( isdigit(sat[j][i]) && !isdigit(sat[j][i + 1]) ){
				place[sat[j][i]] = t;
				x = 1;
			}
		t += x;
	}

	for (int i = '1'; i <= '9'; i++)
		cout << place[i] << endl;

	return 0;
}
