#include <iostream>
#include <climits>

using namespace std;

struct T {
	T(int val) : val(val) { }
	T(T* a, T* b, bool* d) : val(0), a(a), b(b), d(d) { }
	
	int val;
	T* a;
	T* b;
	bool* d;
	
	int query() {
		if(val) {
			return val;
		} else if(*d) {
			return a->query();
		} else {
			return min(a->query(), b->query());
		}
	}
	bool del(int x) {
		if(val) {
			if(val == x) {
				val = INT_MAX;
				return true;
			}
			return false;
		} else if(*d) {
			return a->del(x);
		} else {
			if(a->del(x)) {
				*d = true;
				return true;
			}
			if(b->del(x)) {
				*d = true;
				swap(*a, *b);
				return true;
			}
			return false;
		}
	}
};

T* t[202020];

int main() {
	cin.sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	cin >> n;
	for(int i = 1; i <= n; ++i) {
		int x;
		cin >> x;
		t[i] = new T(x);
	}
	
	for(int i = 2; i <= n; ++i) {
		T* a = t[i / 2];
		T* b = t[i];
		bool* d = new bool(false);
		t[i / 2] = new T(a, b, d);
		t[i] = new T(b, a, d);
	}
	
	for(int i = 1; i <= n; ++i) {
		int val = t[i]->query();
		t[i]->del(val);
		if(i != 1) cout << ' ';
		cout << val;
	}
	cout << '\n';
	
	return 0;
}
