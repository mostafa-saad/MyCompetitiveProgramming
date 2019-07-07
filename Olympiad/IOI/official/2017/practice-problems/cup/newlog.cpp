#include "cup.h"
#include<iostream>

using namespace std;

typedef long long ll;
const ll maxn=5e8;
ll x,tmp,tmp1;

bool same(int k)
{
  ll help=(((ll)1)<<33)-1-(((ll)1)<<k);
  return ((tmp&help)==(tmp1&help));
}

ll f(ll k)
{
  for(int i=33;i>-1;i--)
    if((k>>i)&1)
      return (((ll)1)<<i);
}

vector<int> find_cup()
{
  tmp=ask_shahrasb(-2*maxn,-maxn);
  for(int i=0;i<=32;i++)
    {
      ll k=(((ll)1)<<i);
      tmp1=ask_shahrasb(-2*maxn+k,-maxn);
      if(same(i))
	  x+=k;
    }
  if(-2*maxn+x>maxn)
    x-=f(x);
  return vector<int>({-2*maxn+x,-maxn+(tmp^x)});
}
