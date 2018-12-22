#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0;i < n;++i)
#define FOR(i, a, b) for(int i = a;i < b;++i)
#define pb push_back
#define X first
#define Y second
#define trace(x) cerr << #x << " = " << x << '\n'
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;
const int MAX = 5010;
char aa[MAX], bb[MAX], cc[MAX];
int a[MAX], b[MAX];
int n, cnt[3], place[3], cntcp[3], placecp[3];

void refresh() {
	REP(i, 3) {
		placecp[i] = place[i];
		cntcp[i] = cnt[i];
	}
}

bool possible(int i, int j) {
	if(b[i] == j || cnt[j] == -1) return false;
	REP(k, min(cnt[0], place[1]) + 1) {
		refresh();
		cntcp[0] -= k;
		placecp[1] -= k;
		if(placecp[2] < cntcp[0]) continue;
		placecp[2] -= cntcp[0];
		cntcp[1] -= min(placecp[2], cntcp[1]);
		if(placecp[0] < cntcp[1]) continue;
		placecp[0] -= cntcp[1];
		if(placecp[0] + placecp[1] < cntcp[2]) continue;
		return true;
	}
	return false;
}

void solve() {
	REP(i, n) {
		++cnt[a[i]];
		++place[b[i]];
	}
	REP(i, n) {
		--place[b[i]];
		REP(j, 3) {
			--cnt[j];
			if(possible(i, j)) {
				printf("%c", j + 'a');
				break;
			}
			++cnt[j];
		}
	}
}

int main() {
	scanf("%d %s %s", &n, aa, bb);
	REP(i, n) {
		a[i] = aa[i] - 'a';
		b[i] = bb[i] - 'a';
	}
	solve();
	printf("\n");
}

