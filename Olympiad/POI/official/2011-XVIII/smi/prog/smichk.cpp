/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Smieci                                           *
 *   Autor:             Zbigniew Wojna                                   *
 *   Zlozonosc czasowa: O(n + m)                                         *
 *   Opis:              Program weryfikujacy wyjscia                     *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <set>
#include <vector>
#include <cstring>

#include "oi.h"

#define REP(i,n) for(int _n=n, i=0;i<_n;++i)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;--i)
#define FORE(i,x) for(__typeof((x).begin()) i=(x).begin();i != (x).end();++i)
#define X first
#define Y second
#define PB push_back	
#define MP make_pair
using namespace std;

void own_error_function(const char* msg, int line, int position) {
  printf("WRONG\n");
  exit(1);
}

/* argv[1] - test
 * argv[2] - wyjscie uzytkownika
 * argv[3] - wyjscie wzorcowki
*/
const int MAXN = 100000;
const int MAXM = 1000000;

int n, m, a, b, b1, b2, x, y, nk, k;
set<pair<int, int> > S, S2;
set<int> exist;
char answer[20];
char nie[] = "NIE";

int main(int argc, char **argv){
  oi::Scanner in(argv[1], own_error_function, oi::PL);
  oi::Scanner out(argv[2], own_error_function, oi::PL);
  oi::Scanner out_correct(argv[3], own_error_function, oi::PL);
  
  out_correct.readString(answer, 20);
  if(strcmp(answer, nie) == 0){
    out.readString(answer, 20);
    out.readEofOrEoln();
    if(strcmp(answer, nie) == 0){
      printf("OK\n");
      return 0;}
    else
      out.error("zle");
  }
	
  n = in.readInt(1, MAXN); in.readSpace();
  m = in.readInt(1, MAXM); in.readEoln();
  REP(i, m) {
    a = in.readInt(1, n); in.readSpace();
    b = in.readInt(1, n); in.readSpace();
    b1 = in.readInt(0, 1); in.readSpace();
    b2 = in.readInt(0, 1); in.readEoln();
    if(b1 != b2){
      S.insert(MP(a,b));
      S.insert(MP(b,a));
    }	  
  }

  nk = out.readInt(0, MAXM); out.skipWhitespaces();
  REP(i, nk){
    k = out.readInt(0, n); out.skipWhitespaces();
    x = out.readInt(1, n); out.skipWhitespaces();
    REP(i, k){
      y = out.readInt(1, n); out.skipWhitespaces();
      if(S2.find(MP(x,y)) == S2.end()){
	S2.insert(MP(x,y));
	S2.insert(MP(y,x));
      } else {
	S2.erase(MP(x,y));
        S2.erase(MP(y,x));
      }
      exist.clear();
      if(exist.find(y) != exist.end())
        out.error("cykl nie jest prosty");
      else
        exist.insert(y);
      x = y;
    }
  }

  if(S == S2)
    printf("OK\n");
  else
    out.error("nie zgadzaja sie cykle pokrywajace\n");

  return 0;
};
