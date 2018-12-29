/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Licytacja                                        *
 *   Autor:             Karol Pokorski                                   *
 *   Zlozonosc czasowa: O(n log^2 n)                                     *
 *   Opis:              Rozwiazanie autorskie                            *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
#include "cliclib.h"
using namespace std;

const int MAXN = 30001;
const int MAXLOG2 = 15;
const int MAXLOG3 = 10;

struct TState {
  // struktura reprezentujaca stan:
  // stones - liczba kamieni na stosie
  // stake2 - liczba czynnikow 2 w stawce
  // stake3 - liczba czynnikow 3 w stawce

  int pot, stake2, stake3;
  TState(int a, int b, int c):
    pot(a), stake2(b), stake3(c) {}
};

int pwr2[MAXLOG2], pwr3[MAXLOG3];
vector<TState> adj[MAXN][MAXLOG2][MAXLOG3]; // graf przejsc pomiedzy pozycjami
vector<TState> topSort;
bool visited[MAXN][MAXLOG2][MAXLOG3], winning[MAXN][MAXLOG2][MAXLOG3];

void Dfs(int pot, int stake2, int stake3) {
  if (visited[pot][stake2][stake3])
    return;
  
  visited[pot][stake2][stake3] = true;

  for (int i = 0; i < adj[pot][stake2][stake3].size(); i++) {
    TState next = adj[pot][stake2][stake3][i];

    Dfs(next.pot, next.stake2, next.stake3);
  }
  
  topSort.push_back(TState(pot, stake2, stake3));
}

TState MakeMove(TState cur, int moveType) {
  if (moveType == 1)
    return TState(cur.pot+pwr2[cur.stake2]*pwr3[cur.stake3], 0, 0);
  if (moveType == 2)
    return TState(cur.pot, cur.stake2+1, cur.stake3);
  if (moveType == 3)
    return TState(cur.pot, cur.stake2, cur.stake3+1);
}

int main() {
  int n, temp;

  n = inicjuj();

  // obliczamy kolejne potegi dwojki
  temp = 1;
  for (int i = 0; i < MAXLOG2; (i++, temp *= 2))
    pwr2[i] = temp;
  
  // obliczamy kolejne potegi trojki
  temp = 1;
  for (int i = 0; i < MAXLOG3; (i++, temp *= 3))
    pwr3[i] = temp;

  // generujemy graf przejsc miedzy pozycjami
  for (int i = 0; i < n; i++)
    for (int j = 0; i+pwr2[j] < n; j++)
      for (int k = 0; i+pwr2[j]*pwr3[k] < n; k++) {
        adj[i][j][k].push_back(TState(i+pwr2[j]*pwr3[k], 0, 0)); // pas
        adj[i][j][k].push_back(TState(i, j+1, k)); // podwojenie stawki
        adj[i][j][k].push_back(TState(i, j, k+1)); // potrojenie stawki
      }

  // obliczamy posortowanie topologiczne
  Dfs(0, 0, 0);
  reverse(topSort.begin(), topSort.end());

  // obliczamy, ktore pozycje sa wygrywajace, a ktore przegrywajace
  for (int i = topSort.size()-1; i >= 0; i--) {
    TState cur = topSort[i];

    for (int j = 0; j < adj[cur.pot][cur.stake2][cur.stake3].size(); j++) {
      TState next = adj[cur.pot][cur.stake2][cur.stake3][j];

      winning[cur.pot][cur.stake2][cur.stake3] = max(winning[cur.pot][cur.stake2][cur.stake3], !winning[next.pot][next.stake2][next.stake3]);
    }

  }

  TState curGame = TState(0, 0, 0);

  // teraz gramy w gre
  while (true) {
    int playerMove = 1, opponentMove;

    if (winning[curGame.pot][curGame.stake2][curGame.stake3]) { // jestesmy na pozycji wygrywajacej
      for (int i = 0; i < adj[curGame.pot][curGame.stake2][curGame.stake3].size(); i++) {
        TState posMove = adj[curGame.pot][curGame.stake2][curGame.stake3][i];

        if (!winning[posMove.pot][posMove.stake2][posMove.stake3]) {
          playerMove = i+1;
        }
      }
    }

    curGame = MakeMove(curGame, playerMove);
    alojzy(playerMove);
    opponentMove = bajtazar();
    curGame = MakeMove(curGame, opponentMove);
  }

  return 0;
}
