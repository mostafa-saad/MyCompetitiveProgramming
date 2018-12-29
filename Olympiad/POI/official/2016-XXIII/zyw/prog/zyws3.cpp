/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Zywoplot                                           *
 *   Autor programu:       Marek Sommer                                       *
 *   Zlozonosc czasowa:    O((n * m)^2)                                       *
 *   Zlozonosc pamieciowa: O(n * m)                                           *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/


#include <cassert>
#include <cstdio>

constexpr int MaxWidth = 1000;

enum class Tree {
  Yew, Thuya
};

int m, n;
Tree tree_right[MaxWidth + 5][MaxWidth + 5];
Tree tree_down[MaxWidth + 5][MaxWidth + 5];
int result_number_of_yews, result_number_of_thuyas;
bool result_right[MaxWidth + 5][MaxWidth + 5];
bool result_down[MaxWidth + 5][MaxWidth + 5];

constexpr int DistanceZero = 0;
constexpr int DistanceThuya = 1;
constexpr int DistanceYew = 2;
constexpr int DistanceInfty = 3;
int distance[MaxWidth + 5][MaxWidth + 5];
bool* which_edge[MaxWidth + 5][MaxWidth + 5];
int* which_tree[MaxWidth + 5][MaxWidth + 5];
bool taken[MaxWidth + 5][MaxWidth + 5];

void Algorithm() {
  for (int x = 1; x <= m; x++) {
    for (int y = 1; y <= n; y++) {
      distance[x][y] = DistanceInfty;
      taken[x][y] = false;
    }
  }
  distance[1][1] = DistanceZero;
  which_edge[1][1] = &taken[0][0];  // Binds to an unused variable.
  which_tree[1][1] = &distance[0][0];  // Binds to an unused variable.
  while (true) {
    int x = -1, y = -1, dist = DistanceInfty;
    for (int nx = 1; nx <= m; nx++) {
      for (int ny = 1; ny <= n; ny++) {
        if (!taken[nx][ny] and distance[nx][ny] < dist) {
          dist = distance[nx][ny];
          x = nx;
          y = ny;
        }
      }
    }
    if (dist == DistanceInfty) {
      break;
    }
    taken[x][y] = true;
    *which_edge[x][y] = true;
    *which_tree[x][y] -= 1;
    auto UpdateDistance = [](int x, int y, Tree tree, bool& edge) -> void {
      const int new_dist = (tree == Tree::Yew) ? DistanceYew : DistanceThuya;
      if (new_dist < distance[x][y]) {
        distance[x][y] = new_dist;
        which_edge[x][y] = &edge;
        if (tree == Tree::Yew) {
          which_tree[x][y] = &result_number_of_yews;
        } else {
          which_tree[x][y] = &result_number_of_thuyas;
        }
      }
    };
    if (x > 1) {
      UpdateDistance(x - 1, y, tree_down[x - 1][y], result_down[x - 1][y]);
    }
    if (x < m) {
      UpdateDistance(x + 1, y, tree_down[x][y], result_down[x][y]);
    }
    if (y > 1) {
      UpdateDistance(x, y - 1, tree_right[x][y - 1], result_right[x][y - 1]);
    }
    if (y < n) {
      UpdateDistance(x, y + 1, tree_right[x][y], result_right[x][y]);
    }
  }
}

void ReadInput() {
  auto ReadTreeInto = [](Tree& tree) -> void {
    char c;
    scanf(" %c", &c);
    if (c == 'C') {
      tree = Tree::Yew;
      result_number_of_yews++;
    } else if (c == 'T') {
      tree = Tree::Thuya;
      result_number_of_thuyas++;
    } else {
      assert(false);
    }
  };
  scanf("%d%d", &m, &n);
  for (int x = 1; x <= m; x++) {
    for (int y = 1; y < n; y++) {
      ReadTreeInto(tree_right[x][y]);
    }
  }
  for (int x = 1; x < m; x++) {
    for (int y = 1; y <= n; y++) {
      ReadTreeInto(tree_down[x][y]);
    }
  }
}

void PrintOutput() {
  printf("%d %d\n", result_number_of_yews + result_number_of_thuyas,
                    result_number_of_yews);
  for (int x = 1; x <= m; x++) {
    for (int y = 1; y < n; y++) {
      if (result_right[x][y]) {
        printf(".");
      } else {
        printf("Z");
      }
    }
    printf("\n");
  }
  for (int x = 1; x < m; x++) {
    for (int y = 1; y <= n; y++) {
      if (result_down[x][y]) {
        printf(".");
      } else {
        printf("Z");
      }
    }
    printf("\n");
  }
}

int main() {
  ReadInput();
  Algorithm();
  PrintOutput();
  return 0;
}
