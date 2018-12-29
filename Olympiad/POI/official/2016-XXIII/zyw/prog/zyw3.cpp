/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Zywoplot                                           *
 *   Autor programu:       Marek Sommer                                       *
 *   Zlozonosc czasowa:    O((n * m) * log(n * m))                            *
 *   Zlozonosc pamieciowa: O(n * m)                                           *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include <cassert>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

constexpr int MaxWidth = 1000;

constexpr int ZeroCost = 0;
constexpr int YewCost = 1;
constexpr int ThuyaCost = 2;
constexpr int InftyCost = 3;

struct Point {
  int x, y;
};

int m, n;

int result_number_of_thuyas, result_number_of_yews;
bool result_down[MaxWidth + 5][MaxWidth + 5];
bool result_right[MaxWidth + 5][MaxWidth + 5];

void AddEdgeToResult(Point a, Point b, bool is_yew) {
  if (is_yew) {
    result_number_of_yews++;
  } else {
    result_number_of_thuyas++;
  }
  if (a.x == b.x) {
    result_right[a.x][std::min(a.y, b.y)] = true;
  } else if (a.y == b.y) {
    result_down[std::min(a.x, b.x)][a.y] = true;
  } else {
    assert(false);
  }
}

std::vector< std::pair<int, Point> > graph[MaxWidth + 5][MaxWidth + 5];

int distance[MaxWidth + 5][MaxWidth + 5];
Point distance_is_from[MaxWidth + 5][MaxWidth + 5];
bool is_taken[MaxWidth + 5][MaxWidth + 5];

struct VertexQueueComparator {
  bool operator()(Point a, Point b) {
    if (distance[a.x][a.y] == distance[b.x][b.y]) {
      if (a.x == b.x) {
        return a.y < b.y;
      }
      return a.x < b.x;
    }
    return distance[a.x][a.y] < distance[b.x][b.y];
  }
};

std::set<Point, VertexQueueComparator> vertex_queue;

void Algorithm() {
  for (int x = 0; x <= m; x++) {
    for (int y = 0; y <= n; y++) {
      distance[x][y] = InftyCost;
    }
  }
  auto AddDistance = [](Point from_point, Point point, int dist) -> void {
    if (!is_taken[point.x][point.y] and distance[point.x][point.y] >= dist) {
      vertex_queue.erase(point);
      distance[point.x][point.y] = dist;
      distance_is_from[point.x][point.y] = from_point;
      vertex_queue.insert(point);
    }
  };
  auto IsOnBorder = [](int x, int y) -> bool {
    if (x == 0 or x == m) return true;
    if (y == 0 or y == n) return true;
    return false;
  };
  for (int x = 0; x <= m; x++) {
    for (int y = 0; y <= n; y++) {
      if (IsOnBorder(x, y)) {
        AddDistance(Point{-1, -1}, Point{x, y}, ZeroCost);
      }
    }
  }
  while (!vertex_queue.empty()) {
    Point point = *vertex_queue.begin();
    vertex_queue.erase(vertex_queue.begin());
    assert(!is_taken[point.x][point.y]);
    is_taken[point.x][point.y] = true;
    for (std::pair<int, Point> edge : graph[point.x][point.y]) {
      AddDistance(point, edge.second, edge.first);
    }
    if (!IsOnBorder(point.x, point.y)) {
      assert(distance[point.x][point.y] == YewCost
          or distance[point.x][point.y] == ThuyaCost);
      AddEdgeToResult(point, distance_is_from[point.x][point.y],
                      distance[point.x][point.y] == YewCost);
    }
  }
  for (int x = 0; x <= m; x++) {
    for (int y = 0; y <= n; y++) {
      assert(is_taken[x][y]);
    }
  }
}

int main() {
  std::cin >> m >> n;
  for (int x = 0; x < m; x++) {
    for (int y = 1; y < n; y++) {
      char c;
      std::cin >> c;
      int cost;
      if (c == 'T') {
        cost = ThuyaCost;
      } else if (c == 'C') {
        cost = YewCost;
      } else {
        assert(false);
      }
      graph[x][y].push_back(std::make_pair(cost, Point{x + 1, y}));
      graph[x + 1][y].push_back(std::make_pair(cost, Point{x, y}));
    }
  }
  for (int x = 1; x < m; x++) {
    for (int y = 0; y < n; y++) {
      char c;
      std::cin >> c;
      int cost;
      if (c == 'T') {
        cost = ThuyaCost;
      } else if (c == 'C') {
        cost = YewCost;
      } else {
        assert(false);
      }
      graph[x][y].push_back(std::make_pair(cost, Point{x, y + 1}));
      graph[x][y + 1].push_back(std::make_pair(cost, Point{x, y}));
    }
  }
  Algorithm();
  std::cout << result_number_of_yews + result_number_of_thuyas
            << " " << result_number_of_yews << "\n";
  for (int x = 0; x < m; x++) {
    for (int y = 1; y < n; y++) {
      if (result_down[x][y]) {
        std::cout << "Z";
      } else {
        std::cout << ".";
      }
    }
    std::cout << "\n";
  }
  for (int x = 1; x < m; x++) {
    for (int y = 0; y < n; y++) {
      if (result_right[x][y]) {
        std::cout << "Z";
      } else {
        std::cout << ".";
      }
    }
    std::cout << "\n";
  }
  return 0;
}
