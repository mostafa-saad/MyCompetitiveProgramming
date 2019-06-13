#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
typedef long long Int;
typedef pair<Int, Int> P;
typedef pair<Int, P> T;

bool used[2222];
Int v[2222][2222];
Int a[2222];
Int sum[2222];
vector<T> ans;
vector<T> split[2222];


//compare two mixed  fractions.
//returns a < b
bool small(T a, T b){
  if(a.first < b.first)return true;
  if(a.first > b.first)return false;
  return a.second.first * b.second.second < a.second.second * b.second.first;
}

//greatest common divisor
Int gcd(Int a, Int b){
  if(a == 0)return b;
  return gcd(b % a, a);
}

//c + a / b
T make_frac(Int c, Int a, Int b){
  Int g = gcd(a , b);
  return T(c, P(a / g, b / g));
}

int main(){
  Int n, l;
  
  cin >> n >> l;
  for(int i = 0;i < n;i++){
    for(int j = 0;j < l;j++){
      cin >> v[i][j];
      sum[i] += v[i][j];
    }
  }

  for(int i = 0;i < n;i++){
    Int acum = 0;
    Int p = 0;
    for(int j = 1;j <= n-1;j++){
      while((acum + v[i][p]) * n <= sum[i] * j)acum += v[i][p++];
      Int rest = sum[i]*j - acum*n;
      split[i].push_back(make_frac(p, rest, n * v[i][p]));      
    }
    split[i].push_back(T(l, P(0, 1)));
  }

  for(int i = 0;i < n;i++){
    Int nxt = -1;
    for(int j = 0;j < n;j++){
      if(used[j])continue;
      if(nxt == -1 || small(split[j][i], split[nxt][i]))nxt = j;
    }
    used[nxt] = true;
    a[i] = nxt;
    ans.push_back(split[nxt][i]);
  }

  for(int i = 0;i < n-1;i++){
    cout << ans[i].first*ans[i].second.second + ans[i].second.first << " " << ans[i].second.second << endl;
  }
  for(int i = 0;i < n;i++){
    if(i)cout << " ";
    cout << a[i]+1;
  }cout << endl;
  return 0;
}
