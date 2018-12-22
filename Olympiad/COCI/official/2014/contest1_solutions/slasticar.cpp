#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100100;
const int MAXM = 100100;
const int MAXL = 100100;
const int MAXNODES = 262150;
const int offset = 131072;
const int INF = 2000000000;

struct fenwick {
	int n, a[MAXN];	

	fenwick() {
		n = MAXN - 1;
		memset(a, 0, sizeof a);
	}
	
	void add(int index) {
		++index;
		for(; index <= n; index += index&-index) ++a[index];
	}
	
	int get(int l, int r) {
		int ret = 0;
		for(; l > 0; l -= l&-l) ret -= a[l];
		for(; r > 0; r -= r&-r) ret += a[r];
		return ret;
	}
};

int N, M;
char s[MAXN], w[MAXL];
int id[18][MAXN];
int suff_array[MAXN], pos[MAXN];
int mm[18][MAXN];
int ans[MAXM];
vector< pair<int, int> > bb[MAXM];
pair<int, int> found[MAXM];
fenwick F;

struct tournament {
	int tree[MAXNODES];
	int from, to;
	
	void init_tree(void) {
		for(int i = 0; i < N; ++i)
			tree[offset + i] = suff_array[i];
		for(int i = offset / 2; i > 0; i /= 2)
			for(int j = i; j < 2 * i; ++j)
				tree[j] = min(tree[2 * j], tree[2 * j + 1]);
	}
	
	int get_min(int t, int lo, int hi) {
		if(lo >= to || hi <= from) return INF;
		if(lo >= from && hi <= to) return tree[t];
		int mid = (lo + hi) / 2;
		return min(get_min(2 * t, lo, mid), get_min(2 * t + 1, mid, hi));
	}
	
	int get_min(int l, int r) {
		from = l; to = r;
		return get_min(1, 0, offset);
	}
} T;

struct cmp {
	int p;
	cmp(int _p) : p(_p) {}
	bool operator () (const int &a, const int &b) {
		if(id[p][a] != id[p][b]) return id[p][a] < id[p][b];
		if(p == 0) return 0;
		int na = a + (1 << p - 1), nb = b + (1 << p - 1);
		if(na >= N || nb >= N) return a > b;
		return id[p][na] < id[p][nb];
	}
};

void suffix_array(void) {
	for(int i = 0; i < N; ++i)
		suff_array[i] = i;
	
	for(int i = 0; i < N; ++i)
		id[0][i] = s[i] - '0';
	
	cmp C(0);
	
	sort(suff_array, suff_array + N, C);
	
	int curr = 0;
	
	for(int p = 1; p <= 17; ++p) {
		for(int i = 0; i < N; ++i) {
			if(i != 0 && C(suff_array[i - 1], suff_array[i])) ++curr;
			id[p][suff_array[i]] = curr;
		}		
		C.p = p;	
		sort(suff_array, suff_array + N, C);
	}	
	
	for(int i = 0; i < N; ++i) pos[suff_array[i]] = i;
}

pair<int, int> find(int l, int r, int p, char d) {
	pair<int, int> ret;
	int lo, hi, mid;
	lo = l; hi = r;
	while(lo < hi) {
		mid = (lo + hi) / 2;
		int x = suff_array[mid] + p;
		if(x < N && s[x] >= d) hi = mid; else lo = mid + 1;
	}
	ret.first = lo;
	lo = l; hi = r;
	while(lo < hi) {
		mid = (lo + hi) / 2;
		int x = suff_array[mid] + p;
		if(x >= N || s[x] <= d) lo = mid + 1; else hi = mid;
	}
	ret.second = lo;
	return ret;
}

int main(void) {

	scanf("%d", &N);
	scanf("%s", s);
	
	suffix_array();	
	T.init_tree();
		
	scanf("%d", &M);
	for(int i = 0; i < M; ++i) {
		scanf("%s", w);
		bb[i].resize(strlen(w));
		pair<int, int> curr(0, N);
		for(int j = 0; w[j] != '\0'; ++j) {
			curr = find(curr.first, curr.second, j, w[j]);
			bb[i][j] = curr;
		}
		if(curr.first == curr.second) found[i] = make_pair(N - 1, i);
			else found[i] = make_pair(T.get_min(curr.first, curr.second), i);
	}
	
	sort(found, found + M);
	
	int prev = 0;
	
	for(int i = 0; i < M; ++i) {
		int index = found[i].second;
		while(prev <= found[i].first) F.add(pos[prev++]);
		ans[index] += prev;
		for(int j = 0; j < bb[index].size(); ++j)
			ans[index] += F.get(bb[index][j].first, bb[index][j].second);
		if(bb[index].back().first != bb[index].back().second) --ans[index];
	}
	
	for(int i = 0; i < M; ++i) printf("%d\n", ans[i]);
	
	return 0;
	
}
