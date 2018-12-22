#include <cstdio>
#include <cstring>
#include <cmath>

#include <vector>
#include <algorithm>

using namespace std;
typedef long double ldouble;

#define MAXH 1005
#define MAXN 100005

struct node {
  ldouble a, b, c;
  ldouble full;
  ldouble cnt;

  node() { a = b = c = full = 0.0; }
  node(ldouble A, ldouble B, ldouble C, ldouble F, ldouble Ct) {
    a = A; b = B; c = C; 
    full = F;
    cnt = Ct;
  }
};

node operator+(node P, node Q) {
  P.a += Q.a; P.b += Q.b; P.c += Q.c;
  P.full += Q.full;
  P.cnt += Q.cnt;
  return P;
}

node operator-(node P, node Q) {
  P.a -= Q.a; P.b -= Q.b; P.c -= Q.c;
  P.full -= Q.full;
  P.cnt -= Q.cnt;
  return P;
}

int N, M;
int x, nh; 
char type;

int h[MAXN];

node s[MAXN];        
node f[MAXH][MAXH];  

void add(node n, int x, int y, int sgn) {
  for (int i = x + 1; i < MAXH; i += i & -i)
    for (int j = y + 1; j < MAXH; j += j & -j)
      f[i][j] = (sgn == -1) ? (f[i][j] - n) : (f[i][j] + n);
}

node get(int x, int y) {
  node ret(0, 0, 0, 0, 0);
  for (int i = x + 1; i; i -= i & -i)
    for (int j = y + 1; j; j -= j & -j)
      ret = ret + f[i][j]; 
  return ret;
}

void update_segment(int x0) {
  ldouble h0 = min(h[x0], h[x0 + 1]);
  ldouble h1 = max(h[x0], h[x0 + 1]);

  s[x0].a = -(ldouble)0.5 / (h1 - h0);
  s[x0].b = (ldouble)h1 / (h1- h0);
  s[x0].c = -(ldouble)0.5 * h0 * h0 / (h1 - h0);
  s[x0].full = (ldouble)0.5 * (h1 + h0);
  s[x0].cnt = (ldouble)1.0;

  add(s[x0], h[x0], h[x0 + 1], +1);
}

void update_height(int x0, int nh) {
  add(s[x0], h[x0], h[x0 + 1], -1);
  add(s[x0 - 1], h[x0 - 1], h[x0], -1);

  h[x0] = nh;

  update_segment(x0);
  update_segment(x0 - 1);
}

ldouble calc_area(int h) {
  node U = get(h - 1, h - 1);
  node R = get(h, MAXH - 2);
  node F = get(MAXH - 2, h);
  node T = get(MAXH - 2, MAXH - 2) - R - F + get(h, h);
  R = R - get(h, h - 1);
  F = F - get(h - 1, h);

  ldouble sol = (ldouble) N * h;

  sol -= U.full;
  sol -= R.a * h * h + R.b * h + R.c;
  sol -= F.a * h * h + F.b * h + F.c;
  sol -= T.cnt * h;
  
  return sol;
}

int main(void)
{
  scanf("%d%d", &N, &M);

  for (int i = 1; i < N; ++i)
    scanf("%d", h + i);

  for (int i = 0; i < N; ++i)
    update_segment(i);

  for (int i = 0; i < M; ++i) {
    scanf(" %c", &type);

    if (type == 'U') {
      scanf("%d%d", &x, &nh);
      update_height(x, nh);
    } else {
      scanf("%d", &nh);
      printf("%.3Lf\n", calc_area(nh));
    }
  }

  return 0;
}
