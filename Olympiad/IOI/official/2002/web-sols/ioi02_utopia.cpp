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
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, a[10005], b[10005];
bool s1[10005], s2[10005];

int ret1[10005], ret2[10005];
int tsgn[10005];

void solve(int *arr, bool *sgn, int *ret){
	int pos = 0;
	for(int i=0; i<n-1; i++){
		if(sgn[i] == sgn[i+1]) pos++;
	}
	int is = pos, ie = pos;
	tsgn[pos] = (sgn[0] ? -1 : 1);
	ret[0] = tsgn[pos] * arr[pos];
	for(int i=1; i<n; i++){
		if(sgn[i] == sgn[i-1]){
			is--;
			tsgn[is] = tsgn[is+1] * -1;
			ret[i] = tsgn[is] * arr[is];
		}
		else{
			ie++;
			tsgn[ie] = tsgn[ie-1] * -1;
			ret[i] = tsgn[ie] * arr[ie];
		}
	}
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i],&b[i]);
	}
	sort(a,a+n);
	sort(b,b+n);
	for(int i=0; i<n; i++){
		int t;
		scanf("%d",&t);
		if(t == 2){
			s1[i] = 1;
		}
		if(t == 3){
			s1[i] = 1;
			s2[i] = 1;
		}
		if(t == 4){
			s2[i] = 1;
		}
	}
	solve(a, s1, ret1);
	solve(b, s2, ret2);
	for(int i=0; i<n; i++){
		printf("%c%d ",ret1[i] > 0 ? '+' : '-',abs(ret1[i]));
		printf("%c%d\n",ret2[i] > 0 ? '+' : '-',abs(ret2[i]));
	}

}