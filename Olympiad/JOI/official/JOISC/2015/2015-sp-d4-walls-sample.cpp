#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <cstdlib>
using namespace std;
typedef long long ll;

const int MAXN = 200200;
const int MAXM = 200200;

int N, M, M0, A[MAXN], B[MAXN], P[MAXM];
vector<int> laser;
set<pair<int, int> > diffs;
set<pair<int, int> > gaps;
vector<pair<int, int> > qs;
ll sol[MAXN];
ll gap_sum;

void rm(int loc)
{
	auto df = *(diffs.lower_bound(make_pair(loc, -1001001001)));

	gap_sum -= abs(df.second);
	gaps.erase(make_pair(abs(df.second), df.first));
	diffs.erase(df);
}

void ins(int loc, int gap)
{
	gap_sum += abs(gap);
	diffs.insert(make_pair(loc, gap));
	gaps.insert(make_pair(abs(gap), loc));
}

int mov(int &left, int &right, int target)
{
	if (left <= target && target <= right) return 0;
	if (right < target) {
		int d = target - right;
		left += d;
		right += d;
		return d;
	}
	int d = left - target;
	left -= d;
	right -= d;
	return d;
}

int main()
{
	scanf("%d%d", &N, &M0);
	for (int i = 0; i < N; ++i) scanf("%d%d", &(A[i]), &(B[i]));

	int M = 0;
	for (int i = 0; i < M0; ++i) {
		int Ptmp;
		scanf("%d", &Ptmp);

		if (M == 0 || P[M - 1] != Ptmp) P[M++] = Ptmp;
	}

	laser.push_back(P[0]);
	for (int i = 1; i < M - 1; ++i) {
		if (P[i] == P[i - 1]) continue;
		if ((P[i - 1] >= P[i] && P[i] <= P[i + 1]) || (P[i - 1] <= P[i] && P[i] >= P[i + 1])) laser.push_back(P[i]);
	}
	laser.push_back(P[M - 1]);
	
	int orig = laser[0];
	gap_sum = 0;
	for (int i = 1; i < laser.size(); ++i) ins(i, laser[i] - laser[i - 1]);
	for (int i = 0; i < N; ++i) qs.push_back(make_pair(B[i] - A[i], i));

	sort(qs.begin(), qs.end());

	for (int i = 0; i < N; ++i) {
		int qi = qs[i].second;
		
		while (1 < gaps.size() && gaps.begin()->first <= qs[i].first) {
			auto beg = *(gaps.begin());

			if (diffs.begin()->first == beg.second) {
				orig += diffs.begin()->second;
				rm(beg.second);
			} else if (diffs.rbegin()->first == beg.second) {
				rm(beg.second);
			} else {
				auto df = diffs.lower_bound(make_pair(beg.second, -1001001001));
				auto prev = df; --prev;
				auto next = df; ++next;

				int gap_new = prev->second + df->second + next->second;
				rm(prev->first);
				rm(df->first);
				rm(next->first);

				ins(beg.second, gap_new);
			}
		}

		if (gaps.size() >= 2) {
			ll tmp = gap_sum - gaps.size() * (ll)(B[qi] - A[qi]);
			int gfirst = diffs.begin()->second;

			if (gfirst > 0) {
				tmp += abs(A[qi] - orig);
			} else {
				tmp += abs(B[qi] - orig);
			}
			sol[qi] = tmp;
		} else {
			ll tmp = 0;

			int left = A[qi], right = B[qi];
			tmp += mov(left, right, orig);
			if (gaps.size() == 1) tmp += mov(left, right, orig + diffs.begin()->second);

			sol[qi] = tmp;
		}
	}

	for (int i = 0; i < N; ++i) printf("%lld\n", sol[i]);

	return 0;
}
