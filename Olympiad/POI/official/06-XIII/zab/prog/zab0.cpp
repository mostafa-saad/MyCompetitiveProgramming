/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ZAB (¯aby)                                     *
 *   Plik:                zab0.cpp                                       *
 *   Autor:               Jakub Pawlewicz                                *
 *   Opis:                Faza szukania odleg³o¶ci: Algorytm wêdrowców   *
 *                        z u¿yciem heap'a z STL'a.                      *
 *                        Faza szukania szeroko¶ci: Dijkstra z u¿yciem   *
 *                        heap'a z STL'a                                 *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define INF 0x7FFFFFFF

enum direction {
  RIGHT,
  UP,
  LEFT,
  DOWN
};

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
  point up() { return point(x, y + 1); }
  point left() { return point(x - 1, y); }
  point down() { return point(x, y - 1); }

  template <direction d> point move();
};
 
template<> inline point point::move<RIGHT>() { return right(); }
template<> inline point point::move<UP>() { return up(); }
template<> inline point point::move<LEFT>() { return left(); }
template<> inline point point::move<DOWN>() { return down(); }

static inline bool operator==(const point a, const point b)
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
  void init()
  {
    arr = vector<T>(size.x * size.y);
  }

  void clear()
  {
    arr.clear();
  }
  
  T& operator[](const point p)
  {
    return arr[p.x + p.y * size.x];
  }
};

struct dist_info {
  int dist;
  point source;

  dist_info() : dist(INF) { }
  dist_info(int dist, point source) : dist(dist), source(source) { }
};

template <direction d>
static bool good_direction(point my_source, point nearer_source);
template<> static inline
bool good_direction<RIGHT>(point m, point n) { return n.x < m.x; }
template<> static inline
bool good_direction<UP>(point m, point n) { return n.y < m.y; }
template<> static inline
bool good_direction<LEFT>(point m, point n) { return m.x < n.x; }
template<> static inline
bool good_direction<DOWN>(point m, point n) { return m.y < n.y; }

template <direction d> static bool can_move(point p);
template<>
static inline bool can_move<RIGHT>(point p) { return p.x + 1 < size.x; }
template<>
static inline bool can_move<UP>(point p) { return p.y + 1 < size.y; }
template<>
static inline bool can_move<LEFT>(point p) { return p.x > 0; }
template<>
static inline bool can_move<DOWN>(point p) { return p.y > 0; }

point_map<dist_info> dist_info_vec;

template <typename Dummy> struct walker_impl;

typedef walker_impl<void> walker;

vector<walker> walk_heap;

void walk_heap_add(const walker& w);

template <typename Dummy>
struct walker_impl {
  dist_info di;
  point p;

  enum type {
    PLANE,
    QUARTER_UPPER_RIGHT,
    QUARTER_UPPER_LEFT,
    QUARTER_LOWER_LEFT,
    QUARTER_LOWER_RIGHT,
    LINE_RIGHT,
    LINE_UP,
    LINE_LEFT,
    LINE_DOWN
  } t;

  walker_impl(point source) : di(0, source), p(source), t(PLANE) { }

  walker_impl(point source, point p, type t)
    : di(dist(source, p), source), p(p), t(t) { }

  walker_impl(dist_info di, point p, type t) : di(di), p(p), t(t) { }

  void try_move_plane_goto(point destp, type destt)
  {
    if (dist_info_vec[destp].dist != 0) {
      dist_info_vec[destp] = dist_info(1, di.source);
      walk_heap_add(walker(di.source, destp, destt));
    }
  }

  template <typename Dummy2>
  void try_move_plane()
  {
    if (can_move<LEFT>(p))
      try_move_plane_goto(p.left(), QUARTER_UPPER_LEFT);
    if (can_move<RIGHT>(p))
      try_move_plane_goto(p.right(), QUARTER_LOWER_RIGHT);
    if (can_move<DOWN>(p))
      try_move_plane_goto(p.down(), QUARTER_LOWER_LEFT);
    if (can_move<UP>(p))
      try_move_plane_goto(p.up(), QUARTER_UPPER_RIGHT);
  }

  template <direction d, typename Dummy2>
  struct walker_movement {
    point p;
    dist_info di;
    walker_impl<Dummy2> w;
    dist_info& prev_di;

    walker_movement(point pos, point source, type t)
      : p(pos.template move<d>()), di(dist(source, p), source), w(di, p, t),
	prev_di(dist_info_vec[p]) { }

    bool try_move_and_reduce_dist()
    {
      if (di.dist < prev_di.dist) {
	prev_di = di;
	walk_heap_add(w);
	return true;
      } else
	return false;
    }

    template <direction e>
    bool try_forced_move()
    {
      if (good_direction<e>(di.source, prev_di.source)) {
	walk_heap_add(w);
	return true;
      } else
	return false;
    }
  };

  template <type lt, direction e0>
  void try_move_line()
  {
    if (can_move<e0>(p)) {
      walker_movement<e0,Dummy> wm(p, di.source, lt);
      if (!wm.try_move_and_reduce_dist())
	wm.template try_forced_move<e0>();
    }
  }

  template <type qt, type lt, direction e0, direction e1>
  void try_move_quarter()
  {
    if (!can_move<e1>(p))
      try_move_line<lt, e0>();
    else {
      walker_movement<e1,Dummy> wm1(p, di.source, qt);
      bool w1_created = true;
      if (!wm1.try_move_and_reduce_dist())
	if (!wm1.template try_forced_move<e1>())
	  w1_created = false;

      if (can_move<e0>(p)) {
	walker_movement<e0,Dummy> wm0(p, di.source, w1_created ? lt : qt);
	if (!wm0.try_move_and_reduce_dist())
	  if (!wm0.template try_forced_move<e0>())
	    if (!w1_created)
	      wm0.template try_forced_move<e1>();
      }
    }
  }

  bool operator<(const walker_impl<Dummy>& w)
  {
    return di.dist > w.di.dist;
  }  

  void try_move()
  {
    void (walker::*const try_move_call[])() = {
      &walker::try_move_plane<void>,
      &walker::try_move_quarter<QUARTER_UPPER_RIGHT, LINE_RIGHT, RIGHT, UP>,
      &walker::try_move_quarter<QUARTER_UPPER_LEFT, LINE_UP, UP, LEFT>,
      &walker::try_move_quarter<QUARTER_LOWER_LEFT, LINE_LEFT, LEFT, DOWN>,
      &walker::try_move_quarter<QUARTER_LOWER_RIGHT, LINE_DOWN, DOWN, RIGHT>,
      &walker::try_move_line<LINE_RIGHT, RIGHT>,
      &walker::try_move_line<LINE_UP, UP>,
      &walker::try_move_line<LINE_LEFT, LEFT>,
      &walker::try_move_line<LINE_DOWN, DOWN>
    };
    (this->*try_move_call[t])();
  }
};

void walk_heap_add(const walker& w)
{
  walk_heap.push_back(w);
  push_heap(walk_heap.begin(), walk_heap.end());
}

walker walk_heap_delmin()
{
  walker w = walk_heap.front();
  pop_heap(walk_heap.begin(), walk_heap.end());
  walk_heap.pop_back();
  return w;
}

point_map<int> compute_dists(point size, vector<point>& electrodes)
{
  dist_info_vec.init();
  
  for (uint i = 0; i < electrodes.size(); i++) {
    point p = electrodes[i];
    walk_heap_add(walker(p));
    dist_info_vec[p] = dist_info(0, p);
  }

  while (!walk_heap.empty())
    walk_heap_delmin().try_move();

  point p;
  point_map<int> ret;
  ret.init();
  for (p.y = 0; p.y < size.y; p.y++)
    for (p.x = 0; p.x < size.x; p.x++)
      ret[p] = dist_info_vec[p].dist;
  dist_info_vec.clear();

  return ret;
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
  width_heap_info_vec.init();
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
    if (can_move<LEFT>(p))
      width_relax(p.left(), w);
    if (can_move<RIGHT>(p))
      width_relax(p.right(), w);
    if (can_move<DOWN>(p))
      width_relax(p.down(), w);
    if (can_move<UP>(p))
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
