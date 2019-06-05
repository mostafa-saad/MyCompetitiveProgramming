#include "Joi.h"

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

static const int NMAX = 10000;
static const int BITS = 60;

namespace {
vector<int> tree[NMAX];
int N;

int union_find[NMAX];
int root(int p)
{
	return union_find[p] < 0 ? p : (union_find[p] = root(union_find[p]));
}
bool join(int p, int q)
{
	p = root(p);
	q = root(q);
	if (p == q) return false;
	union_find[p] += union_find[q];
	union_find[q] = p;
	return true;
}
void SpanningTree(int M, int A[], int B[]) {
	fill(union_find, union_find + N, -1);
	for (int i = 0; i < M; ++i) {
		if (join(A[i], B[i])) {
			tree[A[i]].push_back(B[i]);
			tree[B[i]].push_back(A[i]);
		}
	}
	for (int i = 0; i < N; ++i) sort(tree[i].begin(), tree[i].end());
}

bool HasEdge(int u, int v) {
	return binary_search(tree[u].begin(), tree[u].end(), v);
}

vector<int> subtree[NMAX];
int idx[NMAX];

void InitialSubtree(int p, int rt, vector<int> &sto)
{
	if (sto.size() >= BITS) return;
	idx[p] = sto.size();
	sto.push_back(p);
	for (int q : tree[p]) if (q != rt) {
		InitialSubtree(q, p, sto);
	}
}
void ComputeSubtrees(int p, int rt, vector<pair<int, int> > sub)
{
	bool has = false;
	for (auto v : sub) if (v.first == p) has = true;

	if (!has) {
		int purge = -1;
		for (int i = 0; i < sub.size(); ++i) {
			if (sub[i].second == 1 && sub[i].first != rt) {
				purge = i;
				break;
			}
		}
		for (int i = 0; i < sub.size(); ++i) {
			if (HasEdge(sub[i].first, sub[purge].first)) {
				--sub[i].second;
			}
		}
		idx[p] = idx[sub[purge].first];
		sub[purge] = make_pair(p, 1);
		for (int i = 0; i < sub.size(); ++i) {
			if (sub[i].first == rt) {
				++sub[i].second;
			}
		}
	}

	for (auto v : sub) subtree[p].push_back(v.first);
	for (int q : tree[p]) if (q != rt) {
		ComputeSubtrees(q, p, sub);
	}
}
void CommonProc(int N_, int M, int A[], int B[]) {
	N = N_;
	SpanningTree(M, A, B);

	vector<int> tree;
	InitialSubtree(0, -1, tree);

	vector<pair<int, int> > tree_deg;
	for (int i = 0; i < tree.size(); ++i) {
		int deg = 0;
		for (int j = 0; j < tree.size(); ++j) {
			if (HasEdge(tree[i], tree[j])) ++deg;
		}
		tree_deg.push_back({ tree[i], deg });
	}
	ComputeSubtrees(0, -1, tree_deg);
}
}
void Joi(int N_, int M, int A[], int B[], long long X, int T) {
	CommonProc(N_, M, A, B);

	for (int i = 0; i < N; ++i) {
		MessageBoard(i, (int)((X >> idx[i]) & 1));
	}
}
