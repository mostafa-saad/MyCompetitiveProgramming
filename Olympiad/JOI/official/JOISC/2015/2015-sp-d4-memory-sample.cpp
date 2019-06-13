#include "Memory_lib.h"

int Memory(int N, int M) {
  int target   = (M >>  0) & ((1 << 7) - 1);
  int position = (M >>  7) & ((1 << 7) - 1);
  int depth    = (M >> 14) & ((1 << 7) - 1);
  int last     = (M >> 21) & ((1 << 1) - 1);
  if (target >= N || position >= N || depth >= N + 1 || last >= 2) {
    return 0;
  }
  switch (Get(position + 1)) {
    case '<':
      if (depth++ == target) {
        last = 0;
      }
      break;
    case '>':
      if (depth == 0) {
        return -2;
      }
      if (--depth == target) {
        if (last != 0) {
          return -2;
        }
      }
      break;
    case '[':
      if (depth++ == target) {
        last = 1;
      }
      break;
    case ']':
      if (depth == 0) {
        return -2;
      }
      if (--depth == target) {
        if (last != 1) {
          return -2;
        }
      }
      break;
    default:
      return -2;
  }
  if (++position == N) {
    if (depth != 0) {
      return -2;
    }
    if (++target == N) {
      return -1;
    }
    position = 0;
    depth = 0;
  }
  return target << 0 | position << 7 | depth << 14 | last << 21;
}
