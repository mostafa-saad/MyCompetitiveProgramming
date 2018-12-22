#include <cstdio>
#include <set>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>
#include <complex>

using namespace std;

#define TRACE(x) cerr << #x << " = " << x << endl
#define REP(i, n) for (int i=0; i<n; i++)
#define FOR(i, a, b) for (int i=(a); i<(b); i++)

typedef long long ll;
typedef pair<int, int> P;
#define X first
#define Y second

const int MAXS = 505, MAXN = 1<<20;

namespace FFT {
  typedef int value;
  typedef complex<double> comp;
  int N;
  comp omega[MAXN];
  comp a1[MAXN], a2[MAXN];
  comp z1[MAXN], z2[MAXN];
  void fft(comp *a, comp *z, int m = N) {
    if (m == 1) {
      z[0] = a[0];
    } else {
      int s = N/m;
      m /= 2;
      fft(a, z, m);
      fft(a+s, z+m, m);
      REP(i, m) {
        comp c = omega[s*i] * z[m+i];
        z[m+i] = z[i] - c;
        z[i] += c;
      }
    }
  }
  void mult(value *a, value *b, value *c, int len) {
    N = 2*len;
    while (N & (N-1)) ++N;
    assert(N <= MAXN);
    REP(i, N) a1[i] = 0;
    REP(i, N) a2[i] = 0;
    REP(i, len) a1[i] = a[i];
    REP(i, len) a2[i] = b[i];

    REP(i, N) omega[i] = polar(1.0, 2*M_PI/N*i);
    fft(a1, z1, N);
    fft(a2, z2, N);

    REP(i, N) omega[i] = comp(1, 0) / omega[i];
    REP(i, N) a1[i] = z1[i] * z2[i] / comp(N, 0);
    fft(a1, z1, N);
    REP(i, 2*len) c[i] = (value) round(z1[i].real());
  }
}

const double EPS = 1e-7;

bool lt(double a, double b) { return a + EPS < b; }
bool eq(double a, double b) { return !lt(a, b) && !lt(b, a); }

struct duz {
  P poc, kraj;
};

double poz(const duz &a, int x)
{
  return ((double) a.poc.Y - a.kraj.Y) / (a.poc.X - a.kraj.X) * (x - a.poc.X) + a.poc.Y;
}

void printduz(const duz &a)
{
  printf("%d %d    %d %d\n", a.poc.X, a.poc.Y, a.kraj.X, a.kraj.Y);
}

int tmpx;
bool operator < (const duz &a, const duz &b)
{
  double ya = poz(a, tmpx), yb = poz(b, tmpx);
  if (!eq(ya, yb)) return lt(ya, yb);
  if (a.poc.X < tmpx && b.poc.X == tmpx) return true;
  if (b.poc.X < tmpx && a.poc.X == tmpx) return false;
  if (a.poc.X < tmpx) {
    assert(b.poc.X < tmpx && a.kraj.X == tmpx && b.kraj.X == tmpx);
    return lt(poz(a, tmpx-1), poz(b, tmpx-1));
  }
  assert(a.poc.X == tmpx && b.poc.X == tmpx && a.kraj.X > tmpx && b.kraj.X > tmpx);
  return lt(poz(a, tmpx+1), poz(b, tmpx+1));
}

int n;
P p[MAXN];
int unutra[MAXS][MAXS];
int velx, vely;
int brm;
P muha[MAXN];
int polin_muh[MAXN], polin_mlat[MAXN], umn[MAXN];

void nadi_tocke()
{
  int minx = p[0].X, miny = p[0].Y;
  REP(i, n) {
    minx = min(minx, p[i].X);
    miny = min(miny, p[i].Y);
  }

  REP(i, n) {
    p[i].X -= minx;
    p[i].Y -= miny;

    if (p[i].X > velx || p[i].Y > vely) return;
  }

  set <duz> S;
  vector <duz> E;

  REP(i, n) {
    P a = p[i], b = p[(i+1)%n];
    if (a.X == b.X)
      FOR(j, min(a.Y, b.Y), max(a.Y, b.Y) + 1)
        unutra[a.X][j] = 1;
    else {
      E.push_back({a, b});
      E.push_back({b, a});
    }
  }

  sort(E.begin(), E.end(), [] (const duz &a, const duz &b) {
      return make_pair(a.poc, a.kraj) < make_pair(b.poc, b.kraj); });

  int j=0;
  for (tmpx=0; tmpx<=velx; tmpx++) {
    int ind = j;
    for (; j<(int) E.size() && E[j].poc.X == tmpx; j++)
      if (E[j].poc.X < E[j].kraj.X)
        S.insert({min(E[j].poc, E[j].kraj), max(E[j].poc, E[j].kraj)});

    auto it = S.begin();
    double toc = (it == S.end()) ? MAXS : poz(*it, tmpx);
    int in = 0;
    REP(i, vely + 1) {
      for (; eq(i, toc) || lt(toc, i); ) {
        if (eq(i, toc))
          unutra[tmpx][i] = 1;

        if (it->poc.X < tmpx)
          in ^= 1;

        it++;
        toc = (it == S.end()) ? MAXS : poz(*it, tmpx);
      }

      unutra[tmpx][i] |= in;
    }

    j = ind;
    for (; j<(int) E.size() && E[j].poc.X == tmpx; j++)
      if (E[j].poc.X > E[j].kraj.X) {
        assert(S.find({min(E[j].poc, E[j].kraj), max(E[j].poc, E[j].kraj)}) != S.end());
        S.erase({min(E[j].poc, E[j].kraj), max(E[j].poc, E[j].kraj)});
      }
  }

  REP(i, n)
    assert(unutra[p[i].X][p[i].Y]);
}

int main()
{
  scanf("%d%d%d", &velx, &vely, &brm);
  REP(i, brm)
    scanf("%d %d", &muha[i].X, &muha[i].Y);

  scanf("%d", &n);
  REP(i, n)
    scanf("%d%d", &p[i].X, &p[i].Y);

  nadi_tocke();

  int K = 2 * vely + 5, M = K * (velx + 1);;
  REP(i, brm)
    polin_muh[M - (K * muha[i].X + muha[i].Y)] = 1;

  REP(i, velx + 1)
    REP(j, vely + 1)
    if (unutra[i][j])
      polin_mlat[K * i + j] = 1;

  FFT::mult(polin_muh, polin_mlat, umn, M);

  int maxx = 0, maxy = 0;
  REP(i, n) {
    maxx = max(maxx, p[i].X);
    maxy = max(maxy, p[i].Y);
  }

  int rje = 0;
  REP(i, velx + 1)
    REP(j, vely + 1)
      if (!umn[M - (K*i + j)] && i + maxx <= velx && j + maxy <= vely)
        rje++;

  printf("%d\n", rje);

  return 0;
}

