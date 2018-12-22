#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 510;

int n, m, k, x, br;

char s[MAXN];
char niz[MAXN][MAXN];

int pos[MAXN];

int main()
{
  scanf("%d %d %d %d", &n, &m, &k, &x);
  scanf("%s", s);
  for(int i = 0; i < n; i++)
    if(s[i] == '#')
      pos[br++] = i;
  for(int i = 0; i < m; i++)
    scanf("%s", niz[i]);
  if(m == 1 && k == 3)
  {
    char zelim = 'a';
    for(int a = 0; a < 3; a++)
      for(int b = 0; b < 3; b++)
        for(int c = 0; c < 3; c++)
        {
          if(a == b || a == c || b == c) continue;
          if(niz[0][a] < niz[0][b] && niz[0][b] < niz[0][c])
          {
            if(x == 1) zelim = niz[0][a];
            if(x == 2) zelim = niz[0][b];
            if(x == 3) zelim = niz[0][c];
          }
        }
    s[pos[0]] = zelim;
    printf("%s\n", s);
  } 
  else if(m == 1)
  {
    sort(niz[0], niz[0] + k);
    s[pos[0]] = niz[0][x - 1];
    printf("%s\n", s);
    return 0;
  }
  else
  {
    x--;
    for(int i = 0; i < m; i++)
      sort(niz[i], niz[i] + k);
    for(int i = 0; i < m; i++)
      s[pos[i]] = niz[i][0];
    for(int i = m - 1; i >= 0; i--)
    {
      if(x == 0) break;
      int koji = x % k;
      s[pos[i]] = niz[i][koji];
      x /= k;
    }
    printf("%s\n", s);    
  }
  return 0;
}
