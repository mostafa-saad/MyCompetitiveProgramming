/*
	COCI 2012/13, Round 1, task SNAGA
	Author: Adrian Satja Kurdija

	ALTERNATIVE SOLUTION.
	Using some math, we can show that strength(n) = 3, except for the
	following (pairwise disjoint) arithmetic progressions
	(intial term is denoted by a, and the common difference by d):

	i) a = 3, d = 2 (progression 3, 5, 7, 9, ...) --> strength(n) = 2
	ii) a = 6, d = 12 (progression 6, 18, 30, ...) --> strength(n) = 4
	iii) a = 420, d = 840 (progression 420, 1260, ...) --> strength(n) = 4
	iv) a = 360360, d = 2*360360 --> strength(n) = 4
	v) a = 72201776446800, d = 2*72201776446800 --> strength(n) = 4

	There is more of them, but with too large terms.
*/

#include<iostream>
using namespace std;

long long count(long long N, long long a, long long d) {
	return ((N -= a) < 0? 0 : 1 + N/d);
}

int main()
{
	long long a[5] = {3, 6, 420, 360360, 72201776446800LL};
	long long d[5] = {2};
	long long strength[5] = {2};

	for (int i = 1; i < 5; i++) {
		d[i] = 2 * a[i];
		strength[i] = 4;
	}

	long long A, B, solution = 0;
	cin >> A >> B;
	long long remaining = B - A + 1;

	for (int i = 0; i < 5; i++) {
		// How many terms of i-th arithmetic progression
		// is between A and B?
		long long how_much = count(B, a[i], d[i]) - count(A-1, a[i], d[i]);
		solution += strength[i] * how_much;
		remaining -= how_much;
	}
	cout << solution + 3 * remaining << endl;
}
