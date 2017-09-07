// Coach wahav
// RMQ + Divide and conquer (min value is bottleneck)

#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;
const int MAXN = 100002;
typedef long long ll;
int Log[MAXN];
ll stable[MAXN][17]; // sparse table
ll arr[MAXN];
int n;

void build(){
  int cnt = -1;
  for(int i = 0; i < n; i++){
    if(!((i+1)&i)) cnt++;
    stable[i][0] = i;
    Log[i+1] = cnt;
  }
  for(int j = 1; (1<<j) <= n; j++){
    for(int i = 0; (i+(1<<j)) <= n; i++){
      int a = stable[i][j-1];
      int b = stable[i + (1<<(j-1))][j-1];
      stable[i][j] = ((arr[a]<arr[b])?a:b);
    }
  }
}

int getMin(int st, int en){
  int L = Log[en-st+1];
  int a = stable[st][L], b = stable[en-(1<<L)+1][L];
  return ((arr[a]<arr[b])?a:b);
}
ll divideAndConquer(int st, int en){
  if(st == en) return arr[st];
  if(st > en) return 0;
  int mnIdx = getMin(st,en);
  ll ret = arr[mnIdx]*(en-st+1LL);
  ret = max(ret, max(divideAndConquer(st,mnIdx-1), divideAndConquer(mnIdx+1,en)));
  return ret;
}

int main() {
	std::ios_base::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
 freopen("in.txt","rt",stdin);
// freopen("out.txt","wt",stdout);
#endif
 while(cin >> n, n){
   for(int i = 0; i < n; i++){
     cin >> arr[i];
   }
   build();
   cout << divideAndConquer(0,n-1) << endl;
 }
	
	return 0;
}
