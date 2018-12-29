/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Zapytania (ZAP)                                            *}
{*   Plik:    zaps5.cpp                                                  *}
{*   Autor:   Jakub Pawlewicz                                            *}
{*   Opis:    Rozwiazanie alternatywne O(n m^(3/4))                      *}
{*                                                                       *}
{*************************************************************************/
#include <algorithm>
#include <cstdio>
#include <vector>

typedef long long ll;
typedef unsigned long long ull;

typedef uint res_t; /* Zmienic na ull, aby umozliwic wyniki 64-bitowe */

using namespace std;

const uint MAX_HT_EXP = 20;

struct question {
  uint i, a, b;
  bool operator<(question q) const
  {
    ll r = ((ll) b) * q.a - ((ll) a) * q.b;
    if (r < 0)
      return true;
    else if (r > 0)
      return false;
    else
      return a < q.a;
  }
};

struct entry {
  uint a, b;
  res_t c;
  entry() : a(0) { }
  entry(uint a, uint b, ull c) : a(a), b(b), c(c) { }
};

static vector<question> Q;
static vector<res_t> answer;
static vector<entry> ht;
static uint m = 2;

static inline
void ht_init(uint n)
{
  uint size = 1;
  ull dest_size = ((ull) n) * m;
  for (uint i = 0; i < MAX_HT_EXP; i++)
    if (size >= dest_size)
      break;
    else
      size *= 2;
  ht.resize(size);
}

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
    if (q.a < q.b)
      swap(q.a, q.b);
    Q.push_back(q);
    m = max(m, max(q.a, q.b));
  }
  ht_init(n);
}

static inline
pair<res_t, bool> ht_get(uint a, uint b)
{
  entry& e = ht[(b * m + a) & (ht.size() - 1)];
  if (e.a == a && e.b == b)
    return make_pair(e.c, true);
  else
    return make_pair(0, false);
}

static inline
void ht_save(uint a, uint b, res_t c)
{
  entry& e = ht[(b * m + a) & (ht.size() - 1)];
  e.a = a;
  e.b = b;
  e.c = c;
}

static
res_t coprimes(uint a, uint b)
{
  if (b == 0)
    return 0;
  if (b == 1)
    return a;
  if (b == 2)
    return 2 * a - a / 2;
  pair<res_t, bool> ht_res = ht_get(a, b);
  if (ht_res.second)
    return ht_res.first;
  /* Tutaj mozna przekroczyc zakres, ale to nie szkodzi, gdyz
     ostateczny wynik bedzie miescil sie w liczbie 32-bitowej, a cale
     obliczenia mozna traktowac jak rachunki modulo 2^32. */
  res_t c = ((res_t) a) * b;
  uint k = a / b, l;
  uint d = b;
  while (k * k <= a) {
    l = b / d;
    uint d1 = max(a / (k + 1), b / (l + 1));
    c -= (d - d1) * coprimes(k, l);
    d = d1;
    k = a / d;
  }
  for (; d >= 2; d--)
    c -= coprimes(a / d, b / d);
  ht_save(a, b, c);
  return c;
}

static inline
void solve()
{
  sort(Q.begin(), Q.end());
  for (vector<question>::iterator i = Q.begin(); i != Q.end(); ++i)
    answer[i->i] = coprimes(i->a, i->b);
  for (uint i = 0; i < answer.size(); i++)
    printf("%llu\n", (ull) answer[i]);
}

int main()
{
  read_questions();
  solve();
  return 0;
}
