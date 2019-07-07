#include "cup.h"
#include<iostream>

using namespace std;

typedef long long ll;
const ll maxn=5e8;
ll x,y,tmp,tmp1;

bool same(int k)
{
  ll help=(((ll)1)<<33)-1-(((ll)1)<<k);
  return ((tmp&help)==(tmp1&help));
}

vector<int> find_cup()
{
  x=-maxn*2;
  tmp=ask_shahrasb(x,0);
  for(int i=0;i<=32;i++)
    {
      ll k=(((ll)1)<<i);
      if(x+k>2*maxn)
        break;
      tmp1=ask_shahrasb(x+k,0);
      if(tmp==0 && tmp1==0)
	{
	  y=k/2;
	  break;
	}
      if(same(i)) 
	y+=k^(k&tmp);
      else
	y+=(k&tmp);
      if(tmp&k) 
	{
	  x+=k;
	  tmp=tmp1;
	}
    }
  if(ask_shahrasb(x+y,y)==0) return vector<int>({x+y,y});
  else return vector<int>({x+y,-y});
}
