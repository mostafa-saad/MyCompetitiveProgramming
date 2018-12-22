#include <cstdio>

using namespace std;

int n, a, b;
const int MAXT = 48 * 60;
int d[MAXT];

int main(void) 
{
  scanf("%d", &n);
  
  for (int i = 0; i < n; ++i) {
    int t, mm, ss;
    scanf("%d %d:%d", &t, &mm, &ss);
    if (t == 1) d[mm * 60 + ss] =  1;
    if (t == 2) d[mm * 60 + ss] = -1;
  }

  for (int i = 0; i < MAXT; ++i) {
    if (i > 0) d[i] += d[i - 1];
    if (d[i] > 0) ++a;
    if (d[i] < 0) ++b;
  }

  printf("%02d:%02d\n", a / 60, a % 60);
  printf("%02d:%02d\n", b / 60, b % 60);
  
  return 0;
}
