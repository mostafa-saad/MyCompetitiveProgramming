/**
 * A valid solution for task FRIENDS.
 *
 * Author: Marijonas Petrauskas
 */

#include <iostream>
#include <string>

using namespace std;

string try_candidate(const string &s, int orig_start, int orig_len, int modified_start) {
	bool was_mismatch = false;
	int orig = orig_start, mod = modified_start, i = 0;
	while (i < orig_len) {
		if (s[orig] != s[mod]) {
			if (was_mismatch)
				return string();
			was_mismatch = true;
			mod++;
		} else
			orig++, mod++, i++;
	}
	return s.substr(orig_start, orig_len);
}

int main() {
	string final;
	int N;
	cin >> N;
	cin >> final;
	int orig_len = (final.length() - 1) / 2;
	const string&
		pos1 = try_candidate(final, orig_len + 1, orig_len, 0),
		pos2 = try_candidate(final, 0, orig_len, orig_len);
	if ( (pos1.empty() && pos2.empty()) || (final.size() % 2 == 0))
		cout << "NOT POSSIBLE" << endl;
	else if (pos1.empty())
		cout << pos2 << endl;
	else if (pos2.empty())
		cout << pos1 << endl;
	else if (pos1 != pos2)
		cout << "NOT UNIQUE" << endl;
	else 
		cout << pos1 << endl;
	return 0;
}
