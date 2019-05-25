#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

char str[1505];
int len[1505], ds[1505];
int n, m;

int mark[15005];

int main(){
	cin >> n >> m;
	int ret = 0;
	for(int i=0; i<n; i++){
		scanf("%s",str);
		for(int j=0; j<m; j++) ds[j]++;
		for(int j=0; j<m; j++){
			if(str[j] == '1') len[j]++;
			else{
				mark[len[j]+1]++;
				len[j] = 0;
			}
		}
		int p = 0;
		for(int j=0; j<m; j++){
			if(mark[ds[j]]){
				mark[ds[j]]--;
			}
			else{
				ds[p] = ds[j];
				p++;
			}
		}
		for(int j=p; j<m; j++){
			ds[j] = 0;
		}
		for(int i=0; i<m; i++){
			ret = max(ret, (i+1) * ds[i]);
		}
	}
	cout << ret;
}