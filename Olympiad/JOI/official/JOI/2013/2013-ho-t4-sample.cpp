#include <iostream>
#include <string>
#include <queue>
using namespace std;

int N;
string S;

bool Test(int count) {
	string s = S;
	int head = count, foot = count;
	queue<int> q;

	q = queue<int>();
	for (int i = s.size() - 1; 0 <= i && head; i--) {
		if (s[i] == 'I') {
			q.push(i);
		} else if (s[i] == 'O' && q.size()) {
			s[q.front()] = 'i';
			s[i] = 'o';
			q.pop();
			head--;
		}
	}
	q = queue<int>();
	for (int i = s.size() - 1; 0 <= i && foot; i--) {
		if (s[i] == 'o') {
			q.push(i);
		} else if ((s[i] == 'I' || s[i] == 'J') && q.size()) {
			s[q.front()] = '0';
			s[i] = '1';
			q.pop();
			foot--;
		}
	}
	return foot == 0;
}

int BinarySearch() {
	int low = 0, high = S.size() / 3 + 1;
	// lowは必ずOK，highは必ずダメ
	while (low + 1 < high) {
		int mid = (low + high) / 2;
		if (Test(mid)) {
			low = mid;
		} else {
			high = mid;
		}
	}
	return low;
}

int main() {
	cin >> N >> S;
	cout << BinarySearch() << endl;
	return 0;
}
