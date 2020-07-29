// SPOJ FSEQ
// This problem id from 10th Egyptian Collegiate Programming Contest (ECPC 2011)
// Author and chief judge is Mostafa Saad Ibrahim
// This solution is based on segment tree. However, naturally, 
// most people handle "next greater element" part using a simple datastructures such as Stack or Prioirty Queue

// For priority based solution, 
	// https://github.com/yelghareeb/problem_solving/blob/master/SPOJ/SPOJ%20FSEQ.cpp
	// https://github.com/BRAINOOOO/CompetitiveProgramming/blob/dd02ff8e60a2e238e61e6a4421aec2338e3f39a8/Spoj/SPOJ%20FSEQ.Cpp
	
// For stack explantation for "next greater element", See: http://www.geeksforgeeks.org/next-greater-element/
		https://github.com/mostafa-saad/ArabicCompetitiveProgramming/blob/master/18-Programming-4kids/16_homework_09_answer.cpp
		https://ideone.com/zfXDVU
		
// Others:
	// https://github.com/abdullaAshraf/Problem-Solving/blob/master/SPOJ/FSEQ

// The first equation is not given in a straightforward way.
// Then naturally you should try to arrange in a better format, or even simulate and detect the pattern
// You will notice it is just Fibonacci. Without this point, you will face lots of diffculities

// F[n] 	= F[n-2]+(F[n-3]+..F[1]+1)
// F[n-1] 	= F[n-3]+F[n-4]+..F[1]+1 by replacement
// F[n] 	= F[n-2]+F[n-1] which is Fibonacci sequence when F[0] = 0, F[1] = 1
// Under % M, F[n] is very intersting. It doesn't have a pre-cycle (why?)
// Excersie: Assume we did not inform the max cylic length for it, can you compute an upper bound?
	// I decided to inform about limit, to make it easier
// Given that fib only depends on last 2 elements, detecting the cycle is trivial

// Now, we built the array. It will be simply the cycle doubled
// E.g. if cycle is 2 5 7, then we have array 2 5 7 2 5 7
// We need for first n elements, the next greater element
// This is not a hard part. However, if want to avoid thinking
// Just implement a segment tree: querey is range, value and find first position > value

// Last part is trivial, we need to compute length of each position. This is a simple linear DP

// Overall, this is an example problem = combinations of easy sub-problems. One can decompose and tackle each part reasonably


#include<cassert>
#include<map>
#include<list>
#include<iomanip>
#include<cmath>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<complex>
#include<sstream>
#include<iostream>
#include<algorithm>
#include<stdio.h>
using namespace std;

#define all(v)				((v).begin()), ((v).end())
#define sz(v)				((int)((v).size()))
#define clr(v, d)			memset(v, d, sizeof(v))
#define repi(i, j, n) 		for(int i=(j);i<(int)(n);++i)
#define repd(i, j, n) 		for(int i=(j);i>=(int)(n);--i)
#define rep(i, v)			repi(i, 0, sz(v))
#define lp(i, cnt)			repi(i, 0, cnt)
#define lpi(i, s, cnt)		repi(i, s, cnt)

typedef long long ll;

double diffclock(clock_t clock1, clock_t clock2) {
	double diffticks = clock1 - clock2;
	double diffms = (diffticks * 1000) / CLOCKS_PER_SEC;
	return diffms;
}

const int TREE_SIZE = 2 * 262144;
int interval[TREE_SIZE + 9];

const int MAX_M = 100000;
const int MAX_SLEN = 100000;
const int MAX_TERMS = 45;

int seq[2 * MAX_SLEN];
int nextInc[MAX_SLEN + 9];
int idx;
int from, to, bound;

int len[MAX_SLEN + 9];


//segment tree to find next element for me with value > than me
int build(int s, int e, int p) {
	if (s == e)
		return interval[p] = s;

	int a = build(s, (s + e) / 2, 2 * p);
	int b = build((s + e) / 2 + 1, e, 2 * p + 1);

	return interval[p] = seq[a] > seq[b] ? a : b;
}

// find first value in range > bound
int upperBound(int s, int e, int p) {
	if (from <= s && to >= e) {
		if (bound >= seq[interval[p]])
			return -1; // bad interval
	}

	if (s == e)
		return interval[p];

	int mid = (s + e) / 2;

	if (to <= mid)
		return upperBound(s, (s + e) / 2, 2 * p);
	if (from > mid)
		return upperBound((s + e) / 2 + 1, e, 2 * p + 1);

	int a = upperBound(s, (s + e) / 2, 2 * p);
	if (a != -1)
		return a;
	return upperBound((s + e) / 2 + 1, e, 2 * p + 1);
}

void generateSeq(ll M) {
	ll a = 0 % M, b = 1 % M, c;
	ll ia = a, ib = b;

	seq[1] = a, seq[2] = b, idx = 3;

	for (int i = 3;; ++i) {
		c = (a + b) % M, a = b, b = c;
		seq[idx++] = c;
		if (a == ia && b == ib)
			break;

	}
	idx -= 3;
	assert(idx <= MAX_SLEN);
}


void generateSeq_TESTREPETATION(ll M, bool print = 1) {
	ll a = 0 % M, b = 1 % M;
	ll ia = a, ib = b;
	map<pair<int, int> , int> vis;
	vis[make_pair(a, b)] = 2;

	for (int i = 3;; ++i) {
		ll c = (a + b) % M;
		a = b, b = c;
		pair<int, int> p = make_pair(a, b);
		if (vis.count(p) == 0)
			vis[p] = i;
		else {
			assert(a == ia && b == ib);
			return;
		}
	}
}

int getLen(int i) {
	if (nextInc[i] == -1)
		return 1;

	if (len[i] != -1)
		return len[i];

	return len[i] = 1 + getLen(nextInc[i]);
}

int main() {

	clock_t begin = clock();


	int cases;
	scanf("%d", &cases);
	int M;
	int max_m = -1, max_t = -1, max_n = -1;

	lp(cc, cases) {
		printf("Case %d: ", cc + 1);
		scanf("%d", &M);
		max_m = max(max_m, M);

		assert(M <= MAX_M);

		generateSeq(M);
		//generateSeq_TESTREPETATION(M);

		int n = idx;
		max_n = max(n, max_n);
		assert(n <= MAX_SLEN);

		for (int i = n + 1; i <= 2 * n; ++i)
			seq[i] = seq[i - n]; // one cycle

		build(1, 2 * n, 1);

		for (int i = 1; i <= n; ++i) {
			from = i + 1, to = 2 * n, bound = seq[i];
			nextInc[i] = upperBound(1, 2 * n, 1);
			if (nextInc[i] > n)
				nextInc[i] -= n;
		}

		memset(len, -1, (n + 1) * sizeof(int));

		int sum = 0;
		for (int i = 1; i <= n; ++i) {
			sum += getLen(i);
			max_t = max(max_t, getLen(i));
		}
		printf("%d\n", sum);
	}

	cin>>ws;
	assert(cin.eof());

	cerr << max_m << " max_t " << max_t << " max_n " << max_n << "\n";

	clock_t end = clock();
	//cerr << "Time elapsed: " << double(diffclock(end, begin)) << " ms" << endl;
	
	return 0;
}
