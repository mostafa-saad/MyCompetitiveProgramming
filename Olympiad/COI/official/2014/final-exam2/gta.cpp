#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_LEN = 8;
vector<string> mali;
int komp[500000];
int N, br_komp;
char s[50001];
int prvi_u_komp[100001];
string zamjena[500];
string broj_u_string[500000];

string global;
int broj;

void gen(int n) {
  if (n == MAX_LEN) return;
  for (int i = 0; i < 4; ++i) {
    global += (char)('a' + i);
    broj = broj * 5 + i + 1;
    mali.push_back(global);
    broj_u_string[broj] = global;
    gen(n + 1);
    global.erase(global.size() - 1);
    broj /= 5;
  }
}

inline int string_u_broj(const string &s) {
  int ret = 0;
  for (int i = 0; i < (int)s.size(); ++i)
    ret = ret * 5 + s[i] - 'a' + 1;
  return ret;
}

void dfs(int b) {
  if (komp[b]) return;
  komp[b] = br_komp;
  string& s = broj_u_string[b];
  for (int i = 0; i < (int)s.size() - 1; ++i) {
    if ((s[i + 1] & 1) != (s[i] & 1)) continue;
    if (s[i] == s[i + 1]) continue;
    char slovo = 'd';
    if (s[i + 1] != 'a')
      slovo = s[i + 1] - 1;
    dfs(string_u_broj(s.substr(0, i) + slovo + s.substr(i + 2)));
  }
  if ((int)s.size() == MAX_LEN) return;
  for (int i = 0; i < (int)s.size(); ++i)
    dfs(string_u_broj(s.substr(0, i) + zamjena[s[i]] + s.substr(i + 1)));
}

inline bool cmp(const string &a, const string &b) {
  if (a.size() == b.size())
    return a < b;
  return a.size() < b.size();
}

int main () {
  zamjena['a'] = "db";
  zamjena['b'] = "ac";
  zamjena['c'] = "bd";
  zamjena['d'] = "ca";

  gen(0);
  sort(mali.begin(), mali.end(), cmp);
  N = mali.size();
  for (int i = 0; i < N; ++i) {
    int b = string_u_broj(mali[i]);
    if (komp[b]) continue;
    ++br_komp;
    prvi_u_komp[br_komp] = b;
    dfs(b);
  }

  int n;
  scanf("%d", &n);
  int k[n];
  for (int i = 0; i < n; ++i) {
    scanf("%s", s);
    int d = strlen(s);
    for (int j = 0; j < d; ++j) {
      if (s[j] == 'A') s[j] = 'a';
      else if (s[j] == 'C') s[j] = 'b';
      else if (s[j] == 'G') s[j] = 'c';
      else if (s[j] == 'T') s[j] = 'd';
    }
    int next = min(4, d);
    int b = string_u_broj(string(s, next));
    while (next < d)
      b = prvi_u_komp[komp[b * 5 + s[next++] - 'a' + 1]];
    k[i] = komp[b];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j)
      printf("%d", (k[i] == k[j]));
    printf("\n");
  }
}
