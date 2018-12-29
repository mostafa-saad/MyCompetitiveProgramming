/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Hydrorozgrywka                                     *
 *   Autor programu:       Wojtek Nadara                                      *
 *   Zlozonosc czasowa:    O(n * 2^m)                                         *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/


#include <iostream>
#include <vector>
#include <utility>

using namespace std;

const int N = 20;
vector<pair<int, int> > slo[N];
// W winner[v][mask] przetrzymujemy informacje o tym, kto wygra jezeli
// zajete sa krawedzie, ktorym odpowiadaja zapalone bity w mask
// i aktualnie znajdujemy sie w wierzcholku w v
int winner[N + 2][(1 << N) + 2];

void rec(int act_n, int mask) {
  bool can_win = false;
  if (winner[act_n][mask]) {
    return;
  }
  for (auto e : slo[act_n]) {
    int nei = e.first;
    int e_nr = e.second;
    // Jezeli krawedz byla juz uzyta
    if (mask & (1 << e_nr)) {
      continue;
    }
    int new_mask = (mask | (1 << e_nr));
    rec(nei, new_mask);
    can_win |= (winner[nei][new_mask] == 2);
  }
  // Jezeli istnieje krawedz prowadzaca do stanu, w ktorym wygra drugi gracz
  // dla tamtego stanu (czyli de facto pierwszy gracz w naszym aktualnym stanie),
  // to pierwszy gracz w aktualnym stanie moze wygrac
  if (can_win) {
    winner[act_n][mask] = 1;
  } else {
    winner[act_n][mask] = 2;
  }
}   

int main() {
  ios_base::sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  if (m > N) {
    while (1);
  }
  for (int i = 1; i <= m; i++) {
    int a, b;
    cin >> a >> b;
    slo[a].push_back(make_pair(b, i - 1));
    slo[b].push_back(make_pair(a, i - 1));
  }
  for (int i = 1; i <= n; i++) {
    rec(i, 0);
    cout << winner[i][0] << "\n";
  }
  return 0;
}
    