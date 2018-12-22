#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define TRACE(x) cout << #x << " = " << x << endl;

typedef long long int llint;

typedef pair<int, int> par;

#define X first
#define Y second

const int MAXN = 500010, MOD = 1000000007;

inline int add(int a, int b)
{
  int ret = a + b;
  if(ret >= MOD) ret -= MOD;
  return ret;
}

inline int mul(int a, int b)
{
  llint ret = (llint)a * b;
  if(ret >= MOD) ret %= MOD;
  return ret;
}

int n;
int niz[MAXN], dva[MAXN];

par A[MAXN], B[MAXN];
par FWT_gore[MAXN], FWT_dolje[MAXN];

par rj;

par spoji(par a, par b)
{
 if(b.X > a.X)
 {
   a.X = b.X;
   a.Y = b.Y;
 } 
 else if(b.X == a.X)
   a.Y = add(a.Y, b.Y);
 return a;
}

void ubaci_gore(int x, par v)
{
  x += 5;
  for(; x < MAXN; x += x & -x)
    FWT_gore[x] = spoji(FWT_gore[x], v);
}

par upit_gore(int x)
{
  x += 5;
  par ret(0, 0);
  for(; x > 0; x -= x & -x)
    ret = spoji(ret, FWT_gore[x]);
  return ret;
}

void ubaci_dolje(int x, par v)
{
  x += 5;
  for(; x > 0; x -= x & -x)
    FWT_dolje[x] = spoji(FWT_dolje[x], v);
}

par upit_dolje(int x)
{
  x += 5;
  par ret(0, 0);
  for(; x < MAXN; x += x & -x)
    ret = spoji(ret, FWT_dolje[x]);
  return ret;
}

void sazmi()
{
  vector<int> v;
  for(int i = 0; i < n; i++)
    v.push_back(niz[i]);
  sort(v.begin(), v.end());
  v.resize(unique(v.begin(), v.end()) - v.begin());
  for(int i = 0; i < n; i++)
    niz[i] = lower_bound(v.begin(), v.end(), niz[i]) - v.begin();
}

void sredi_gore()
{
  for(int i = n - 1; i >= 0; i--)
  {
    par p = upit_gore(niz[i] - 1);
    if(p.X == 0)
    {
      A[i] = par(0, 1);
      ubaci_gore(niz[i], par(1, 1));
    }
    else 
    {
      A[i] = p;
      p.X++;
      ubaci_gore(niz[i], p);
    }
  }
}

void sredi_dolje()
{
  for(int i = n - 1; i >= 0; i--)
  {
    par p = upit_dolje(niz[i] + 1);
    if(p.X == 0)
    {
      B[i] = par(0, 1);
      ubaci_dolje(niz[i], par(1, 1));
    }
    else
    {
      B[i] = p;
      p.X++;
      ubaci_dolje(niz[i], p);
    }
  }
}

void postavi()
{
  dva[0] = 1;
  for(int i = 1; i < MAXN; i++)
    dva[i] = mul(dva[i - 1], 2);
}

void glavno()
{
  for(int i = 0; i < n; i++)
    rj = spoji(rj, par(A[i].X + 1 + B[i].X, mul(A[i].Y, B[i].Y)));
  rj.Y = mul(rj.Y, dva[n - rj.X]);
}

int main()
{
  postavi();
  scanf("%d", &n);
  for(int i = 0; i < n; i++)
    scanf("%d", &niz[i]);
  sazmi();
  sredi_gore();
  sredi_dolje();
  glavno();
  printf("%d %d\n", rj.X, rj.Y);
  return 0;
}
