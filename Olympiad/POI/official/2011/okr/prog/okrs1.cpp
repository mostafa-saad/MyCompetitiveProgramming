/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Okresowosc                                       *
 *   Autor:             Marcin Pilipczuk                                 *
 *   Zlozonosc czasowa: O(n^2 * 2^n)                                     *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <list>
#include <queue>
#include <deque>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <numeric>
#include <cmath>
using namespace std;

typedef vector <int > VI;
typedef vector < VI > VVI;
typedef long long LL;
typedef vector < LL > VLL;
typedef vector < double > VD;
typedef vector < string > VS;
typedef pair<int,int> PII;
typedef vector <PII> VPII;
typedef istringstream ISS;

#define ALL(x) x.begin(),x.end()
#define REP(i,n) for (int i=0; i<(n); ++i)
#define FOR(var,pocz,koniec) for (int var=(pocz); var<=(koniec); ++var)
#define FORD(var,pocz,koniec) for (int var=(pocz); var>=(koniec); --var)
#define FOREACH(it, X) for(__typeof((X).begin()) it = (X).begin(); it != (X).end(); ++it)
#define PB push_back
#define PF push_front
#define MP(a,b) make_pair(a,b)
#define ST first
#define ND second
#define SIZE(x) (int)x.size()

const int N = 200 * 1000 + 100;

char text[N];
bool okresy[N];
int n;

bool czyokres(char *x, int o){
  for (int i = 0; i < n - o; ++i)
    if (x[i] != x[i+o])
      return false;
  return true;
}

int main(){
  int testy;
  scanf("%d", &testy);
  while(testy--){
    scanf("%s", text);
    n = strlen(text);
    for (int i = 1; i < n; ++i)
      okresy[i] = czyokres(text, i);
    for (int i = 0; i < n; ++i)
      text[i] = '0';
    bool ok;
    do{
      ok = true;
      for (int i = 1; i < n; ++i)
        if (okresy[i] != czyokres(text, i)){
          ok = false;
          break;
        }
      if (ok) break;
      int k = n - 1;
      while (text[k] == '1') text[k--] = '0';
      text[k] = '1';
    }while(!ok);
    printf("%s\n", text);
  }
  return 0;
}
