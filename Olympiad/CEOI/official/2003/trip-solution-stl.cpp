#include <fstream>
#include <set>
#include <string>

using namespace std;

int main () {
	string s1, s2;
	ifstream in("trip.in");
	ofstream out("trip.out");
	getline(in,s1);
	getline(in,s2);
	set<string> sol[2][81];
	int a[81][81],act = 0;
	for (int i=0; i<=s1.size(); i++, act=!act)
		for (int j=0; j<=s2.size(); j++)
			if (i == 0 || j == 0) {
				a[i][j] = 0;
				sol[act][j].insert("");
			}
		else {
			sol[act][j].clear();
			if (s1[i-1] == s2[j-1]) {
				a[i][j] = a[i-1][j-1]+1;
				for (set<string>::iterator it = sol[!act][j-1].begin(); it != sol[!act][j-1].end(); ++it)
					sol[act][j].insert(*it + s1[i-1]);
			}
			else {
				a[i][j] = max(a[i-1][j], a[i][j-1]);
				if (a[i][j] == a[i-1][j])
					sol[act][j] = sol[!act][j];
				if (a[i][j] == a[i][j-1])
					sol[act][j].insert(sol[act][j-1].begin(), sol[act][j-1].end());
			}
		}
	act = s1.size() % 2;
	for (set<string>::iterator it = sol[act][s2.size()].begin(); it != sol[act][s2.size()].end(); ++it)
		out << *it << endl;
	return 0;
}

