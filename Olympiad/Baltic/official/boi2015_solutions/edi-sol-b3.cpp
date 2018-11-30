// Wojtek Nadara
// Program wypisujacy tylko koncowy stan edytora
// Zlozonosc: O(n log n)
#include <bits/stdc++.h>
#include <vector>
#define MP make_pair
#define st first
#define nd second
using namespace std;
typedef pair<int, int> PII;
const int N = 5e5 + 5;
int nxt[N];
int prv[N];
int op[N];
void Del(int a) {
  nxt[prv[a]] = nxt[a];
  prv[nxt[a]] = prv[a];
}
int main() {
  ios_base::sync_with_stdio(0);
  int n;
  cin>>n;
  set<PII> by_lvl;
  by_lvl.insert(MP(0, 0));
  for (int i = 1; i <= n; i++) {
    cin>>op[i];
    if (op[i] < 0) {
      by_lvl.insert(MP(op[i], i));
    } else {
      by_lvl.insert(MP(0, -i));
    }
    nxt[i] = i + 1;
    prv[i] = i - 1;
  }
  prv[n + 1] = n;
  while (!by_lvl.empty()) {
    auto it = by_lvl.begin();
    auto most_important = *it;
    if (most_important.st == 0) {
      for(int i=1;i<n;i++)
		cout<<"0\n";
      cout<<op[-most_important.nd]<<"\n";
      return 0;
    }
    int to_undo = prv[most_important.nd];
    Del(most_important.nd);
    Del(to_undo);
    by_lvl.erase(most_important);
    if (op[to_undo] < 0) {
      by_lvl.erase(MP(op[to_undo], to_undo));
    } else {
      by_lvl.erase(MP(0, -to_undo));
    }
  }
}
