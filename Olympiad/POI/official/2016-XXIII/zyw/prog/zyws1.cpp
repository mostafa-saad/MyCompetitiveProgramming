/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Zywoplot                                           *
 *   Zlozonosc czasowa:    O(2^(2nm - n - m) * nm)                            *
 *   Zlozonosc pamieciowa: O(n * m)                                           *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/

#include <algorithm>
#include <cassert>
#include <cstdio>

constexpr int MaxWidth = 1000;

enum class Tree {
  Yew, Thuya
};

int m, n;

//             --- y -->                        y
//         1   2   . . .   n        +-----------------------+
//       +---+---+---+---+---+      |                       |
//     1 |   |   |   |   |   |      |   tree_right[x][y]    |
//       +---+---+---+---+---+      |          |            |
//  |  2 |   |   |   |   |   |      |          +----------->|
//  |    +---+---+---+---+---+    x |                       |
//  x  . |   |   |   |   |   |      |   tree_down[x][y]     |
//  |  . +---+---+---+---+---+      |        |              |
//  V  . |   |   |   |   |   |      |        |              |
//       +---+---+---+---+---+      |        V              |
//     m |   |   |   |   |   |      +-----------------------+
//       +---+---+---+---+---+
Tree tree_right[MaxWidth + 5][MaxWidth + 5];
Tree tree_down[MaxWidth + 5][MaxWidth + 5];
int result_number_of_yews = -1, result_number_of_thuyas;
bool result_right[MaxWidth + 5][MaxWidth + 5];
bool result_down[MaxWidth + 5][MaxWidth + 5];
int tmp_result_number_of_yews, tmp_result_number_of_thuyas;
bool tmp_result_right[MaxWidth + 5][MaxWidth + 5];
bool tmp_result_down[MaxWidth + 5][MaxWidth + 5];

bool TmpCanMove(int from_x, int from_y, int to_x, int to_y) {
  if (!(1 <= from_x and from_x <= m and 1 <= to_x and to_x <= m
      and 1 <= from_y and from_y <= n and 1 <= to_y and to_y <= n)) {
    return false;
  }
  if (from_x == to_x) {
    const int min_y = std::min(from_y, to_y);
    const int max_y = std::max(from_y, to_y);
    if (min_y + 1 != max_y) {
      return false;
    }
    return !tmp_result_right[from_x][min_y];
  } else if (from_y == to_y) {
    const int min_x = std::min(from_x, to_x);
    const int max_x = std::max(from_x, to_x);
    if (min_x + 1 != max_x) {
      return false;
    }
    return !tmp_result_down[min_x][from_y];
  } else {
    return false;
  }
}

bool visited[MaxWidth + 5][MaxWidth + 5];

bool Dfs(int x, int y, int from_x, int from_y) {
  if (visited[x][y]) {
    return false;
  }
  visited[x][y] = true;
  for (int nx = x - 1; nx <= x + 1; nx++) {
    for (int ny = y - 1; ny <= y + 1; ny++) {
      if (nx != from_x or ny != from_y) {
        if (TmpCanMove(x, y, nx, ny)) {
          if (!Dfs(nx, ny, x, y)) {
            return false;
          }
        }
      }
    }
  }
  return true;
}

// Checks wheter it is possible to get to every field in a unique way,
// starting from field (x, y).
bool CheckConnectivity(int xx, int yy) {
  for (int x = 1; x <= m; x++) {
    for (int y = 1; y <= n; y++) {
      visited[x][y] = false;
    }
  }
  if (!Dfs(xx, yy, -1, -1)) {
    return false;
  }
  for (int x = 1; x <= m; x++) {
    for (int y = 1; y <= n; y++) {
      if (!visited[x][y]) {
        return false;
      }
    }
  }
  return true;
}

// Checks wheter planting trees as described in tmp_result_* tables is correct.
bool IsTmpCorrect() {
  return CheckConnectivity(1, (n + 1) / 2)
      and CheckConnectivity(m, (n + 1) / 2);
}

void Algorithm() {
  const int number_of_edges = (m - 1) * n + m * (n - 1);
  if (number_of_edges > 30) {
    while (true);
  }
  for (int i = 0; i < (1 << number_of_edges); i++) {
    int mask = i;
    tmp_result_number_of_yews = 0;
    tmp_result_number_of_thuyas = 0;
    for (int x = 1; x <= m; x++) {
      for (int y = 1; y < n; y++) {
        if (mask & 1) {
          tmp_result_right[x][y] = true;
          if (tree_right[x][y] == Tree::Yew) {
            tmp_result_number_of_yews++;
          } else {
            tmp_result_number_of_thuyas++;
          }
        } else {
          tmp_result_right[x][y] = false;
        }
        mask >>= 1;
      }
    }
    for (int x = 1; x < m; x++) {
      for (int y = 1; y <= n; y++) {
        if (mask & 1) {
          tmp_result_down[x][y] = true;
          if (tree_down[x][y] == Tree::Yew) {
            tmp_result_number_of_yews++;
          } else {
            tmp_result_number_of_thuyas++;
          }
        } else {
          tmp_result_down[x][y] = false;
        }
        mask >>= 1;
      }
    }
    if (IsTmpCorrect()) {
      if (tmp_result_number_of_yews >= result_number_of_yews) {
        result_number_of_yews = tmp_result_number_of_yews;
        result_number_of_thuyas = tmp_result_number_of_thuyas;
        for (int x = 1; x <= m; x++) {
          for (int y = 1; y < n; y++) {
            result_right[x][y] = tmp_result_right[x][y];
          }
        }
        for (int x = 1; x < m; x++) {
          for (int y = 1; y <= n; y++) {
            result_down[x][y] = tmp_result_down[x][y];
          }
        }
      }
    }
  }
}

void ReadInput() {
  scanf("%d%d", &m, &n);
  for (int x = 1; x <= m; x++) {
    for (int y = 1; y < n; y++) {
      char c;
      scanf(" %c", &c);
      if (c == 'C') {
        tree_right[x][y] = Tree::Yew;
      } else if (c == 'T') {
        tree_right[x][y] = Tree::Thuya;
      } else {
        assert(false);
      }
    }
  }
  for (int x = 1; x < m; x++) {
    for (int y = 1; y <= n; y++) {
      char c;
      scanf(" %c", &c);
      if (c == 'C') {
        tree_down[x][y] = Tree::Yew;
      } else if (c == 'T') {
        tree_down[x][y] = Tree::Thuya;
      } else {
        assert(false);
      }
    }
  }
}

void PrintOutput() {
  printf("%d %d\n", result_number_of_yews + result_number_of_thuyas,
                    result_number_of_yews);
  for (int x = 1; x <= m; x++) {
    for (int y = 1; y < n; y++) {
      if (result_right[x][y]) {
        printf("Z");
      } else {
        printf(".");
      }
    }
    printf("\n");
  }
  for (int x = 1; x < m; x++) {
    for (int y = 1; y <= n; y++) {
      if (result_down[x][y]) {
        printf("Z");
      } else {
        printf(".");
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
