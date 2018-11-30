/*
   Model solution (verification)
   Task: hac
   Complexity: O(n)
   Author: Bartosz Kostka
*/

#include "bits/stdc++.h"

using namespace std;

const int MAXN = 500007;
const long long INF = 1LL<<60;

int n, tab[MAXN];
long long pref[MAXN], res[MAXN];

long long sum(int a, int b)
{
  long long res = 0;
  if(a <= b)
    res =  pref[b]-pref[a];
  else
    res = pref[n]-pref[a] + pref[b];
  return res;
}

bool insegment(int x, int a, int b)
{
  if(a < b)
    return a <= x and x < b;
  else
    return not(b <= x and x < a); 
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin >> n;
  int op = (n+1)/2;
  for(int i=1; i<=n; i++)
    cin >> tab[i]; 
  if(n==1)
  {
    cout << tab[1] << "\n";
    return 0;
  }
  for(int i=1; i<=n; i++)
    pref[i] = pref[i-1] + tab[i];
  long long ans = 0;
  for(int i=0; i<n; i++)
    res[i] = sum(i, (i+op)%n);

  deque <int> Q = {0};
  for(int i=1; i<op; i++)
  {
    while(!Q.empty() and res[i]<res[Q.back()])
      Q.pop_back();
    Q.push_back(i);
  }
  for(int i=op; i<op+n; i++)
  {
    ans = max(ans,res[Q.front()]);
    if((i-op)%n==Q.front())
      Q.pop_front();
    while(!Q.empty() and res[i%n]<res[Q.back()])
      Q.pop_back();
    Q.push_back(i%n);
  }
  cout << ans << "\n";
}

