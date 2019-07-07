#include "cup.h"
#include<iostream>

using namespace std;

typedef long long ll;
const ll maxn=1e9;
ll x,ans,tmp;

ll f(ll y)
{
  ll ret=1;
  while(!(y&ret))
    ret*=2;
  return ret;
}

vector<int> find_cup()
{
  x=-maxn*2;
  while(tmp=ask_shahrasb(x,0),tmp!=0)
      x+=f(tmp);
  ans=x;
  x=2*maxn;  
  while(tmp=ask_shahrasb(x,0),tmp!=0)
      x-=f(tmp);
  if(ask_shahrasb((x+ans)/2,(x-ans)/2)==0)
  	return vector<int>({(x+ans)/2,(x-ans)/2});
  return vector<int>({(x+ans)/2,-(x-ans)/2});
}
