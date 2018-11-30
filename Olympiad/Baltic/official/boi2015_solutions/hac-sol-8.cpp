/*
   Model solution (verification)
   Task: hac
   Complexity: O(n log n)
   Author: Bartosz Kostka
*/

#include "bits/stdc++.h"

using namespace std;

const int MAXN = 500007, DRZ = 524288;
const long long INF = 1LL<<60;

int n, tab[MAXN];
long long pref[MAXN], res[MAXN], drz[2*DRZ];

void change(int x, int y)
{
  x += DRZ;
  while(x)
  {
    drz[x] += y;
    x /= 2;
  }
}

long long sumdrz(int a, int b)
{
  a += DRZ; 
  b += DRZ;
  long long res = 0;
  while(a<b)
  {
    if(a%2)
      res += drz[a++];
    if(!(b%2))
      res += drz[b--];
    a /= 2;
    b /= 2;
  }
  if(a==b)
    res += drz[a];
  return res;
}

long long sum(int a, int b)
{
  if(a <= b)
    return sumdrz(a,b);
  else
    return sumdrz(0,b)+sumdrz(a,n-1);
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
  for(int i=0; i<n; i++)
  {
    cin >> tab[i]; 
    change(i,tab[i]);
  }
  long long ans = 0;
  for(int i=0; i<n; i++)
    res[i] = sum(i, (i+op-1)%n);

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

