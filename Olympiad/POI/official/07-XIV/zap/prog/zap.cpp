/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Zapytania (ZAP)                                            *}
{*   Plik:    zap.cpp                                                    *}
{*   Autor:   Jakub Pawlewicz                                            *}
{*   Opis:    Rozwiazanie wzorcowe O( sqrt(n) (n log n + m log m) )      *}
{*                                                                       *}
{*************************************************************************/
#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>

using namespace std;

struct question {
  uint i, a, b;
  bool operator<(question q) const { return b < q.b; }
  bool operator>(question q) const { return b > q.b; }
  bool operator==(question q) const { return i == q.i; }
};

typedef unsigned long long ull;

vector<question> Q;
vector<ull> answer;
uint m = 2;

struct split {
  uint p, r;
};

vector<split> F;

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
}

void sieve_F(uint p, uint q)
{
  if (q > m)
    return;
  sieve_F(p, q * p);
  for (uint i = q, r = 1; i <= m; i += q, r++)
    if (F[i].p == 1) {
      F[i].p = p;
      F[i].r = r;
    }
}

void prepare_F()
{
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
  F = vector<split>(m + 1);
  for (uint i = 1; i <= m; i++)
    F[i].p = 1;
  for (uint i = 2; i <= m; i++)
    if (is_prime[i])
      sieve_F(i, i);
}

/* Counts numbers from set {1, ..., a} coprime with b */
uint coprime_line_count(uint a, uint b)
{
  if (b == 0 || a == 0)
    return 0;
  else if (b == 1)
    return a;
  else
    return coprime_line_count(a, F[b].r) -
      coprime_line_count(a / F[b].p, F[b].r);
}

struct question_ab_less : public binary_function<question, question, bool> {
  bool operator()(question x, question y)
  {
    if (x.a < y.a)
      return true;
    if (y.a < x.a)
      return false;
    return x.b < y.b;
  }
};

template <typename Cmp>
vector<question> find_increasing_subsequence(Cmp cmp)
{
  vector<int> prev(Q.size());
  vector<int> qidx;
  vector<question> q;
  for (uint i = 0; i < Q.size(); i++) {
    vector<question>::iterator j = upper_bound(q.begin(), q.end(), Q[i], cmp);
    if (j == q.end()) {
      qidx.push_back((int) i);
      q.push_back(Q[i]);
      j = q.end() - 1;
    } else {
      qidx[j - q.begin()] = i;
      *j = Q[i];
    }
    if (j != q.begin())
      prev[i] = qidx[j - q.begin() - 1];
  }
  int j = qidx.back();
  for (uint i = q.size(); i-- > 0;) {
    q[i] = Q[j];
    j = prev[j];
  }
  return q;
}

vector<question> get_monotonic_subsequence()
{
  vector<question> seq1 = find_increasing_subsequence(less<question>());
  vector<question> seq2 = find_increasing_subsequence(greater<question>());
  return seq1.size() > seq2.size() ? seq1 : seq2;
}

void strip_subsequence(vector<question> seq)
{
  uint i = 0, j = 0, k = 0;
  while (k < seq.size())
    if (Q[i] == seq[k]) {
      k++; i++;
    } else
      Q[j++] = Q[i++];
  while (i < Q.size())
    Q[j++] = Q[i++];
  Q.resize(j);
}

void find_answer_for(vector<question> seq)
{
  vector<question>::iterator i = seq.begin();
  uint a = 0;
  uint b = i->b;
  ull c = 0;
  while (i != seq.end()) {
    if (a == i->a && b == i->b) {
      answer[i->i] = c;
      ++i;
    } else if (a < i->a)
      c += coprime_line_count(b, ++a);
    else if (a > i->a)
      c -= coprime_line_count(b, a--);
    else if (b < i->b)
      c += coprime_line_count(a, ++b);
    else
      c -= coprime_line_count(a, b--);
  }
}

void solve()
{
  sort(Q.begin(), Q.end(), question_ab_less());
  do {
    vector<question> mon = get_monotonic_subsequence();
    strip_subsequence(mon);
    find_answer_for(mon);
  } while (!Q.empty());
  for (uint i = 0; i < answer.size(); i++)
    printf("%llu\n", answer[i]);
}

int main()
{
  read_questions();
  prepare_F();
  solve();
  return 0;
}
