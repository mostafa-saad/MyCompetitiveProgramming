#include<iostream>
#include<algorithm>
#include "mountains.h"

using namespace std;

const int MAXN=5000;
long long h[MAXN];
int n,ans,dp[MAXN][MAXN];
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
  for(int j=0;j<n;j++)
    for(int i=0;i<=j;i++)
      {
	dp[i][j]=dp[i][j-1];
	int res=1,last=i-1;
	for(int k=i;k<j;k++)
	  {
	    if(mark[k][j]){
	      res+=dp[last+1][k-1];
	      last=k;
	    }
	  }
	res+=dp[last+1][j-1];
	dp[i][j]=max(dp[i][j],res);
	//	cout<<i<<" "<<j<<" "<<res<<" "<<dp[i][j]<<endl;
      }
  return dp[0][n-1];
}
