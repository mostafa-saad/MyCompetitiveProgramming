/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Wcale nie Nim                                      *
 *   Autor programu:       Karol Pokorski                                     *
 *   Opis:                 rozwiazanie naiwne                                 *
 *                         Dla kazdego gracza, dla kazdej ustalonej gry,      *
 *                         wie ktory ruch jest optymalny.                     *
 *                         Nie wie natomiast dla gracza A,                    *
 *                         w ktorej grze nalezy wykonac ruch.                 *
 *****************************************************************************/


#include <cstdio>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 500005;
const int INF = 99999999;

int n;
vector<pair<int,int> > games;
map<pair<vector<pair<int,int> >, int>, int> M;

int MinMax(vector<pair<int,int> > state, int player) {
  sort(state.begin(), state.end());

  if (M.count(make_pair(state, player)) == 1)
    return M[make_pair(state, player)];

  if (player == 0) {
    int bestResult = INF;

    for (int i = 0; i < (int)state.size(); i++) {
      int a = state[i].first, b = state[i].second;
      if (a > b) swap(a, b);
      if (b == 0) continue;
      state[i].first = 0;
      state[i].second = a;
      int result = 1 + MinMax(state, 1);
      bestResult = min(result, bestResult);
      state[i].first = a;
      state[i].second = b;
    }
    
    M[make_pair(state, player)] = bestResult;
  }
  else {
    int bestDiff = -1, bestElem = -1, bestIndex = -1;
    for (int i = 0; i < (int)state.size(); i++) {
      int a = state[i].first, b = state[i].second;
      if (a > b) swap(a, b);
      if (b == 0) continue;
      int diff = b-a;
      if (diff > bestDiff) {
        bestDiff = diff;
        bestElem = a;
        bestIndex = i;
      }
      else if ((diff == bestDiff) && (a > bestElem)) {
        bestDiff = diff;
        bestElem = a;
        bestIndex = i;
      }
    }

    int result = 0;

    if (bestIndex != -1) {  
      int a = state[bestIndex].first, b = state[bestIndex].second;
      if (a == b) {
        state[bestIndex].first = a-1;
        state[bestIndex].second = b+1;
      }
      else {
        state[bestIndex].first = (a+b) / 2;
        state[bestIndex].second = (a+b+1) / 2;
      }
      result = 1 + MinMax(state, 0);
      state[bestIndex].first = a;
      state[bestIndex].second = b;
    }
    
    M[make_pair(state, player)] = result;
  }

  return M[make_pair(state, player)];
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int size;
    scanf("%d", &size);
    games.push_back(make_pair(size, size));
  }

  printf("%d\n", MinMax(games, 0));

  return 0;
}
