#include "Encoder.h"

#include <vector>
using namespace std;

const int kMaxN = 250000;
const int kMaxDepth = 18;
const double kRatio = 1.05;

static vector<int> graph[kMaxN];
static vector<int> widths;

static int lf[kMaxN], rg[kMaxN], last_id;

void SetWidths()
{
	int w = 1;
	widths.push_back((int)w);
	int times = kMaxDepth + 1;
	while (times > 0) {
		int w2 = w * kRatio;
		if (w == w2) ++w2;
		widths.push_back(w2);
		if (w2 > kMaxN) {
			--times;
		}
		w = w2;
	}
}

int ceiling(int w)
{
	return *(lower_bound(widths.begin(), widths.end(), w));
}

void visit(int p, int rt)
{
	lf[p] = last_id++;
	for (int q : graph[p]) if (q != rt) {
		visit(q, p);
	}
	rg[p] = last_id = lf[p] + ceiling(last_id - lf[p]);
}

void Encode(int N, int A[], int B[])
{
	SetWidths();
	for (int i = 0; i < N - 1; ++i) {
		graph[A[i]].push_back(B[i]);
		graph[B[i]].push_back(A[i]);
	}
	last_id = 0;
	visit(0, -1);
	for (int i = 0; i < N; ++i) {
		int wc = lower_bound(widths.begin(), widths.end(), rg[i] - lf[i]) - widths.begin();
		long long code = (long long)lf[i] * widths.size() + wc;
		Code(i, code);
	}
}
