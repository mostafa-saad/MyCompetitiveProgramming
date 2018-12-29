/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Okresowosc                                       *
 *   Autor:             Marcin Pilipczuk                                 *
 *   Zlozonosc czasowa: O(2^n)                                           *
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
int okresy[N];
int nokresy;
int n;
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

int main(){
  int testy;
  scanf("%d", &testy);
  while(testy--){
    scanf("%s", text);
    n = strlen(text);
    generuj_p(0, n);
    nokresy = 0;
    int x = p[n];
    while (x > 0){
      okresy[nokresy++] = n - x;
      x = p[x];
    }
    for (int i = 0; i < n; ++i)
      text[i] = '0';
    generuj_p(0, n);
    do{
      x = p[n];
      int j = 0;
      while (x > 0 && j < nokresy){
        if (okresy[j] != n - x)
          break;
        x = p[x];
        j++;
      }
      if (x == 0 && j == nokresy)
        break;
      int k = n - 1;
      while (text[k] == '1') text[k--] = '0';
      text[k] = '1';
      generuj_p(k, n);
    }while(true);
    printf("%s\n", text);
  }
  return 0;
}
