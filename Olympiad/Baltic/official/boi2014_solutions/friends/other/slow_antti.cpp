#include <iostream>
#include <set>

using namespace std;

string s;
int n;
set<string> q;

int main() {
	int NN;
	cin >> NN;
	cin >> s;
    n = s.size();
    if (n%2 == 0) {
        cout << "NOT POSSIBLE\n";
        return 0;
    }
    for (int i = 0; i < n; i++) {
        string u = s.substr(0, i) + s.substr(i+1);
        string a = u.substr(0, (n-1)/2);
        string b = u.substr((n-1)/2);
        if (a == b) q.insert(a);
    }
    if (q.size() == 0) {
        cout << "NOT POSSIBLE\n";
    } else if (q.size() > 1) {
        cout << "NOT UNIQUE\n";
    } else {
        cout << *(q.begin()) << endl;
    }
}
