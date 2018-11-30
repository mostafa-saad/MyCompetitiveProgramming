// Wojtek Nadara
// Rozwiązanie zakladajace, ze wszystkie operacje cofania sa rzedu 1
#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(0);
  int n;
  cin>>n;
  vector<int> stack;
  for (int i = 1; i <= n; i++) {
    int a;
    cin>>a;
    if (a < -1) {
      return 0;
    } else if (a == -1) {
      stack.pop_back();
    } else {
      stack.push_back(a);
    }
    if (stack.size()) {
      cout<<stack.back();
    } else {
      cout<<"0";
    }
    cout<<"\n";
  }
  return 0;
}