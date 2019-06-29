/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Zapytania (ZAP)                                            *}
{*   Plik:    zaps3.cpp                                                  *}
{*   Autor:   Jakub Pawlewicz                                            *}
{*   Opis:    Rozwiazanie dynamiczne O(m^2 log log m)                    *}
{*                                                                       *}
{*************************************************************************/
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

typedef unsigned long long ull;

typedef uint res_t; /* Zmienic na ull, aby umozliwic wyniki 64-bitowe */

struct question {
  uint i, a, b;
  bool operator<(question q) const
  {
    if (a < q.a)
      return true;
    if (q.a < a)
      return false;
    return b < q.b;
  }
};

static vector<question> Q;
static vector<res_t> answer;
static uint maxa = 1, maxb = 1;

struct split {
  uint p, r;
};

static vector<split> F;

static inline
void read_questions()
{
  uint n;
  scanf("%u", &n);
  Q.reserve(n);
  answer.resize(n);
  for (uint i = 0; i < n; i++) {
    question q;
    uint d;
    scanf("%u%u%u", &q.a, &q.b, &d);
    q.i = i;
    q.a /= d;
    q.b /= d;
    if (q.b < q.a)
      swap(q.a, q.b);
    Q.push_back(q);
    maxa = max(maxa, q.a);
    maxb = max(maxb, q.b);
  }
}

static
void sieve_F(uint p, uint q)
{
  if (q > maxa)
    return;
  sieve_F(p, q * p);
  for (uint i = q, r = 1; i <= maxa; i += q, r++)
    if (F[i].p == 1) {
      F[i].p = p;
      F[i].r = r;
    }
}

static inline
void prepare_F()
{
  vector<bool> is_prime(maxa + 1, true);
  uint p = 2;
  uint p2 = 4;
  while (p2 <= maxa) {
    for (uint i = 2 * p; i <= maxa; i += p)
      is_prime[i] = false;
    do {
      p2 += 2 * p + 1;
      p++;
    } while (p2 <= maxa && !is_prime[p]);
  }
  F = vector<split>(maxa + 1);
  for (uint i = 1; i <= maxa; i++)
    F[i].p = 1;
  for (uint i = 2; i <= maxa; i++)
    if (is_prime[i])
      sieve_F(i, i);
}

static inline
vector<uint> find_coprime(uint a)
{
  vector<char> is_coprime(maxb + 1, true);
  while (a != 1) {
    uint p = F[a].p;
    a = F[a].r;
    for (uint i = p; i <= maxb; i += p)
      is_coprime[i] = false;
  }
  vector<uint> res(maxb + 1);
  res[0] = 0;
  for (uint i = 1; i <= maxb; i++) {
    res[i] = res[i - 1];
    if (is_coprime[i])
      res[i]++;
  }
  return res;
}

static inline
void solve()
{
  sort(Q.begin(), Q.end());
  uint a = 0, b = maxb;
  vector<res_t> c(maxb + 1, 0);
  vector<uint> coprime_a;
  for (uint i = 0; i < Q.size();) {
    if (Q[i].a == a && Q[i].b == b)
      answer[Q[i++].i] = c[b];
    else if (b == maxb) {
      coprime_a = find_coprime(++a);
      b = 0;
    } else {
      b++;
      c[b] += coprime_a[b];
    }
  }
  for (uint i = 0; i < answer.size(); i++)
    printf("%llu\n", (ull) answer[i]);
}

int main()
{
  read_questions();
  prepare_F();
  solve();
  return 0;
}
