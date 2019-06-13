#include "ramen.h"

void Ramen(int N) {
  int max_id, min_id, i;
  if(N%2 == 1) {
    max_id = min_id = N - 1;
  } else {
    if(Compare(N - 2, N - 1) > 0) {
      max_id = N - 2;
      min_id = N - 1;
    } else {
      max_id = N - 1;
      min_id = N - 2;
    }
  }
  for(i = 0; i < (N-1)/2; ++i) {
    int j, k;
    if(Compare(i * 2, i * 2 + 1) > 0) {
      j = i * 2;
      k = i * 2 + 1;
    } else {
      j = i * 2 + 1;
      k = i * 2;
    }
    if(Compare(j, max_id) > 0) {
      max_id = j;
    }
    if(Compare(k, min_id) < 0) {
      min_id = k;
    }
  }
  Answer(min_id, max_id);
}
