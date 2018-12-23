// CEOI 2013 - Task: Tram - Solution
// Author: Luka Kalinovcic

#include <cstdio>
#include <map>
#include <set>
#include <vector>

using namespace std;

typedef long long llint;

llint const oo = 1000000000000000000LL;

struct Point {
  int r, c;
  Point() : r(0), c(0) {}
  Point(int r, int c) : r(r), c(c) {}
};

llint Dist(Point const& A, Point const& B) {
  llint dr = A.r - B.r;
  llint dc = A.c - B.c;
  return dr * dr + dc * dc;
}

struct Candidate {
  Point point;
  llint dist;
};

bool operator<(Candidate const& A, Candidate const& B) {
  if (A.dist != B.dist) return A.dist > B.dist;
  if (A.point.r != B.point.r) return A.point.r < B.point.r;
  return A.point.c < B.point.c;
}

struct Segment;

struct Row {
  int r;
  bool c1_occupied;
  bool c2_occupied;
  Segment *up, *down;

  Row(int r)
      : r(r), c1_occupied(false), c2_occupied(false),
        up(NULL), down(NULL) {}
};

struct Segment {
  Row* row1, *row2;
  Candidate best_seat;

  Segment(Row* row1, Row* row2)
      : row1(row1),
        row2(row2) {
    ResetBestSeat();
    row1->down = this;
    row2->up = this;
  }

  void ResetBestSeat() {
    best_seat.point = Point(row1->r, 1);
    best_seat.dist = 0;
  }

  void FindBestSeat() {
    ResetBestSeat();
    vector<Point> occupied;
    int r1 = row1->r;
    int r2 = row2->r;
    if (row1->c1_occupied) occupied.push_back(Point(r1, 1));
    if (row1->c2_occupied) occupied.push_back(Point(r1, 2));
    if (row2->c1_occupied) occupied.push_back(Point(r2, 1));
    if (row2->c2_occupied) occupied.push_back(Point(r2, 2));
    vector<Point> candidates;
    candidates.push_back(Point(r1, 1));
    candidates.push_back(Point(r1, 2));
    candidates.push_back(Point((r1 + r2) / 2, 1));
    candidates.push_back(Point((r1 + r2) / 2, 2));
    candidates.push_back(Point((r1 + r2 + 1) / 2, 1));
    candidates.push_back(Point((r1 + r2 + 1) / 2, 2));
    candidates.push_back(Point(r2, 1));
    candidates.push_back(Point(r2, 2));
    for (int i = 0; i < (int)candidates.size(); ++i) {
      Candidate seat;
      seat.point = candidates[i];
      seat.dist = oo;
      for (int j = 0; j < (int)occupied.size(); ++j) {
        llint dist = Dist(candidates[i], occupied[j]);
        if (dist < seat.dist) seat.dist = dist;
      }
      if (seat < best_seat) best_seat = seat;
    }
  }
};

struct BestSeatCmp {
  bool operator()(Segment* seg1, Segment* seg2) {
    if (seg1->best_seat < seg2->best_seat) return true;
    if (seg2->best_seat < seg1->best_seat) return false;
    return seg1->row1->r < seg2->row1->r;
  }
};

map<int, Row*> rows;

set<Segment*, BestSeatCmp> segments;

void UpdateSegment(Segment* seg) {
  if (!seg) return;
  segments.erase(seg);
  seg->FindBestSeat();
  segments.insert(seg);
}

void DeleteSegment(Segment* seg) {
  if (!seg) return;
  segments.erase(seg);
  delete seg;
}

int main() {
  int N, M;
  scanf("%d%d", &N, &M);
  rows[1] = new Row(1);
  rows[N] = new Row(N);
  segments.insert(new Segment(rows[1], rows[N]));
  UpdateSegment(rows[1]->down);

  vector<Point> points(M);
  for (int i = 0; i < M; ++i) {
    char op;
    scanf(" %c", &op);
    if (op == 'E') {
      Segment* seg = *segments.begin();
      points[i] = seg->best_seat.point;
      int r = points[i].r;
      int c = points[i].c;
      printf("%d %d\n", r, c);
      Row* row;
      if (rows.count(r)) {
        row = rows[r];
      } else {
        Row* row1 = seg->row1;
        Row* row2 = seg->row2;
        DeleteSegment(seg);
        row = new Row(r);
        rows[r] = row;
        segments.insert(new Segment(row1, row));
        segments.insert(new Segment(row, row2));
      }
      if (c == 1) {
        row->c1_occupied = true;
      } else {
        row->c2_occupied = true;
      }
      UpdateSegment(row->up);
      UpdateSegment(row->down);
    } else {
      int x;
      scanf("%d", &x); --x;
      int r = points[x].r;
      int c = points[x].c;
      Row* row = rows[r];
      if (c == 1) {
        row->c1_occupied = false;
      } else {
        row->c2_occupied = false;
      }
      if (r != 1 && r != N && !row->c1_occupied && !row->c2_occupied) {
        Row* row1 = row->up->row1;
        Row* row2 = row->down->row2;
        DeleteSegment(row->up);
        DeleteSegment(row->down);
        rows.erase(r);
        delete row;
        segments.insert(new Segment(row1, row2));
        UpdateSegment(row1->down);
      } else {
        UpdateSegment(row->up);
        UpdateSegment(row->down);
      }
    }
  }
  return 0;
}
