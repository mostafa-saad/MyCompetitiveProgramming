/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Zapytania (ZAP)                                            *}
{*   Plik:    zapb1.cpp                                                  *}
{*   Autor:   Jakub Pawlewicz                                            *}
{*   Opis:    Rozwiazanie niepoprawne                                    *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <vector>

using namespace std;

struct question {
  uint a, b;
};

typedef unsigned long long ull;

vector<question> Q;
uint m = 2;
vector<ull> T;

void read_questions()
{
  uint n;
  scanf("%u", &n);
  Q.reserve(n);
  for (uint i = 0; i < n; i++) {
    question q;
    uint d;
    scanf("%u%u%u", &q.a, &q.b, &d);
    q.a /= d;
    q.b /= d;
    Q.push_back(q);
    m = max(m, max(q.a, q.b));
  }
}

void prepare_T()
{
  /* sieveing */
  vector<bool> is_prime(m + 1, true);
  uint p = 2;
  uint p2 = 4;
  while (p2 <= m) {
    for (uint i = 2 * p; i <= m; i += p)
      is_prime[i] = false;
    do {
      p2 += 2 * p + 1;
      p++;
    } while (p2 <= m && !is_prime[p]);
  }

  /* phi */
  vector<uint> phi(m + 1);
  for (uint i = 1; i <= m; i++)
    phi[i] = i;
  for (uint p = 2; p <= m; p++)
    if (is_prime[p]) {
      phi[p]--;
      for (uint i = 2 * p; i <= m; i += p) {
  phi[i] /= p;
  phi[i] *= (p - 1);
      }
    }

  /* T */
  T = vector<ull>(m + 1);
  T[1] = 1;
  for (uint i = 2; i <= m; i++)
    T[i] = T[i - 1] + 2 * phi[i];
}

ull answer(uint a, uint b)
{
  ull ret = 0;
  if (b > a)
    swap(a, b);
  while (b != 0) {
    ret += (a / b) * T[b];
    a = a % b;
    swap(a, b);
  }
  return ret;
}

void solve()
{
  for (uint i = 0; i < Q.size(); i++)
    printf("%llu\n", answer(Q[i].a, Q[i].b));
}

int main()
{
  read_questions();
  prepare_T();
  solve();
  return 0;
}
