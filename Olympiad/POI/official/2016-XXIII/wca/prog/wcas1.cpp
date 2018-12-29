/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Wcale nie Nim                                      *
 *   Autor programu:       Karol Pokorski                                     *
 *   Opis:                 rozwiazanie naiwne                                 *
 *                         Zero obserwacji                                    *
 *                         po prostu maksymalnie naiwna implementacja min-max *
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

      for (int j = 0; j < a; j++) {
        state[i].first = min(j, b);
        state[i].second = max(j, b);
        int result = 1 + MinMax(state, 1);
        bestResult = min(bestResult, result);
        state[i].first = a;
        state[i].second = b;
      }
      for (int j = 0; j < b; j++) {
        state[i].first = min(j, a);
        state[i].second = max(j, a);
        int result = 1 + MinMax(state, 1);
        bestResult = min(bestResult, result);
        state[i].first = a;
        state[i].second = b;
      }
    }

    M[make_pair(state, player)] = bestResult;
  }
  else {
    int bestResult = 0;

    for (int i = 0; i < (int)state.size(); i++) {
      int a = state[i].first, b = state[i].second;
      if (a > b) swap(a, b);

      for (int j = 0; j <= a+b; j++) {
        if ((a == b) && (j == a)) continue;

        state[i].first = min(j, a+b-j);
        state[i].second = max(j, a+b-j);
        int result = 1 + MinMax(state, 0);
        bestResult = max(bestResult, result);
        state[i].first = a;
        state[i].second = b;
      }
    }

    M[make_pair(state, player)] = bestResult;
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
