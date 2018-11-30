#include <iostream>
#include <set>

using namespace std;

string s;
int n;
set<string> q;

bool ok(string a, string b) {
    int j = 0;
    int v = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[j] && v == 0) {v++; i--;}
        else if (a[i] != b[j]) return false;
        j++;
    }
    return true;
}

int main() {
 	int NN;
	cin >> NN;
 	cin >> s;
    int n = s.size();
    if (n%2 == 0) {
        cout << "NOT POSSIBLE\n";
        return 0;
    }
    string a1 = s.substr(0, (n-1)/2);
    string b1 = s.substr((n-1)/2);
    if (ok(a1, b1)) q.insert(a1);
    string a2 = s.substr((n-1)/2+1);
    string b2 = s.substr(0, (n-1)/2+1);
    if (ok(a2, b2)) q.insert(a2);
    if (q.size() == 0) {
        cout << "NOT POSSIBLE\n";
    } else if (q.size() > 1) {
        cout << "NOT UNIQUE\n";
    } else {
        cout << *(q.begin()) << endl;
    }
}
