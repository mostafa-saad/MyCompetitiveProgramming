#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

// takes 10 hours to execute (in my mbp mid-2013). patience!

const int mod = 1234567;

int dp2[33][550][550];
int dp1[33][33][550];
int dp3[33][33][550][550];

void update(int a, int b, int c){
	for(int i=0; i+a <= 31; i++){ // a
		for(int k=0; k<=(i+a+1) * (i+a+2)/2; k++){ // d
			dp3[i][a][c][k] += 1ll * dp2[a][b][c] * dp1[i][a][k-b] % mod;
			dp3[i][a][c][k] %= mod;
		}
	}
}

int main(){
	dp1[0][0][0] = 1;
	for(int i=0; i<=32; i++){
		for(int j=0; j<=32; j++){
			for(int k=0; k<=528; k++){
				if(i) dp1[i][j][k] += dp1[i-1][j][k];
				if(j && k-i>=0) dp1[i][j][k] += dp1[i][j-1][k-i];
				dp1[i][j][k] %= mod;
			}
		}
	}
	dp2[0][0][0] = 1;
	update(0, 0, 0);
	for(int i=1; i<=31; i++){
		for(int j=0; j<=i*(i+1)/2; j++){
			for(int k=0; k<=i*(i-1)/2; k++){
				for(int a=0; a<=i-1; a++){
					for(int b=0; b<=j-a-1; b++){
						for(int c=0; c<=k-i+1; c++){
							dp2[i][j][k] += 1ll * dp2[a][b][c] * dp3[a][i-a-1][k-c-i+1][j-b-a-1] % mod;
							dp2[i][j][k] %= mod;
						}
					}
				}
				update(i, j, k);
			}
		}
	}
	pi a[10] = {{5, 1}, {12, 2}, {18, 3}, {20, 1}, {22, 5}, {23, 3}, {24, 4}, {29, 2}, {30, 5}, {31, 1}};
	for(int i=0; i<10; i++){
		int n = a[i].first;
		int x = a[i].second;
		int ret = 0;
		for(int i=0; i<=n*(n+1)/2; i++){
			for(int j=0; j<=x*i && j <= n*(n+1)/2; j++){
				ret += dp2[n][j+1][i];
				ret %= mod;
			}
		}
		cout << ret << endl;
	}
}