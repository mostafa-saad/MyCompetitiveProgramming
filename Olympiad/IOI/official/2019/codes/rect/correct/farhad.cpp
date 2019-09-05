#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int kMax = 3000 + 10;

using PII = pair<int, int>;

struct Interval {
	Interval(int key, int start, int end) : 
		key(key), start(start), end(end), count(0) {}
	int key, start, end, count = 0;
};

vector<Interval> vertical_intervals, horizontal_intervals;
vector<PII> lookup[kMax][kMax];
vector<int> v, previous;
PII tmp[kMax][kMax];
int a[kMax][kMax];
int n, m;

void FindPrevGreaterOrEqual(const vector<int>& v, int* output) {
	static std::vector<PII> s;
	memset(output, -1, v.size() * sizeof(int));
	s.reserve(v.size());
	s.clear();
	for (int i = 0; i < v.size(); ++i) {
		while(!s.empty() && s.back().first < v[i]) s.pop_back();
		if (!s.empty()) {
			output[i] = s.back().second;
		}
		s.emplace_back(v[i], i);
	}
}

void Summerize(vector<Interval>& intervals) {
	memset(tmp, -1, sizeof tmp);
	for (int i = intervals.size() - 1; i >= 0; --i) {
		auto& interval = intervals[i];
		const int prev = tmp[interval.start][interval.end].first;
		if (prev == interval.key) {
			continue;
		}
		if (prev != interval.key + 1) {
			tmp[interval.start][interval.end].second = 0;
		}
		tmp[interval.start][interval.end].first = interval.key;
		interval.count = ++tmp[interval.start][interval.end].second;
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> a[i][j];
		}
	}
	v.resize(m);
	previous.resize(m);
	for (int i = 0; i < n; ++i) {
		copy(a[i], a[i] + m, v.data());
		FindPrevGreaterOrEqual(v, previous.data());
		for (int j = 0; j < m; ++j) {
			if (previous[j] != -1)
			horizontal_intervals.push_back({i, previous[j], j});
		}
		reverse(v.begin(), v.end());
		FindPrevGreaterOrEqual(v, previous.data());
		for (int j = 0; j < m; ++j) {
			if (previous[j] != -1)
				horizontal_intervals.emplace_back(i, m - 1 - j, m - 1 - previous[j]);
		}
	}
	Summerize(horizontal_intervals);

	v.resize(n);
	previous.resize(n);
	for (int j = 0; j < m; ++j) {
		for (int i = 0; i < n; ++i) {
			v[i] = a[i][j];
		}
		FindPrevGreaterOrEqual(v, previous.data());
		for (int i = 0; i < n; ++i) {
			if (previous[i] != -1) vertical_intervals.push_back({j, previous[i], i});
		}
		reverse(v.begin(), v.end());
		FindPrevGreaterOrEqual(v, previous.data());
		for (int i = 0; i < n; ++i) {
			if (previous[i] != -1) {
				vertical_intervals.emplace_back(j, n - 1 - i, n - 1 - previous[i]);
			}
		}
	}
	Summerize(vertical_intervals);

	for (const auto& i : vertical_intervals) {
		lookup[i.start][i.key].emplace_back(i.end, i.count);
	}

	int ans = max(min(2, n) * m, min(2, m) * n);
	for (const auto& interval : horizontal_intervals) {
		if (interval.key == 0) continue;
		for (const auto& p : lookup[interval.key - 1][interval.start + 1]) {
			if (p.first <= interval.key + interval.count &&
					interval.end <= interval.start + 1 + p.second) {
				ans = max(ans, (p.first - interval.key + 2) * (interval.end - interval.start + 1));
			}
		}
	}
	cout << ans << endl;
	return 0;	
}
