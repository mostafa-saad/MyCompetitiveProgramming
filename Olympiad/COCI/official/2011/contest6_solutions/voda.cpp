#include <algorithm>
#include <functional>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <map>
#include <string>
#include <vector>

using namespace std;

const int mod = 10007;
const int MAXR = 10;
const int MAXS = 30;

int R, S;
int Tablica[2*MAXR];
char grid[MAXR][MAXS+1];

struct state {
  int x, y;
  int gore;
  vector<int> red;

  state() {}

  void init() {
    gore = 1;
    x = y = 0;
    red.resize(R,0);
  }  

  void spoji(int a, int b) {
    if (a > b) swap(a,b);
    for (int i = 0; i < R; ++i)
      if (red[i] == b)
        red[i] = a;
  }

  void normaliziraj() {
    memset( Tablica, -1, sizeof Tablica );
    Tablica[0] = 0;
    Tablica[1] = 1;
    int boja = 2;

    for (int i = 0; i < R; ++i)
      if (Tablica[red[i]] == -1)
        Tablica[red[i]] = boja++;

    for (int i = 0; i < R; ++i)
      red[i] = Tablica[red[i]];
    gore = Tablica[gore];
  }

  friend bool operator < ( const state &A, const state &B ) {
    if( A.x != B.x ) return A.x < B.x;
    if( A.y != B.y ) return A.y < B.y;
    if( A.gore != B.gore ) return A.gore < B.gore;
    if( A.red != B.red ) return A.red < B.red;
    return false;
  }
};

char output[MAXR][MAXS+1];

map<state, int> dp;

int solve(state &ref)
{
  map<state, int>::iterator it = dp.find(ref);
  if (it != dp.end()) {
    return it->second;
  }

  int tmp = 0;

  if (ref.y == S-1 && ref.x == R) {
    if (ref.gore != 1) return 0;
    for (int i = 0; i < R; ++i)
      if (ref.red[i] != 0)
        return 0;

    return 1;
  }

  if (ref.x == R) {
    if (ref.gore != 0) return 0;
    ref.x = 0;
    ++ref.y;
    tmp = solve(ref);
    --ref.y;
     ref.x = R;
    return tmp;
  }

  int x = ref.x;
  int y = ref.y;
  int gore = ref.gore;
  int lijevo = ref.red[x];

  if (grid[x][y] != '.' ) { // trenutno polje zauzeto
    if ( gore != 0 || lijevo != 0) return 0;
    ++ref.x;

    tmp = solve(ref);
    --ref.x;
    return dp[ref] = tmp;
  }

  if (gore != 0 && lijevo != 0) { //dolazi od gore i od lijevo
    if (gore == lijevo) return 0;

    state nov = ref;
    nov.spoji(gore, lijevo);
    nov.gore = 0;
    nov.red[x] = 0;
    nov.normaliziraj();
    ++nov.x;

    tmp = solve(nov);
  }

  if (gore != 0 && lijevo == 0) { //dolazi od gore
    ++ref.x; // propusti dolje

    tmp = solve(ref);
    --ref.x;

    ref.gore = 0;
    ref.red[x] = gore;
    ++ref.x;

    tmp += solve(ref);
    if (tmp >= mod) tmp -= mod;
    --ref.x;
    ref.red[x] = 0;
    ref.gore = gore;
  }
  
  if (gore == 0 && lijevo != 0) { // dolazi od lijevo
    ++ref.x; // propusti desno

    tmp = solve(ref);
    --ref.x;

    ref.gore = lijevo;
    ref.red[x] = 0;
    ++ref.x;

    tmp += solve(ref);
    if (tmp >= mod) tmp -= mod;
    --ref.x;
    ref.red[x] = lijevo;
    ref.gore = 0;
  }

  if (gore == 0 && lijevo == 0) {
    ++ref.x;

    tmp = solve(ref);
    --ref.x;

    state nov = ref;
    nov.gore = nov.red[x] = MAXR;
    nov.normaliziraj();
    ++nov.x;

    tmp += solve(nov);

    if (tmp >= mod) tmp -= mod;
  }

  return dp[ref] = tmp;
}

int main(void)
{
  dp.clear();

  scanf("%d %d", &R, &S);
  for (int i = 0; i < R; ++i)
    scanf("%s", grid[i]);  

  state pocetni; pocetni.init();
  printf("%d\n", solve(pocetni) % mod);

  return (0-0);
}
