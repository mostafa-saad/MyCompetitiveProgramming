/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Okresowosc                                       *
 *   Autor:             Marcin Pilipczuk                                 *
 *   Zlozonosc czasowa: O(n)                                             *
 *   Opis:              Rozwiazanie wzorcowe                             *
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
    for (int i = 0; i < r - i - 1; ++i)
      swap(psufy[i], psufy[r - i - 1]);
    psufy[r++] = n;
    for (int i = 0; i < psufy[0]; ++i)
      text[i] = '0';
    if (psufy[0] > 1)
      text[psufy[0]-1] = '1';
    generuj_p(0, psufy[0]);
    for (int k = 1; k < r; ++k){
      if (psufy[k-1] * 2 >= psufy[k]){ // Przypadek 1, bez dziury
        for (int i = 2 * psufy[k-1] - psufy[k]; i < psufy[k-1]; ++i)
          text[i + psufy[k] - psufy[k-1]] = text[i];
        generuj_p(psufy[k-1] + 1, psufy[k]);
      } else { // Przypadek 2, dziura
        int s = psufy[k] - 2 * psufy[k-1];
        for (int i = 0; i < s; ++i)
          text[i + psufy[k-1]] = '0';
        generuj_p(psufy[k-1] + 1, psufy[k-1] + s);
        int c = p[psufy[k-1] + s];
        if (c > 0 && (psufy[k-1] + s) % (psufy[k-1] + s - c) == 0){
          text[s + psufy[k-1] - 1] = '1';
          generuj_p(psufy[k-1] + s, psufy[k-1] + s);
        }
        for (int i = 0; i < psufy[k-1]; ++i)
          text[i + s + psufy[k-1]] = text[i];
        generuj_p(psufy[k-1] + s + 1, psufy[k]);
      }
    }
    printf("%s\n", text);
  }
  return 0;
}
