#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int MaxN = 30;

int M, N, U, L, R, D;
char a[MaxN][MaxN], sol[MaxN][MaxN];

int main (void) {
  scanf("%d %d", &M,&N);
  scanf("%d %d %d %d", &U,&L,&R,&D);

  for (int i = 0; i < M + U + D; ++i)
    for (int j = 0; j < N + L + R; ++j)
      sol[i][j] = (i + j) % 2 ? '.' : '#';
  
  for (int i = 0; i < M; ++i)
    scanf("%s", a[i]);

  for (int i = 0; i < M; ++i)
    for (int j = 0; j < N; ++j)
      sol[U + i][L + j] = a[i][j];
  
  for (int i = 0; i < M + U + D; ++i)
    printf("%s\n", sol[i]);
  
  return 0;
}
