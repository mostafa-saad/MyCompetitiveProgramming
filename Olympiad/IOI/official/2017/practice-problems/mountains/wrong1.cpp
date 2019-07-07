#include<iostream>
#include<algorithm>
#include<vector>
#include "mountains.h"
#define X first
#define Y second

using namespace std;

typedef pair<int,int> pii;
const int MAXN=5000;
long long h[MAXN];
int n;
bool mark[MAXN][MAXN];
pii P[MAXN];
vector<int> ans;

long long cross(int i,int j,int k)
{
  return (j-i)*(h[k]-h[i])-(h[j]-h[i])*(k-i);
}


bool ok(int ind)
{
  for(int i=0;i<ans.size();i++)
    if(mark[ans[i]][ind])
      return false;
  return true;
}

int maximum_deevs(vector<int> y)
{
  int n = y.size();
  for(int i=0;i<n;i++)
    {
      h[i] = y[i];
      P[i].X=h[i],P[i].Y=i;
    }
  for(int i=0;i<n;i++)
    for(int j=i+1;j<n;j++)
      {
	mark[i][j]=true;
	for(int k=i+1;k<j;k++)
	  if(cross(i,j,k)>0)
	    mark[i][j]=false;
	mark[j][i]=mark[i][j];
      }
  sort(P,P+n);
  for(int i=0;i<n;i++)
    if(ok(P[i].Y))
      ans.push_back(P[i].Y);
  return ans.size();
}
