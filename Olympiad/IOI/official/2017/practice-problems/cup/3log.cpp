#include "cup.h"
#include<iostream>

using namespace std;

const int maxn=1e9;
int x,ans,tmp;
bool mark1,mark2;

int f(int y)
{
  int ret=1;
  while(!(y&ret))
    ret*=2;
  return ret;
}

void print(int y)
{
  for(int i=31;i>-1;i--)
    cout<<((y>>i)&1);
  cout<<" ";
}

vector<int> find_cup()
{
  x=-maxn*2;
  while(tmp=ask_shahrasb(x,0),tmp!=0)
    x+=f(tmp);
  if(x<2*maxn)
    mark1=(ask_shahrasb(x+1,1)==0);
  else
    mark1=(ask_shahrasb(x-1,-1)==0);
  if(x<2*maxn)
    mark2=(ask_shahrasb(x+1,-1)==0);
  else
    mark2=(ask_shahrasb(x-1,1)==0);
  if(mark1 && mark2)
	  return vector<int>({x, 0});
  ans=x;
  x++;  
  while(tmp=ask_shahrasb(x,0),tmp!=0)
      x+=f(tmp);
  if(mark1) return vector<int>({(x+ans)/2,(x-ans)/2});
  else	return vector<int>({(x+ans)/2,-(x-ans)/2});
}
