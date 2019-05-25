// https://raw.githubusercontent.com/sirupsen/informatics/master/ceoi/2009/logs/logs.cpp

#include<algorithm>
#include<vector>
#include<cstdio>
#include<string>
using namespace std;

#define MAX_N 15005
#define MAX_M 1505

int main()
{
  int n, m, max_area = 0;
  char line[MAX_M]; fgets(line, MAX_M, stdin);
  sscanf(line, "%d %d", &n, &m);

  vector<int> prev(m);
  vector<int> cur(m);

  for(int i = 0; i < n; i++) {
    fgets(line, MAX_M, stdin);

    for(int j = 0; j < m; j++) {
      cur[j] = line[j] - '0';

      if(i > 0 && cur[j] != 0)
        cur[j] += prev[j];
    }

    prev = cur;

    sort(cur.begin(), cur.end(), [](int &a, int &b) {
        return a > b;
    });

    for(int j = 0; j < m; j++)
      max_area = max((j + 1) * cur[j], max_area);
  }

  printf("%d\n", max_area);

  return 0;
}
