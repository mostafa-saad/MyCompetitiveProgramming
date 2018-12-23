/* Alternative solution for the Treasure hunt task 
 * Author: Marek Cygan
 * Date: 01.07.2011
 * Time complexity: O(#calls * log(#calls)).
 * Space complexity: O(#calls * log(#calls)).
 * Description: adjust the standard lca algorithm with links for powers of two
 *              to run on the compressed tree where each node corresponds
 *              to an added path.
 */

#include <cstdio>
#include <algorithm>

using namespace std;

const int LOG = 20;
const int MAX_CALLS = 400000;
const int MAX_VERTICES = 1000 * 1000 * 1000;
const int MAX_PATHS = MAX_CALLS+10;

int jump[MAX_PATHS][LOG]; //jump[x][i] is a path 2^i higher than path x
int vertex_number[MAX_PATHS]; //for each path we store its upmost vertex 
int last_vertex[MAX_PATHS]; //last vertex on each path
int depth[MAX_PATHS]; //depth of each path in the path tree
int real_depth[MAX_PATHS]; //depth of the highest vertex on a path
                           //in the uncompressed tree
int where_attached[MAX_PATHS]; //for each path store the vertex it is attached to
int vertices, paths;

void init() {
  vertices = 1;
  paths = 1;
}

/* For a given vertex we find its path number. */
inline int path_number(int x) {
  return lower_bound(last_vertex, last_vertex+paths, x) - last_vertex;
}

/* For a vertex x on path p return its depth in the uncompressed tree. */
inline int get_real_depth(int x, int p) {
  return real_depth[p] + (x-vertex_number[p]);
}


void path(int a, int s) {
  int p = path_number(--a); //parent path
  vertex_number[paths] = vertices;
  last_vertex[paths] = vertices+(s-1);
  jump[paths][0] = p; 
  where_attached[paths] = a;
  depth[paths] = depth[p] + 1;
  real_depth[paths] = get_real_depth(a, p) + 1;
  for (int i = 1; i < LOG; ++i) jump[paths][i] = jump[jump[paths][i-1]][i-1];
  vertices += s;
  paths++;
}

/*For a vertex x on path p return its ancestor h levels up in the uncom. tree.*/
int climb(int x, int p, int h) {
  int v = vertex_number[p];
  if (x - v >= h) return x-h;
  h -= (x - v);
  for (int i = LOG-1; i >= 0; --i){
    int cand = jump[p][i];
    if (real_depth[p] - real_depth[cand] <= h){
      h -= real_depth[p] - real_depth[cand];
      p = cand;
    }
  }
  if (h == 0) return vertex_number[p];
  h--; x = where_attached[p];
  p = jump[p][0];
  v = vertex_number[p];
  return x-h;
}

/* Go h levels up in the compressed tree. */
int climb_compressed(int p, int h){
  int i = 0;
  while (h > 0){
    if (h & 1) p = jump[p][i];
    h >>= 1;
    i++;
  }
  return p;
}

/*For two vertices a,b on paths pa,pb compute its lca in the uncom. tree.*/
int lca(int a, int pa, int b,int pb) {
  if (pa == pb) return min(a, b);
  int da = get_real_depth(a, pa);
  int db = get_real_depth(b, pb);
  if (da < db) return lca(b, pb, a, pa);
  
  //go to the same real depth
  a = climb(a, pa, da-db);
  pa = path_number(a);
  if (a == b) return a;

  //go to highest vertex on the lower-attached path
  if (real_depth[pa] < real_depth[pb]) {
    swap(a, b); swap(pa, pb); 
  }
  int d = a - vertex_number[pa];
  a = vertex_number[pa]; //we are done with A, now B
  b -= d;

  b = climb(b, pb, 1);
  if (b == where_attached[pa]) return b;
  b = vertex_number[pb]; //we are done with B

  //now we operate on the compressed tree
  if (depth[pa] < depth[pb]) {
    swap(pa, pb);
  }
  int oldpa = pa;
  pa = climb_compressed(pa, depth[pa] - depth[pb]);
  if (pa == pb){
    pa = climb_compressed(oldpa, depth[oldpa] - depth[pb] - 1);
    return where_attached[pa];
  }
  for (int i = LOG-1; i >= 0; --i) {
    if (jump[pa][i] != jump[pb][i]) {
      pa = jump[pa][i];
      pb = jump[pb][i];
    }
  }

  return min(where_attached[pa], where_attached[pb]);
}

int dig(int a, int b) {
  a--; b--;
  int pa = path_number(a), pb = path_number(b);
  int x = lca(a,pa,b,pb);
  int da = get_real_depth(a, pa);
  int db = get_real_depth(b, pb);
  int dx = get_real_depth(x, path_number(x));

  int dist = ((da-dx) + (db - dx));
  int pos = dist/2;
  return ((da-dx >= pos) ? climb(a, pa, pos) : climb(b, pb, dist - pos)) + 1;
}
