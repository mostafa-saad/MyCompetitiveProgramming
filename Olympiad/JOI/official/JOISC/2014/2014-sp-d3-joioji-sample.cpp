/*
	Sort then Shakutori (O(N log N))
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Pos {
	int jo;
	int ji;
	int len;

	bool operator < (const Pos &other) const {
		if (jo != other.jo) return jo < other.jo;
		if (ji != other.ji) return ji < other.ji;
		return len < other.len;
	}
};

int chmax(int &a, int n) {
	if (n > a) a = n;
	return a;
}

int main() {
	int N;
	string S;
	cin >> N >> S;

	vector<Pos> ois;
	Pos origin;
	origin.jo = origin.ji = origin.len = 0;
	ois.push_back(origin);

	int Js = 0, Os = 0, Is = 0;
	for (int i = 0; i < N; i++) {
		char c = S[i];
		if (c == 'J') Js++;
		else if (c == 'O') Os++;
		else Is++;

		Pos pos;
		pos.jo = Js - Os;
		pos.ji = Js - Is;
		pos.len = i + 1;

		ois.push_back(pos);
	}
	sort(ois.begin(), ois.end());

	int ans = 0;
	int lastind = 0;
	for (int i = 1; i < ois.size(); i++) {
		if (ois[i].jo == ois[lastind].jo && ois[i].ji == ois[lastind].ji) {
			chmax(ans, ois[i].len - ois[lastind].len);
		}
		else {
			lastind = i;
		}
	}

	cout << ans << endl;
	return 0;
}
