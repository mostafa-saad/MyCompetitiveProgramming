#include "mountains.h"
#include <complex>

using namespace std;

/**
 * Simple backtrack with branch & bound
 * The running time of this algorithm is bounded by O(g^n) where g is the golden number (1+sqrt(5))/2
 *
 * Author: Kian Mirjalali
 *
 */

#define forv(i, v) for (int i=0; i<int((v).size()); i++)

template<class A, class B>
inline bool minEq(A& a, const B& b) {
  return (b<a) && (a=b, true);
}

typedef long long Int;
typedef complex<Int> point;
#define X real()
#define Y imag()

inline int sign(Int x) {
  return (x<0) ? -1 : ((x>0)? +1 : 0);
}

inline Int zcross(const point& a, const point& b) {
  return a.X*b.Y-a.Y*b.X;
}
inline int turn(const point& a, const point& b, const point& c) {
  return sign(zcross(b-a, c-a));
}


int n, ans, curr;
vector< vector<bool> > vis;
vector< vector<int> > visFList;
vector<int> ubound, put;


void bt(int i) {
  if (i==n)
	{
	  if (ans<curr)
		ans = curr;
	  return;
	}
  if (put[i]==0)
	{
	  curr++;
	  forv(j, visFList[i])
		put[visFList[i][j]]++;
	  bt(i+1);
	  curr--;
	  forv(j, visFList[i])
		put[visFList[i][j]]--;
	}
  if (curr+ubound[i+1]>ans)
	bt(i+1);
}

int maximum_deevs(vector<int> y) {
  n = y.size();
  
  vis.clear();
  vis.resize(n, vector<bool>(n));
  for (int i=0; i<n; i++)
	{
	  int h = -1;
	  for (int j=i-1; j>=0; j--)
		{
		  if (h<0 || turn(point(i, y[i]), point(j, y[j]), point(h, y[h]))>=0)
			h = j;
		  vis[j][i] = vis[i][j] = (h==j);
		}
	}
  
  visFList.clear();
  visFList.resize(n);
  for (int i=0; i<n; i++)
	for (int j=i+1; j<n; j++)
	  if (vis[i][j])
		visFList[i].push_back(j);
  
  ubound.resize(n+1);
  for (int i=n; i>=0; i--)
	{
	  ubound[i] = (n+1-i)/2;
	  for (int j=i; j<n; j++)
		{
		  int b = true;
		  for (int k=i; k<j; k++)
			b = b && vis[k][j];
		  if (b)
			minEq(ubound[i], 1+ubound[j+1]);
		  else
			break;
		}
	}
  /*
  for (int i=0; i<=n; i++)
	cerr << ubound[i] << " ";
  cerr << endl;
  //*/
  ans = 0;
  put.clear();
  put.resize(n, 0);
  curr = 0;
  bt(0);
  return ans;
}

