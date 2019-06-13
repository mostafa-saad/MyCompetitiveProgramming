#include "Brunolib.h"
#include <cstdio>

static int it;
static int dat[150];

static const int len[] = { 0, 1, 1, 2, 2, 2, 1, 2 };
static const int val[] = { 0, 1, 0, 2, 0, 1, 1, 3 };

long long Bruno( int N, int A[] ){

  it = 0;
  for( int i = 0; i < N/3; i++ ){
    int c = A[i*3+0] * 4 + A[i*3+1] * 2 + A[i*3+2];
    if( len[c] == 1 ){
      dat[it++] = val[c];
    } else if( len[c] == 2 ){
      dat[it++] = val[c] / 2;
      dat[it++] = val[c] % 2;
    }
  }
  
  long long d = 1;
  long long ans = 0;
  for( int i = 0; i < 60; i++ ){
    ans += d * dat[i];
    d *= 2;
  }
  
  return ans;
}
