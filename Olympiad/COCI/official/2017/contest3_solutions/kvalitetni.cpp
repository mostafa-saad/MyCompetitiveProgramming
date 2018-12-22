#include <cstdio>
#include <iostream>
#include <cstring>
#include <stack>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAXN = 1000010;

enum {ADD, MUL};

char a[MAXN];
stack<int> s;
vector<int> e[MAXN];
int n, m, k, z[MAXN], op[MAXN];
double val[MAXN];

bool cmp(int i, int j) {
  return val[i] < val[j];
}

double get_mul(vector<int>& v) {
  assert((int)v.size() <= k);
  sort(v.begin(), v.end(), cmp);
  double tot = z[(int)v.size()];
  
  double ret = 1;
  for (int i = 0; i < (int)v.size(); ++i) {
    int rem = (int)v.size() - i;
    if (tot / rem < val[v[i]]) {
      for (int j = i; j < (int)v.size(); ++j)
	ret *= tot / rem;
      break;
    } else {
      ret *= val[v[i]];
      tot -= val[v[i]];
    }
  }
  return ret;
}

double get_add(vector<int>& v) {
  double ret = 0;
  for (int i = 0; i < (int)v.size(); ++i)
    ret += val[v[i]];
  return min(ret, (double)z[(int)v.size()]);
}

int main(void) {
  scanf("%d",&k);
  for (int i = 1; i <= k; ++i)
    scanf("%d",&z[i]);
  scanf("%s",a);
  n = strlen(a);

  for (int i = 0; i < n; ++i) {
    if (a[i] == '(') {
      if (!s.empty()) {
	e[s.top()].push_back(m);
      }
      s.push(m++);
    }
    else if (a[i] == '+')
      op[s.top()] = ADD;
    else if (a[i] == '*')
      op[s.top()] = MUL;
    else if (a[i] == ')') {
      int x = s.top();
      s.pop();
      if (e[x].empty()) {
	val[x] = z[1];
	assert(val[x] != 0);
      }
      else {
	val[x] = (op[x] == ADD) ? get_add(e[x]) : get_mul(e[x]);
      }
    }
  }

  printf("%.9lf\n",val[0]);

  return 0;
}
