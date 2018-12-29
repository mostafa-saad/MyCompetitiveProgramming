// Autor: Ivan Katanic

#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

typedef long long llint;

const int MAX = 100100;
const int H = 9973;
const int mod = 1e9 + 7;

int pw[MAX];

int h[MAX];
int hr[MAX];
char s[MAX];
char sr[MAX];
int n;

void calcHashes(char* s, int* h) {
  h[0] = 1;
  for (int i = 0; i < n; ++i)
    h[i+1] = (h[i]*1LL*H + s[i]) % mod;
}

int getHash(int* h, int a, int b) {
  return ((h[b+1] - h[a]*1LL*pw[b-a+1]) % mod + mod) % mod;
}

bool revEqual(int a, int b, int c, int d) {
  return getHash(h, a, b) == getHash(hr, n-d-1, n-c-1);
}

int main(void) {
  scanf("%s", s);
  n = strlen(s);

  pw[0] = 1;
  for (int i = 0; i < n; ++i)
    pw[i+1] = (pw[i]*1LL*H) % mod;
  
  for (int i = 0; i < n; ++i)
    sr[i] = s[n-i-1];
  calcHashes(s, h);
  calcHashes(sr, hr);

  static llint f[MAX][26]; // created 
  static llint fk[MAX], fl[MAX]; // destroyed

  llint base = 0;
  for (int i = 0; i < n; ++i)
    for (int j = i; j <= i+1; ++j) {
      int lo = 0, hi = min(i+1, n-j);
      while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (revEqual(i-mid+1, i, j, j+mid-1)) lo = mid;
        else hi = mid - 1;
      }
      int r = lo;
      base += r;

      if (i == j) { // odd
        fk[j+1] += -1, fk[j+r] -= -1;
        fl[j+1] += j+r, fl[j+r] -= j+r;
        
        fk[i-r+1] += 1, fk[i] -= 1;
        fl[i-r+1] += -(i-r), fl[i] -= -(i-r);
      } else { // even
        fk[j] += -1, fk[j+r] -= -1;
        fl[j] += j+r, fl[j+r] -= j+r;
        
        fk[i-r+1] += 1, fk[i+1] -= 1;
        fl[i-r+1] += -(i-r), fl[i+1] -= -(i-r);
      }
      
      int x = i-r, y = j+r;
      if (x < 0 || y >= n) continue;
    
      r++;
      lo = 0, hi = min(i+1, n-j) - r;
      while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (revEqual(x-mid, x-1, y+1, y+mid)) lo = mid;
        else hi = mid - 1;
      }

      f[x][s[y]-'a'] += lo+1;
      f[y][s[x]-'a'] += lo+1;
    }
  
  llint best_change = 0;
  llint k = 0, l = 0;
  for (int i = 0; i < n; ++i) {
    k += fk[i], l += fl[i];
    for (int j = 0; j < 26; ++j)
      if (j+'a' != s[i]) {
        best_change = max(best_change, f[i][j] - (llint(i)*k + l));
      }
  }

  printf("%lld\n", base + best_change);
  return 0;
}
