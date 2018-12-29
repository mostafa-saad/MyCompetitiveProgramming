/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Zywoplot                                           *
 *   Autor programu:       Marek Sommer                                       *
 *   Zlozonosc czasowa:    O(n * m * find_union(n * m))                       *
 *   Zlozonosc pamieciowa: O(n * m)                                           *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include <cassert>
#include <cstdio>
#include <vector>

constexpr int MaxWidth = 1000;

int m, n;

// Punkty na planszy:
//          ----- y ---->
//      0   1   2   3  ...  n
//    0 +---+---+---+---+---+
//      |   |   |   |   |   |
// |  1 +---+---+-(1,3)-+---+
// |    |   |   |   |   |   |
// x  . +-(2,1)-+---+---+---+
// |  . |   |   |   |   |   |
// v  . +---+---+---+---+---+
//      |   |   |   |   |   |
//    m +---+---+---+---+-(m,n)
struct Point {
  int x, y;

  Point(int x, int y) : x(x), y(y) {
    assert(0 <= x and x <= m);
    assert(0 <= y and y <= n);
  }

  Point() : x(0), y(0) {}
  Point(const Point& point) = default;
  Point(Point&& point) = default;
  Point& operator=(const Point& point) = default;

  const Point point_down() const {
    assert(x < m);
    return Point(x + 1, y);
  }

  const Point point_right() const {
    assert(y < n);
    return Point(x, y + 1);
  }

  bool operator==(const Point& point) const {
    return x == point.x and y == point.y;
  }
};

struct Edge {
  enum class Direction {
    Down, Right
  };

  Edge(const Point& point, const Direction direction)
      : point(point), direction(direction) {}

  const Point neighbour() const {
    if (direction == Direction::Down) {
      return point.point_down();
    } else if (direction == Direction::Right) {
      return point.point_right();
    } else {
      assert(false);
    }
  }

  Point point;
  Direction direction;
};

Point fu_id[MaxWidth + 1][MaxWidth + 1];

Point fu_find(const Point& point) {
  if (fu_id[point.x][point.y] == point) {
    return point;
  }
  return fu_id[point.x][point.y] = fu_find(fu_id[point.x][point.y]);
}

void fu_union(Point point_a, Point point_b) {
  point_a = fu_find(point_a);
  point_b = fu_find(point_b);
  fu_id[point_a.x][point_a.y] = point_b;
}

bool fu_connected(const Point& point_a, const Point& point_b) {
  return fu_find(point_a) == fu_find(point_b);
}

std::vector<Edge> yews, thuyas;

int result_number_of_yews_taken;
int result_number_of_thuyas_taken;
bool is_edge_down_taken[MaxWidth][MaxWidth];
bool is_edge_right_taken[MaxWidth][MaxWidth];

void Algorithm() {
  for (int x = 0; x <= m; x++) {
    for (int y = 0; y <= n; y++) {
      fu_id[x][y] = Point(x, y);
    }
  }
  // Łączy brzegi planszy w find&union.
  for (int x = 0; x < m; x++) {
    fu_union(Point(x, 0), Point(x, 0).point_down());
    fu_union(Point(x, n), Point(x, n).point_down());
  }
  for (int y = 0; y < n; y++) {
    fu_union(Point(0, y), Point(0, y).point_right());
    fu_union(Point(m, y), Point(m, y).point_right());
  }
  // Bierze tyle cisów ile się da.
  for (const Edge& edge : yews) {
    if (!fu_connected(edge.point, edge.neighbour())) {
      fu_union(edge.point, edge.neighbour());
      result_number_of_yews_taken++;
      if (edge.direction == Edge::Direction::Down) {
        is_edge_down_taken[edge.point.x][edge.point.y] = true;
      } else if (edge.direction == Edge::Direction::Right) {
        is_edge_right_taken[edge.point.x][edge.point.y] = true;
      } else {
        assert(false);
      }
    }
  }
  // Wypełnia resztę tujami.
  for (const Edge& edge : thuyas) {
    if (!fu_connected(edge.point, edge.neighbour())) {
      fu_union(edge.point, edge.neighbour());
      result_number_of_thuyas_taken++;
      if (edge.direction == Edge::Direction::Down) {
        is_edge_down_taken[edge.point.x][edge.point.y] = true;
      } else if (edge.direction == Edge::Direction::Right) {
        is_edge_right_taken[edge.point.x][edge.point.y] = true;
      } else {
        assert(false);
      }
    }
  }
}

void ReadData() {
  scanf("%d%d", &m, &n);
  for (int x = 0; x < m; x++) {
    for (int y = 1; y < n; y++) {
      char tree_type;
      scanf(" %c", &tree_type);
      const Edge edge(Point(x, y), Edge::Direction::Down);
      if (tree_type == 'C') {
        yews.push_back(edge);
      } else if (tree_type == 'T') {
        thuyas.push_back(edge);
      } else {
        assert(false);
      }
    }
  }
  for (int x = 1; x < m; x++) {
    for (int y = 0; y < n; y++) {
      char tree_type;
      scanf(" %c", &tree_type);
      const Edge edge(Point(x, y), Edge::Direction::Right);
      if (tree_type == 'C') {
        yews.push_back(edge);
      } else if (tree_type == 'T') {
        thuyas.push_back(edge);
      } else {
        assert(false);
      }
    }
  }
}

void WriteResult() {
  printf("%d %d\n",
         result_number_of_yews_taken + result_number_of_thuyas_taken,
         result_number_of_yews_taken);
  for (int x = 0; x < m; x++) {
    for (int y = 1; y < n; y++) {
      if (is_edge_down_taken[x][y]) {
        printf("Z");
      } else {
        printf(".");
      }
    }
    printf("\n");
  }
  for (int x = 1; x < m; x++) {
    for (int y = 0; y < n; y++) {
      if (is_edge_right_taken[x][y]) {
        printf("Z");
      } else {
        printf(".");
      }
    }
    printf("\n");
  }
}

int main() {
  ReadData();
  Algorithm();
  WriteResult();
  return 0;
}
