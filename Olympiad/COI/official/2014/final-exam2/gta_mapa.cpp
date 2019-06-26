#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>
using namespace std;

const int MAX_LEN = 8;
map<string, int> komp;
map<string, string> skrati;
map<string, string> z;
vector<string> mali;
int N, br_komp;
char s[100001];

string global;
void gen(int n) {
  if (n == MAX_LEN) return;
  for (int i = 0; i < 4; ++i) {
    global += "ACGT"[i];
    mali.push_back(global);
    gen(n + 1);
    global.erase(global.size() - 1);
  }
}

void dfs(string s) {
  komp[s] = br_komp;
  for (int i = 0; i < (int)s.size() - 1; ++i) {
    map<string,string>::iterator it = z.find(s.substr(i, 2));
    if (it == z.end()) continue;
    string ss = s.substr(0, i) + it->second + s.substr(i + 2);
    if (komp.count(ss) == 0)
      dfs(ss);
  }
  if ((int)s.size() == MAX_LEN) return;
  for (int i = 0; i < (int)s.size(); ++i) {
    map<string,string>::iterator it = z.find(s.substr(i, 1));
    if (it == z.end()) continue;
    string ss = s.substr(0, i) + it->second + s.substr(i + 1);
    if (komp.count(ss) == 0)
      dfs(ss);
  }
}

inline void zamjena(string a, string b) {
  z[a] = b;
  z[b] = a;
}

int main () {
  zamjena("A", "TC");
  zamjena("C", "AG");
  zamjena("G", "CT");
  zamjena("T", "GA");

  gen(0);
  N = mali.size();
  for (int i = 0; i < N; ++i)
    if (komp.count(mali[i]) == 0) {
      dfs(mali[i]);
      ++br_komp;
    }
  for (int i = 0; i < N; ++i)
    if (mali[i].size() == 5) {
      int k = komp[mali[i]];
      for (int j = 0; ; ++j)
        if (mali[j].size() < 5 && komp[mali[j]] == k) {
          skrati[mali[i]] = mali[j];
          break;
        }
    }

  int n;
  scanf("%d", &n);
  int k[n];
  for (int i = 0; i < n; ++i) {
    scanf("%s", s);
    int d = strlen(s);
    while (d > 4) {
      string suf = skrati[string(s + d - 5, 5)];
      d -= 5;
      for (int j = 0; j < (int)suf.size(); ++j)
        s[d++] = suf[j];
    }
    k[i] = komp[string(s, d)];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j)
      printf("%d", (k[i] == k[j]));
    printf("\n");
  }
}
