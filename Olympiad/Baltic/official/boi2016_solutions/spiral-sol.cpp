#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long int Z;

constexpr Z mod = 1000000007;

struct M {
	M() : x(0) { }
	M(Z s) {
		x = s % mod;
		if(x < 0) x += mod;
	}
	
	Z x;
};
M operator+(M a, M b) {
	return M(a.x + b.x);
}
M operator-(M a, M b) {
	return M(a.x - b.x);
}
M operator-(M a) {
	return M(-a.x);
}
M operator*(M a, M b) {
	return M(a.x * b.x);
}

M arithSum(Z a, Z b) {
	return (b * (b + 1) - a * (a - 1)) / 2;
}

M clampArithSum(int a1, int b1, int a2, int b2, M c) {
	int a = max(a1, a2);
	int b = min(b1, b2);
	if(a <= b) {
		return arithSum(a, b) + (b - a + 1) * c;
	} else {
		return 0;
	}
}

bool bw(int a, int x, int b) {
	return a <= x && x <= b;
}

M layerSum(int l, int x1, int y1, int x2, int y2) {
	if(l == 0) {
		if(x1 <= 0 && x2 >= 0 && y1 <= 0 && y2 >= 0) {
			return 1;
		} else {
			return 0;
		}
	}
	
	Z val = (Z)(2 * l + 1) * (Z)(2 * l + 1);
	M ret;
	
	val = val - l;
	if(bw(y1, -l, y2)) ret = ret + clampArithSum(-l, l, x1, x2, val);
	val = val - 2 * l;
	if(bw(x1, -l, x2)) ret = ret + clampArithSum(-l + 1, l - 1, -y2, -y1, val);
	val = val - 2 * l;
	if(bw(y1, l, y2)) ret = ret + clampArithSum(-l, l, -x2, -x1, val);
	val = val - 2 * l;
	if(bw(x1, l, x2)) ret = ret + clampArithSum(-l + 1, l - 1, y1, y2, val);
	
	return ret;
}

M div2((mod + 1) / 2);
M div6((mod + 1) / 6);

int main() {
	cin.sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, q;
	cin >> n >> q;
	
	for(int i = 0; i < q; ++i) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		
		vector<int> events;
		events.push_back(0);
		events.push_back(1);
		events.push_back(2);
		events.push_back(std::abs(x1) - 1);
		events.push_back(std::abs(x1));
		events.push_back(std::abs(x1) + 1);
		events.push_back(std::abs(x2) - 1);
		events.push_back(std::abs(x2));
		events.push_back(std::abs(x2) + 1);
		events.push_back(std::abs(y1) - 1);
		events.push_back(std::abs(y1));
		events.push_back(std::abs(y1) + 1);
		events.push_back(std::abs(y2) - 1);
		events.push_back(std::abs(y2));
		events.push_back(std::abs(y2) + 1);
		sort(events.begin(), events.end());
		
		M ret;
		for(int i = 1; i < (int)events.size(); ++i) {
			int a = events[i - 1];
			int b = events[i];
			if(a < 0 || a == b) continue;
			int k = b - a;
			if(k >= 4) {
				M v[4];
				for(int j = 0; j < 4; ++j) {
					v[j] = layerSum(a + j, x1, y1, x2, y2);
				}
				M A = (v[3] - 2 * v[2] + v[1]) - (v[2] - 2 * v[1] + v[0]);
				A = A * div6;
				v[1] = v[1] - A;
				v[2] = v[2] - 8 * A;
				v[3] = v[3] - 27 * A;
				M B = v[2] - 2 * v[1] + v[0];
				B = B * div2;
				v[1] = v[1] - B;
				v[2] = v[2] - 4 * B;
				v[3] = v[3] - 9 * B;
				M C = v[1] - v[0];
				M D = v[0];
				
				M K = k;
				M H = K * (K - 1) * div2;
				ret = ret + H * H * A;
				ret = ret + K * (K - 1) * (2 * K - 1) * div6 * B;
				ret = ret + H * C;
				ret = ret + K * D;
			} else {
				for(int l = a; l < b; ++l) {
					ret = ret + layerSum(l, x1, y1, x2, y2);
				}
			}
		}
		
		cout << ret.x << '\n';
	}
	
	return 0;
}
