/*
* pravo rjesenje za hash.
* slozenost:
* O(N, K, M) = 26^(N/2)
*
* iskoristava se cinjenica da je hash funkcija
*
* state[0] = 0
* state[i+1] = (state[i] * 33 + a[i]) % Mod;
*
* iterativno reverzibilna, odnosno da je:
*
* state[i-1] = ((state[i] ^ a[i]) / 33) % Mod
*
* kada ovo znamo, mozemo generirati hash vrijednosti za sve
* kombinacije od N/2 slova unaprijed i unazad i prebrojat
* kolizije.
*/
#include <cstdio>
#include <cassert>
#include <cstring>

const int maxMod = (1 << 25);

int N, K, Mod, table[maxMod];
long long solution = 0, inv33;

void rec1(int state, int iter) {
  if (iter) {
    for (int z = 1; z <= 26; ++z) {
      rec1(((state * 33) ^ z) & Mod, iter - 1);
    }
  } else {
    ++table[state];
  }
}

void rec2(int state, int iter) {
  if (iter) {
    for (int z = 1; z <= 26; ++z) {
      rec2(((state ^ z) * inv33) & Mod, iter - 1);
    }
  } else {
    solution += table[state];
  }
}

void load() {
  scanf("%d%d%d", &N, &K, &Mod);
  Mod = (1 << Mod);
  int e = Mod / 2 - 1;
  long long b = 33;
  for (inv33 = 1; e; e /= 2) {
    if (e & 1) inv33 = (inv33 * b) % Mod;
    b = (b * b) % Mod;
  }
  assert((33ll * inv33) % Mod == 1);
  --Mod;
}

int main() {
  load();
  rec1(0, N / 2);
  rec2(K, N - N / 2);
  printf("%lld\n", solution);
  return 0;
}
