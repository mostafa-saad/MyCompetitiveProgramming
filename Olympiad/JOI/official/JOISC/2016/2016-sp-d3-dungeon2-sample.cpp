#include "dungeon2.h"

#include <vector>
#include <cstdio>

using namespace std;

const int MAX_N = 250;

vector<int> con[MAX_N];
int id;

int Visit1(int rt)
{
	if (Color() != 1) {
		int n = Color();
		Move(LastRoad(), n);
		return -n;
	}

	int p = id++;
	int last = LastRoad() - 1;
	int deg = NumberOfRoads();
	for (int i = 0; i < deg; ++i) {
		if (i != last) {
			Move(i + 1, 2);
			int t = Visit1(p);
			if (t == -2) {
				con[p].push_back(1000);
			} else if (t == -3) {
				con[p].push_back(-1);
			} else {
				con[p].push_back(t);
			}
		} else {
			con[p].push_back(-1);
		}
	}

	if (rt != -1) {
		Move(last + 1, 3);
	}
	return p;
}

vector<int> S;

void Visit2(int p, int rt, int power3)
{
	int depth = S.size();
	S.push_back(p);

	int label = (depth / power3) % 3 + 1;
	int last = LastRoad() - 1;
	for (int i = 0; i < con[p].size(); ++i) {
		int q = con[p][i];
		if (q == -1) continue;
		if (q >= 1000) {
			Move(i + 1, label);
			con[p][i] += power3 * (Color() - 1);
			if (power3 == 1) {
				con[p][i] = S[con[p][i] - 1000];
			}
			Move(LastRoad(), Color());
		} else {
			Move(i + 1, label);
			Visit2(q, p, power3);
		}
	}

	S.pop_back();
	if (rt != -1) {
		Move(last + 1, 1);
	}
}

int wf[MAX_N][MAX_N];
int ans[MAX_N + 1];

void Inspect(int R)
{
	id = 0;
	Visit1(-1);
	Visit2(0, -1, 81);
	Visit2(0, -1, 27);
	Visit2(0, -1, 9);
	Visit2(0, -1, 3);
	Visit2(0, -1, 1);

	for (int i = 0; i < id; ++i) {
		for (int j = 0; j < id; ++j) wf[i][j] = (i == j ? 0 : (id + 1));
	}
	for (int i = 0; i < id; ++i) {
		for (int j : con[i]) if (j != -1) wf[i][j] = wf[j][i] = 1;
	}
	for (int i = 0; i < id; ++i) {
		for (int j = 0; j < id; ++j) {
			for (int k = 0; k < id; ++k) wf[j][k] = min(wf[j][k], wf[j][i] + wf[i][k]);
		}
	}
	for (int i = 1; i <= R; ++i) ans[i] = 0;
	for (int i = 0; i < id; ++i) {
		for (int j = i + 1; j < id; ++j) {
			if (1 <= wf[i][j] && wf[i][j] <= R) ++ans[wf[i][j]];
		}
	}
	for (int i = 1; i <= R; ++i) Answer(i, ans[i]);
}
