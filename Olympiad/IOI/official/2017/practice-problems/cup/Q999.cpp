#include "cup.h"
#include <iostream>

using namespace std;

typedef long long ll;
const ll maxn=5e8;
ll x,tmp,tmp1,y;

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
  return 0;
}

vector<int> find_cup()
{
  int Q = 999;
  for (int i=32; i<Q; i++)
    tmp=tmp^ask_shahrasb(0,0);
  x=y=tmp1=tmp^tmp;
  tmp=ask_shahrasb(-2*maxn,-maxn);
  for(int i=0;i<31;i++)
    {
      ll k=(((ll)1)<<i);
      tmp1=ask_shahrasb(-2*maxn+k,-maxn);
      if(same(i))
	y+=k^(tmp&k);
      else
	y+=(tmp&k);
    }
  x=y^tmp;
  if(-2*maxn+x>maxn)
    x-=f(x);
  vector<int> res(1, (int)(-2*maxn+x));
  res.push_back((int)(-maxn+(tmp^x)));
  return res;
}
