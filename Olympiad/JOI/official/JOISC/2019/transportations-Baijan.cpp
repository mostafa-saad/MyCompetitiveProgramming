#include "Baijan.h"
#include <queue>

using namespace std;

namespace {

const int INF = 1000000007;
int n;
vector<pair<int, int> > *E;
vector<int> dist;
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > PQ;
int Lcnt;
int Mcnt;
int buf;
bool mode;
int dist_m;
int d_sent;

void updateQ(int N) {
	for(auto e: E[N]) {
		if(dist[N] + e.second < -dist[e.first]) {
			dist[e.first] = -(dist[N] + e.second);
			PQ.push(make_pair(dist[N] + e.second, e.first));
		}
	}
}

void getQ() {
	if(Lcnt == 0) return;
	Lcnt--;
	for(;;) {
		if(PQ.empty()) {
			d_sent = (1 << 9) - 1;
			for(int i = 8; i >= 0; i--) {
				SendB((d_sent >> i) & 1);
			}
			return;
		}
		pair<int, int> rem = PQ.top();
		if(rem.first + dist[rem.second] == 0) {
			d_sent = rem.first - dist_m;
			for(int i = 8; i >= 0; i--) {
				SendB((d_sent >> i) & 1);
			}
			return;
		}
		PQ.pop();
	}
}

} // namespace

void InitB(int N, int B, std::vector<int> S, std::vector<int> T, std::vector<int> D) {
	n = N;
	E = new vector<pair<int, int> >[N];
	for(int i = 0; i < B; i++) {
		E[S[i]].push_back(make_pair(T[i], D[i]));
		E[T[i]].push_back(make_pair(S[i], D[i]));
	}
	dist.push_back(0);
	for(int i = 1; i < N; i++) {
		dist.push_back(-INF);
	}
	Lcnt = N - 1;
	dist_m = 0;
	updateQ(0);
	getQ();
	mode = false;
	Mcnt = 0;
	buf = 0;
}

void ReceiveB(bool y) {
	buf *= 2;
	buf += y;
	if(mode) {
		if(++Mcnt == 11) {
			dist_m += d_sent;
			dist[buf] = dist_m;
			updateQ(buf);
			getQ();
			mode = false;
			Mcnt = 0;
			buf = 0;
		}
	} else {
		if(++Mcnt == 9) {
			if(buf > d_sent) {
				int N = PQ.top().second;
				for(int i = 10; i >= 0; i--) {
					SendB((N >> i) & 1);
				}
				dist_m += d_sent;
				dist[N] = dist_m;
				updateQ(N);
				getQ();
			} else {
				d_sent = buf;
				mode = true;
			}
			Mcnt = 0;
			buf = 0;
		}
	}
}
