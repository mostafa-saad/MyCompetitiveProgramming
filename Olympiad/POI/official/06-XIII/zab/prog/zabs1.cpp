/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ZAB (¯aby)                                     *
 *   Plik:                zabs1.c                                        *
 *   Autor:               Jakub Pawlewicz                                *
 *   Opis:                Faza szukania odleg³o¶ci: Przegl±danie         *
 *                        wszystkich elektrod.                           *
 *                        Faza szukania szeroko¶ci: Dijkstra z u¿yciem   *
 *                        heap'a z STL'a.                                *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define INF 0x7FFFFFFF

struct point {
  int x, y;

  point() { }

  point(int x, int y) : x(x), y(y) { }

  void read()
  {
    scanf("%d%d", &x, &y);
  }

  void read1()
  {
    read();
    x--;
    y--;
  }

  point right() { return point(x + 1, y); }
  point left() { return point(x - 1, y); }
  point up() { return point(x, y + 1); }
  point down() { return point(x, y - 1); }
};

bool operator==(point a, point b)
{
  return a.x == b.x && a.y == b.y;
}

static inline int sqr(int a)
{
  return a * a;
}

static inline int dist(point a, point b)
{
  return sqr(a.x - b.x) + sqr(a.y - b.y);
}

vector<point> read_electrodes()
{
  int count;
  scanf("%d", &count);
  vector<point> electrodes(count);
  for(int i = 0; i < count; i++)
    electrodes[i].read1();
  return electrodes;
}

point size;

template <typename T>
class point_map {
  vector<T> arr;
public:
  point_map() : arr(size.x * size.y) { }

  T& operator[](const point p)
  {
    return arr[p.x + p.y * size.x];
  }
};

int dist_to_electrodes(point p, vector<point>& electrodes)
{
  int d = INF;
  for (uint i = 0; i < electrodes.size(); i++)
    d = min(d, dist(p, electrodes[i]));
  return d;
}

point_map<int> compute_dists(point size, vector<point>& electrodes)
{
  point_map<int> dist;
  point p;
  for (p.x = 0; p.x < size.x; p.x++)
    for (p.y = 0; p.y < size.y; p.y++)
      dist[p] = dist_to_electrodes(p, electrodes);
  return dist;
}

point_map<int> point_dist;

struct width_heap_elem;

struct width_heap_info {
  vector<width_heap_elem>::iterator width_heap_it;
  int width;
};

point_map<width_heap_info> width_heap_info_vec;

vector<width_heap_elem> width_heap;

struct width_heap_elem {
  point p;
  bool operator<(const width_heap_elem& elem)
  {
    return width_heap_info_vec[p].width < width_heap_info_vec[elem.p].width;
  }


  width_heap_elem& operator=(const width_heap_elem& elem)
  {
    p = elem.p;
    width_heap_info_vec[p].width_heap_it =
      width_heap.begin() + (this - &*width_heap.begin());
    return *this;
  }
};

void width_heap_init()
{
  width_heap_info_vec = point_map<width_heap_info>();
  width_heap = vector<width_heap_elem>(size.x * size.y);
  point p;
  vector<width_heap_elem>::iterator width_heap_it = width_heap.begin();
  for (p.y = 0; p.y < size.y; p.y++)
    for (p.x = 0; p.x < size.x; p.x++) {
      width_heap_info_vec[p].width_heap_it = width_heap_it;
      width_heap_info_vec[p].width = 0;
      width_heap_it->p = p;
      ++width_heap_it;
    }
}

void width_relax(point p, int width)
{
  int w = min(width, point_dist[p]);
  if (w > width_heap_info_vec[p].width) {
    width_heap_info_vec[p].width = w;
    push_heap(width_heap.begin(), width_heap_info_vec[p].width_heap_it + 1);
  }
}

int get_width_from_to(point start, point end)
{
  width_heap_init();
  width_relax(start, INF);
  while (true) {
    point p = width_heap.front().p;
    int w = width_heap_info_vec[p].width;
    if (p == end)
      return w;
    pop_heap(width_heap.begin(), width_heap.end());
    width_heap.pop_back();
    if (p.x > 0)
      width_relax(p.left(), w);
    if (p.x + 1 < size.x)
      width_relax(p.right(), w);
    if (p.y > 0)
      width_relax(p.down(), w);
    if (p.y + 1 < size.y)
      width_relax(p.up(), w);
  }
}

int main()
{
  point start, end;
  size.read();
  start.read1();
  end.read1();
  vector<point> electrodes = read_electrodes();
  point_dist = compute_dists(size, electrodes);
  printf("%d\n", get_width_from_to(start, end));
  return 0;
}
