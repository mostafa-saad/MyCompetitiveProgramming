#include<iostream>
#include<algorithm>

using namespace std;
typedef long long Int;
Int n, t, k;
Int x[108000];
Int X[108000];
bool dp[2][108000];
Int cnt;

bool check(Int v){
  for(Int i = 0;i < n;i++)X[i] = x[i] - 2 * v * t * i;

  Int gl = k, gr = k;
  for(Int i = k;i >= 0;i--){
    if(X[gl] <= X[i])gl = i;
  }
  for(Int i = k;i < n;i++){
    if(X[gr] >= X[i])gr = i;
  }


  Int l = k, r = k;
  while(true){
    bool change = false;
    Int nl = l;
    while(true){
      if(nl - 1 >= gl && X[nl - 1] >= X[r])nl--;
      else break;
      if(X[nl] >= X[l] || nl == gl)break;
    }
    if(X[nl] >= X[l] && l != nl){
      l = nl;
      change = true;
    }

    Int nr = r;
    while(true){
      if(nr + 1 <= gr && X[nr + 1] <= X[l])nr++;
      else break;
      if(X[nr] <= X[r] || nr == gr)break;
    }
    if(X[nr] <= X[r] && r != nr){
      r = nr;
      change = true;
    }
    if(!change)break;
  }


  if(l != gl || r != gr)return false;

  l = 0;
  r = n-1;
  
  if(X[l] < X[r])return false;
  while(true){
    bool change = false;
    
    Int nl = l;
    while(true){
      if(nl + 1 <= gl && X[nl + 1] >= X[r])nl++;
      else break;
      if(X[nl] >= X[l] || nl == gl)break;
    }
    if(X[nl] >= X[l] && nl != l){
      l = nl;
      change = true;
    }

    Int nr = r;
    while(true){
      if(nr - 1 >= gr && X[nr - 1] <= X[l])nr--;
      else break;
      if(X[nr] <= X[r] || nr == gr)break;
    }
    if(X[nr] <= X[r] && nr != r){
      r = nr;
      change = true;
    }

    if(!change)break;
  }
 
  return (r == gr && l == gl);
}

int main(){
  cin >> n >> k >> t;
  k--;
  for(Int i = 0;i < n;i++){
    cin >> x[i];
  }

  bool same_check = true;
  for(int i = 0;i < n;i++){
    if(x[i] != x[0])same_check = false;
  }
  if(same_check){
    cout << 0 << endl;
    return 0;
  }
  
  Int bottom = 0, top = x[n-1];

  while(top - bottom > 1){
    Int mid = (top + bottom) / 2;
    if(check(mid))top = mid;
    else bottom = mid;
  }
  cout << top << endl;
  return 0;
}
