/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Drogi zmiennokierunkowe                            *
 *   Autor programu:       Marek Sommer                                       *
 *   Zlozonosc czasowa:    O(m + n^2)                                         *
 *   Zlozonosc pamieciowa: O(n + m)                                           *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/

#include <algorithm>
#include <vector>

constexpr int MaxN = 500 * 1000;
constexpr int MaxM = 1000 * 1000;

int losuj(int a, int b) {
  return rand() % (b - a + 1) + a;
}

int n, m;
std::vector<int> graf[MaxN + 5];
std::vector<int> graf_t[MaxN + 5];

int post_order_l;
int post_order[MaxN + 5];
bool odw[MaxN + 5];

void post_order_dfs(int w) {
  if (odw[w]) {
    return;
  }
  odw[w] = true;
  for (int i : graf[w]) {
    post_order_dfs(i);
  }
  post_order[++post_order_l] = w;
}

int skladowe;
int id[MaxN + 5];
std::vector<int> zbior[MaxN + 5];
std::vector<int> dag[MaxN + 5];

void dfs_id(int w) {
  if (id[w] != 0) {
    return;
  }
  id[w] = skladowe;
  zbior[skladowe].push_back(w);
  for (int i : graf_t[w]) {
    dfs_id(i);
  }
}

bool ok_dag[MaxN + 5];
bool ok[MaxN + 5];

std::vector<int> dag_t[MaxN + 5];
int porzadek_topologiczny[MaxN + 5];  // Na pozycjach 1..skladowe
int porzadek_topologiczny_t[MaxN + 5];  // Odwrotna permutacja.
int stopien[MaxN + 5];
bool da_sie_wszedzie[MaxN + 5];
int najbardziej_prawy[MaxN + 5];

bool CzyWyeliminowac(int pos) {
  for (int i = pos + 1; i <= skladowe; i++) {
    const int w_i = porzadek_topologiczny[i];
    if (najbardziej_prawy[w_i] < pos) {
      return true;
    } else if (da_sie_wszedzie[w_i]) {
      return false;
    }
  }
  return false;
}

void EliminujOdLewejDoPrawej() {
  for (int i = 1; i <= skladowe; i++) {
    najbardziej_prawy[i] = 0;
    for (int j : dag_t[i]) {
      najbardziej_prawy[i]
          = std::max(najbardziej_prawy[i], porzadek_topologiczny_t[j]);
    }
  }
  for (int i = skladowe; i >= 1; i--) {
    const int w = porzadek_topologiczny[i];
    if (ok_dag[w]) {
      if (CzyWyeliminowac(i)) {
        ok_dag[porzadek_topologiczny[i]] = false;
        da_sie_wszedzie[w] = false;
      } else {
        da_sie_wszedzie[w] = true;
      }
    } else {
      da_sie_wszedzie[w] = false;
    }
  }
}

void LosujPorzadekTopologiczny() {
  std::vector<int> kolejka;
  for (int i = 1; i <= skladowe; i++) {
    stopien[i] = dag_t[i].size();
    if (stopien[i] == 0) {
      kolejka.push_back(i);
    }
  }
  for (int i = 1; i <= skladowe; i++) {
    const int pos = losuj(0, (int) kolejka.size() - 1);
    const int w = kolejka[pos];
    std::swap(kolejka[pos], kolejka.back());
    kolejka.pop_back();
    porzadek_topologiczny[i] = w;
    porzadek_topologiczny_t[w] = i;
    for (int j : dag[w]) {
      stopien[j]--;
      if (stopien[j] == 0) {
        kolejka.push_back(j);
      }
    }
  }
}

// Odwraca krawędzie w dagu i zmienia wszystkie dane dotyczące dagu tak, aby
// wszystko pasowało.
void OdwrocDag() {
  for (int i = 1; i <= skladowe; i++) {
    std::swap(dag[i], dag_t[i]);
  }
  std::reverse(porzadek_topologiczny + 1, porzadek_topologiczny + skladowe + 1);
  for (int i = 1; i <= skladowe; i++) {
    porzadek_topologiczny_t[porzadek_topologiczny[i]] = i;
  }
}

void RozwiazDag() {
  for (int i = 1; i <= n; i++) {
    for (int j : dag[i]) {
      dag_t[j].push_back(i);
    }
  }

  LosujPorzadekTopologiczny();

  // Początkowo, każdy wierzchołek jest potencjalnie dobry.
  for (int i = 1; i <= skladowe; i++) {
    ok_dag[i] = true;
  }

  EliminujOdLewejDoPrawej();
  OdwrocDag();
  EliminujOdLewejDoPrawej();
}

int main() {
  std::srand(52742);
  scanf("%d%d", &n, &m);
  while (m--) {
    int a, b;
    scanf("%d%d", &a, &b);
    graf[a].push_back(b);
    graf_t[b].push_back(a);
  }
  for (int i = 1; i <= n; i++) {
    post_order_dfs(i);
  }
  for (int i = n; i >= 1; i--) {
    const int w = post_order[i];
    if (id[w] == 0) {
      skladowe++;
      dfs_id(w);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j : graf[i]) {
      const int a = id[i];
      const int b = id[j];
      if (a != b) {
        dag[a].push_back(b);
      }
    }
  }
  RozwiazDag();
  for (int i = 1; i <= skladowe; i++) {
    if (ok_dag[i]) {
      for (int j : zbior[i]) {
        ok[j] = true;
      }
    }
  }
  int ile = 0;
  for (int i = 1; i <= n; i++) {
    if (ok[i]) {
      ile++;
    }
  }
  printf("%d\n", ile);
  bool pierwsze = true;
  for (int i = 1; i <= n; i++) {
    if (ok[i]) {
      if (pierwsze) {
        pierwsze = false;
      } else {
        printf(" ");
      }
      printf("%d", i);
    }
  }
  printf("\n");
  return EXIT_SUCCESS;
}
