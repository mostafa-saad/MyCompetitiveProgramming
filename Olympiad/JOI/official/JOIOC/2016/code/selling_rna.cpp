#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

const int MAXN = 100000;
const int MAXM = 100000;
const int KIND_CHAR = 4;

struct segtree
{
	static const int DEPTH = 18;
	static const int N = 1 << DEPTH;
	int data[2 * N];

	void init()
	{
		for (int i = 0; i < 2 * N; ++i) data[i] = 0;
	}
	void append(int p, int v)
	{
		p += N;
		while (p) {
			data[p] += v;
			p >>= 1;
		}
	}
	int query(int L, int R)
	{
		int ret = 0;
		L += N; R += N;
		while (L < R) {
			if (L & 1) ret += data[L++];
			if (R & 1) ret += data[--R];
			L >>= 1; R >>= 1;
		}
		return ret;
	}
};
struct node
{
	node *next[KIND_CHAR];
	vector<int> val;
};

node pool[10000000]; int pLast = 0;

node *alloc()
{
	node *ret = &(pool[pLast++]);
	for (int i = 0; i < KIND_CHAR; ++i) ret->next[i] = nullptr;
	return ret;
}

int N, M;
string A[MAXN];
string P[MAXM], Q[MAXM];
char in[1010101];

node *trie, *trie_rev;

void append(node *nd, string &str, int v)
{
	for (int i = 0; i < str.size(); ++i) {
		int c = str[i];
		if (!nd->next[c]) nd->next[c] = alloc();
		nd = nd->next[c];
	}
	nd->val.push_back(v);
}

int px[MAXN], py[MAXN], leftx[MAXM], rightx[MAXM], lefty[MAXM], righty[MAXM];
int ret[MAXM];
segtree seg;

void visit(node *nd, int *idx, int *p, int *lf, int *rg)
{
	if (nd == nullptr) return;
	for (int v : nd->val) {
		if (v < 0) {
			v = ~v;
			lf[v] = *idx;
		}
	}
	for (int v : nd->val) {
		if (v >= 0) {
			p[v] = (*idx)++;
		}
	}
	for (int i = 0; i < KIND_CHAR; ++i) visit(nd->next[i], idx, p, lf, rg);
	for (int v : nd->val) {
		if (v < 0) {
			v = ~v;
			rg[v] = *idx;
		}
	}
}
int trans(char c)
{
	if (c == 'A') return 0;
	if (c == 'U') return 1;
	if (c == 'G') return 2;
	if (c == 'C') return 3;
}
struct action
{
	int pos;
	int type;
	int left, right;
	action(int pos = 0, int type = 0, int left = 0, int right = 0) : pos(pos), type(type), left(left), right(right){}
};
inline bool operator<(const action& a, const action& b)
{
	return a.pos < b.pos || (a.pos == b.pos && a.type < b.type);
}
int main()
{
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; ++i) {
		scanf("%s", in); A[i] = in;
		for (char& c : A[i]) c = trans(c);
	}
	for (int i = 0; i < M; ++i) {
		scanf("%s", in); P[i] = in;
		for (char& c : P[i]) c = trans(c);
		scanf("%s", in); Q[i] = in;
		for (char& c : Q[i]) c = trans(c);
	}
	trie = alloc(); trie_rev = alloc();
	for (int i = 0; i < N; ++i) {
		append(trie, A[i], i);
		reverse(A[i].begin(), A[i].end());
		append(trie_rev, A[i], i);
	}
	for (int i = 0; i < M; ++i) {
		append(trie, P[i], ~i);
		reverse(Q[i].begin(), Q[i].end());
		append(trie_rev, Q[i], ~i);
	}
	int idx = 0; visit(trie, &idx, px, leftx, rightx);
	idx = 0; visit(trie_rev, &idx, py, lefty, righty);
	for (int i = 0; i < M; ++i) ret[i] = 0;
	vector<action> v; const int INFT = 1000000;
	for (int i = 0; i < N; ++i) {
		v.push_back(action(px[i], INFT, py[i]));
	}
	for (int i = 0; i < M; ++i) {
		v.push_back(action(leftx[i], ~i, lefty[i], righty[i]));
		v.push_back(action(rightx[i], i, lefty[i], righty[i]));
	}
	sort(v.begin(), v.end());
	seg.init();
	for (action& a : v) {
		if (a.type == INFT) {
			seg.append(a.left, 1);
		} else if (a.type >= 0) {
			ret[a.type] += seg.query(a.left, a.right);
		} else {
			ret[~a.type] -= seg.query(a.left, a.right);
		}
	}
	for (int i = 0; i < M; ++i) printf("%d\n", ret[i]);
	return 0;
}
