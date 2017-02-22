/*
 * 3194.cpp
 * Another buggy code by mostafa_saad
 *
 *  Created on: Aug 15, 2009
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

typedef vector<int> vi;
typedef vector<double> vd;
typedef vector<vi> vvi;
typedef vector<vd> vvd;
typedef vector<string> vs;
typedef long long ll;
typedef long double ld;

const int OO = (int) 1e8; //Small -> WRONG, Large -> OVERFLOW

const double PI = acos(-1.0);
const double EPS = (1e-7);

int dcmp(double x, double y) {
	return fabs(x - y) <= EPS ? 0 : x < y ? -1 : 1;
}

int pp[18] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59,
		61 };

vector<ll> factorization(ll n) {

	vector<ll> powers;

	for (ll d = 1, i = 2; i * i <= n; i += d, d = 2)
		while (n % i == 0)
			powers.push_back(i), n /= i;

	if (n > 1)
		powers.push_back(n);

	return powers;
}

string ans[64];

void generate() {
	lp(k, 18) {
		int i = pp[k];

		vector<ll> ans = factorization((1LL << i) - 1);
		if (ans.size() > 1) {
			cout << "ans[" << i << "] = \"";

			rep(j, ans) {
				if (j)
					cout << "* ";
				cout << ans[j] << " ";
			}
			cout << "= " << (1ll << i) - 1 << " = ( 2 ^ " << i
					<< " ) - 1\";\n" << flush;
		}

	}
}

int main() {
	freopen("c.in", "rt", stdin);

	//generate();


	ans[11] = "23 * 89 = 2047 = ( 2 ^ 11 ) - 1";
	ans[23] = "47 * 178481 = 8388607 = ( 2 ^ 23 ) - 1";
	ans[29] = "233 * 1103 * 2089 = 536870911 = ( 2 ^ 29 ) - 1";
	ans[37] = "223 * 616318177 = 137438953471 = ( 2 ^ 37 ) - 1";
	ans[41] = "13367 * 164511353 = 2199023255551 = ( 2 ^ 41 ) - 1";
	ans[43] = "431 * 9719 * 2099863 = 8796093022207 = ( 2 ^ 43 ) - 1";
	ans[47] = "2351 * 4513 * 13264529 = 140737488355327 = ( 2 ^ 47 ) - 1";
	ans[53] = "6361 * 69431 * 20394401 = 9007199254740991 = ( 2 ^ 53 ) - 1";
	ans[59] = "179951 * 3203431780337 = 576460752303423487 = ( 2 ^ 59 ) - 1";


	int cases;
	cin>>cases;


	lp(cc, cases) {
		if(cc)	cout<<"\n";

		int n;
		cin>>n;

		for (int i = 0; i < n; ++i) {
			if(ans[i] != "")
				cout<<ans[i]<<"\n";
		}
	}

	return 0;
}
