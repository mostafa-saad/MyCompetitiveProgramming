/*
 * 1684_FREQUENT.cpp
 * Another buggy code by mostafa_saad
 *
 *  Created on: Jul 15, 2009
 */


#include<set>
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
#define repa(v)				repi(i, 0, sz(v)) repi(j, 0, sz(v[i]))
#define rep(i, v)			repi(i, 0, sz(v))
#define lp(i, cnt)			repi(i, 0, cnt)
#define lpi(i, s, cnt)		repi(i, s, cnt)
#define P(x)				cout<<#x<<" = { "<<x<<" }\n"
#define pb					push_back
#define MP					make_pair

typedef vector<int>       vi;
typedef vector<double>    vd;
typedef vector< vi >      vvi;
typedef vector< vd >      vvd;
typedef vector<string>    vs;
typedef long long         ll;
typedef long double   	  ld;

const int OO = (int)1e8;	//Small -> WRONG, Large -> OVERFLOW

const double PI  = acos(-1.0);
const double EPS = (1e-7);

int dcmp(double x, double y) {	return fabs(x-y) <= EPS ? 0 : x < y ? -1 : 1;	}


const int MIN_VAL = 100000;
const int MAX = 100000*2+9;	// 2^20
const int LOGMAX = 18;//1+log2(MAX)
int ind[MAX][LOGMAX];

int memo[MAX][LOGMAX];

int inp[MAX];
int freq[MAX];	// calculate the frequency of the elements in the range [0, i]
int A[MAX];		// A[i] is frequency of input in[i] in range [0, i]
int F[MAX];		// F[i] is the first time input in[i] appeared
int L[MAX];		// L[i] is the last time input in[i] appeared

int rmq(int i, int k) {
	if(k == 0)				return i;
	if(memo[i][k] != -1)	return memo[i][k];

    int idx1 = rmq(i, k-1);	// cover range (i, i+2^(k-1) -1)
    int idx2 = rmq(i + (1<<(k - 1)), k-1);

    return memo[i][k] = A[idx1] > A[idx2] ? idx1 : idx2;
}

int rmqQuery(int i, int j) {	// 0-based parameters
	if(j < i)	return 0;
	int k = (int)(log2(j-i+1) + 1e-8);
	return max( A[rmq(i, k)],  A[rmq(j-(1<<k)+1, k)] );
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("c.in", "rt", stdin);
#endif

	int n, q, val, s, e;

	while(true) {
		scanf("%d", &n);
		if(!n)	break;
		scanf("%d", &q);

		//read
		int mx = 0;
		lp(i, n) {
			scanf("%d", &inp[i]);
			inp[i] += MIN_VAL, mx = max(mx, inp[i]);
		}

		//Initialize
		int limit = 1+(int)( log2(mx) + 1e-8);
		lp(i, mx+1) {
			freq[i] = A[i] = 0, F[i] = L[i] = -1;
			lp(j, limit+1)	memo[i][j] = -1;
		}

		//precompute
		lp(i, n)
			val = inp[i], A[i] = ++freq[val], L[val] = i, F[val] = (F[val] == -1 ? i : F[val]);

		lp(i, q) {
			scanf("%d %d", &s, &e);
			s--, e--;
			if(s > e)	swap(s, e);
			// prepare the range to be valid for maximum range query, rearrange its start and end
			// so new range has elements did not appear before or after range
			int ans = 0;
			if(inp[s] == inp[e])
				ans = e-s+1;
			else {
				int mxe = min(e, L[inp[s]]);
				int mns = max(s, F[inp[e]]);
				ans = max( max(mxe - s + 1, e - mns + 1), rmqQuery(mxe+1, mns-1));
			}
			printf("%d\n", ans);

		}
	}


	return 0;
}
