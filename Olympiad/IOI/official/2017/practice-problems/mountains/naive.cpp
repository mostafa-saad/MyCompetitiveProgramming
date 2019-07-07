#include<iostream>
#include<algorithm>
#include "mountains.h"

using namespace std;

const int MAXN=100;
long long h[MAXN];
int n,ans;
bool mark[MAXN][MAXN];

long long cross(int i,int j,int k)
{
  return (j-i)*(h[k]-h[i])-(h[j]-h[i])*(k-i);
}

int maximum_deevs(vector<int> y)
{
  int n = y.size();
  for(int i=0;i<n;i++)
    h[i]=y[i];
  for(int i=0;i<n;i++)
    for(int j=i+1;j<n;j++)
      {
	mark[i][j]=true;
	for(int k=i+1;k<j;k++)
	  if(cross(i,j,k)>0)
	    mark[i][j]=false;
      }
  for(int i=0;i<(1<<n);i++)
    {
      bool mark1=true;
      for(int j=0;j<n;j++)
	for(int k=j+1;k<n;k++)
	  if(mark[j][k] && ((i>>j)&1) && ((i>>k)&1))
	    mark1=false;
      if(mark1)
	ans=max(ans,__builtin_popcount(i));
    }
  return ans;
}
