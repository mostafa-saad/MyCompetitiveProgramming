/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Okresowosc                                       *
 *   Autor:             Marcin Pilipczuk                                 *
 *   Zlozonosc czasowa: O(n * 2^26)                                      *
 *   Opis:              Rozwiazanie bledne                               *
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
char kopia[N];
int n;
int psufy[N];
int r;
int p[N];

/* Wypelnia tablice P od pozycji a wlacznie do b wlacznie;
 * zaklada ze do pozycji a wylacznie jest juz wypelniona */
void generuj_p(int a, int b){
  while (a <= 1)
    p[a++] = 0;
  int x = p[a - 1];
  while(a <= b){
    while(x > 0 && text[a-1] != text[x])
      x = p[x];
    if (x || text[a-1] == text[0])
      x++;
    p[a++] = x;
  }
}

char literki[30];
int nlit;
char wartosci[30];
char litwart[30];
bool bylo[30];

int main(){
  int testy;
  scanf("%d", &testy);
  while(testy--){
    scanf("%s", text);
    n = strlen(text);
    generuj_p(0, n);
    int x = p[n];
    r = 0;
    while (x > 0){
      psufy[r++] = x;
      x = p[x];
    }
    REP(i, 26) wartosci[i] = '0', bylo[i] = false;
    REP(i, n) kopia[i] = text[i];
    nlit = 0;
    REP(i, n) if (!bylo[text[i] - 'A']){
      bylo[text[i] - 'A'] = true;
      literki[nlit++] = text[i];
    }
    while(1){
      REP(i, nlit)
        litwart[literki[i] - 'A'] = wartosci[i];
      REP(i, n)
        text[i] = litwart[kopia[i] - 'A'];
      generuj_p(0, n);
      bool ok = true;
      x = p[n];
      int r2 = 0;
      while (x > 0){
        if (r2 >= r || psufy[r2] != x) { ok = false; break; }
        r2++;
        x = p[x];
      }
      if (ok && r2 == r) break;
      FORD(i, nlit - 1, 0){
        if (wartosci[i] == '1') wartosci[i] = '0';
        else { wartosci[i] = '1'; break; }
      }
    }
    printf("%s\n", text);
  }
  return 0;
}
