#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
  int n, past, start, sol = 0;

  scanf("%d%d", &n, &past);
  start = past;

  int curr;

  for(int i = 0; i < n-1; ++i) {
    scanf("%d", &curr);

    if(curr <= past) {
      sol = max(sol, past-start);
      start = curr;
    }

    past = curr;
  }
  
  sol = max(sol, past-start);
  printf("%d\n", sol);

  return 0;
}
