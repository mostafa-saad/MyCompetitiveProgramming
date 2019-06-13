#include "Device.h"

#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

const int kMaxN = 250000;
const int kMaxDepth = 18;
const double kRatio = 1.05;

static vector<int> widths;

void InitDevice()
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

pair<int, int> range(long long code)
{
	int left = (int)(code / widths.size());
	int w = widths[(int)(code % widths.size())];
	return{ left, left + w };
}

int Answer(long long S, long long T)
{
	pair<int, int> X = range(S), Y = range(T);
	if (Y.first <= X.first && X.second <= Y.second) return 0;
	if (X.first <= Y.first && Y.second <= X.second) return 1;
	return 2;
}
