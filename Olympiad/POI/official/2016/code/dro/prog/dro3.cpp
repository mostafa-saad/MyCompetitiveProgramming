/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Drogi zmiennokierunkowe                            *
 *   Autor programu:       Marek Sommer                                       *
 *   Zlozonosc czasowa:    O(n + m)                                           *
 *   Zlozonosc pamieciowa: O(n + m)                                           *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/


#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

constexpr int MaxN = 500 * 1000;
constexpr int MaxM = 1000 * 1000;

// Graph
namespace G {

  int n;  // Number of vertices.
  int m;  // Number of edges.
  std::vector< std::pair<int, int> > edges;
  std::vector<int> graph[MaxN + 5];
  std::vector<int> graph_t[MaxN + 5];  // Transpose graph.

  void ReadGraph() {
    std::cin >> n >> m;
    assert(1 <= n and n <= MaxN);
    assert(0 <= m and m <= MaxM);
    for (int i = 1; i <= m; i++) {
      int a, b;
      std::cin >> a >> b;
      assert(1 <= a and a <= n);
      assert(1 <= b and b <= n);
      edges.push_back({a, b});
      graph[a].push_back(b);
      graph_t[b].push_back(a);
    }
  }

}  // namespace G

// Strongly connected components.
namespace SCC {

  int number_of_components;
  int component_of[MaxN + 5];
  std::vector<int> vertices_in_component[MaxN + 5];

  bool visited[MaxN + 5];
  int post_order_counter;
  int post_order[MaxN + 5];  // Assigns a vertex to its post order index.

  void DfsPostOrder(int w) {
    assert(1 <= w and w <= G::n);
    if (!visited[w]) {
      visited[w] = true;
      for (const int i : G::graph[w]) {
        DfsPostOrder(i);
      }
      post_order[++post_order_counter] = w;
    }
  }

  void DfsOnTransposeGraph(int w, int component_id) {
    if (component_of[w] == 0) {
      component_of[w] = component_id;
      vertices_in_component[component_id].push_back(w);
      for (const int i : G::graph_t[w]) {
        DfsOnTransposeGraph(i, component_id);
      }
    }
  }

  void StronglyConnectedComponents() {
    // Cleaning.
    post_order_counter = 0;
    number_of_components = 0;
    for (int i = 1; i <= G::n; i++) {
      visited[i] = false;
      component_of[i] = 0;
    }
    // Computing post orders.
    for (int i = 1; i <= G::n; i++) {
      DfsPostOrder(i);
    }
    // Iterating in reverse-post-order order.
    for (int i = G::n; i >= 1; i--) {
      const int w = post_order[i];
      if (component_of[w] == 0) {
        number_of_components++;
        vertices_in_component[number_of_components].clear();
        DfsOnTransposeGraph(w, number_of_components);
      }
    }
  }

}  // namespace SCC


// Buckets
namespace B {

  int bucket[MaxN + 5];

  std::vector<int> MakeResult(int n) {
    std::vector<int> result;
    for (int i = 1; i <= n; i++) {
      if (bucket[i] != 0) {
        result.push_back(i);
      }
    }
    return result;
  }

  std::vector<int> BucketSort(std::vector<int> v, int n) {
    for (int i = 1; i <= n; i++) {
      bucket[i] = 0;
    }
    for (int i : v) {
      assert(1 <= i and i <= n);
      bucket[i] = 1;
    }
    return MakeResult(n);
  }

  std::vector<int> Complement(std::vector<int> v, int n) {
    for (int i = 1; i <= n; i++) {
      bucket[i] = 1;
    }
    for (int i : v) {
      bucket[i] = 0;
    }
    return MakeResult(n);
  }

  std::vector<int> Intersection(std::vector<int> a, std::vector<int> b, int n) {
    std::vector<int> complement_a = Complement(a, n);
    std::vector<int> complement_b = Complement(b, n);
    for (int i = 1; i <= n; i++) {
      bucket[i] = 1;
    }
    for (int i : complement_a) {
      bucket[i] = 0;
    }
    for (int i : complement_b) {
      bucket[i] = 0;
    }
    return MakeResult(n);
  }

  std::vector<int> SumOfRanges(
      std::vector< std::pair<int, int> > ranges, int n) {
    for (int i = 1; i <= n; i++) {
      bucket[i] = 0;
    }
    for (std::pair<int, int> range : ranges) {
      assert(1 <= range.first and range.first <= range.second
             and range.second <= n);
      bucket[range.first]++;
      if (range.second < n) {
        bucket[range.second + 1]--;
      }
    }
    std::vector<int> result;
    int counter = 0;
    for (int i = 1; i <= n; i++) {
      counter += bucket[i];
      assert(counter >= 0);
      if (counter > 0) {
        result.push_back(i);
      }
    }
    return result;
  }

  bool set_element[MaxN + 5];
  int set_size;

  void InitializeSet(int n) {
    for (int i = 1; i <= n; i++) {
      set_element[i] = false;
    }
    set_size = 0;
  }

  void SetElement(int x, bool val) {
    assert(1 <= x);
    if (set_element[x] != val) {
      set_element[x] = val;
      if (val) {
        set_size++;
      } else {
        set_size--;
      }
    }
  }

  int SetSize() {
    return set_size;
  }

}  // namespace B

// Good Vertices
namespace GV {
  int n;  // Size of the DAG.
  std::vector<int> graph[MaxN + 5];  // Edges in DAG.
  std::vector<int> graph_t[MaxN + 5];  // Transposed edges in DAG.
  int topological_order[MaxN + 5];  // Vertices in topological order (->).
  int topological_order_t[MaxN + 5];  // Position of vertex in the order above.
  int degree[MaxN + 5];

  void TopologicalSort() {
    std::queue<int> q;
    for (int i = 1; i <= n; i++) {
      degree[i] = static_cast<int>(graph_t[i].size());
      if (degree[i] == 0) {
        q.push(i);
      }
    }
    for (int i = 1; i <= n; i++) {
      assert(!q.empty());
      int w = q.front();
      q.pop();
      topological_order[i] = w;
      topological_order_t[w] = i;
      for (int j : graph[w]) {
        degree[j]--;
        if (degree[j] == 0) {
          q.push(j);
        }
      }
    }
    assert(q.empty());  // Otherwise, the graph is not a DAG.
  }

  std::vector<int> OneWayGoodVertices() {
    std::vector<int> good;
    B::InitializeSet(n);
    for (int i = n; i >= 1; i--) {
      const int w = topological_order[i];
      B::SetElement(w, true);
      for (int j : graph[w]) {
        B::SetElement(j, false);
      }
      if (B::SetSize() == 1) {
        good.push_back(w);
      }
    }
    return good;
  }

  void MakeGraph(const std::vector< std::pair<int, int> > edges) {
    for (int i = 1; i <= n; i++) {
      graph[i].clear();
      graph_t[i].clear();
    }
    for (std::pair<int, int> edge : edges) {
      const int a = SCC::component_of[edge.first];
      const int b = SCC::component_of[edge.second];
      if (a != b) {
        graph[a].push_back(b);
        graph_t[b].push_back(a);
      }
    }
  }

  std::vector<int> FindGoodVertices() {
    // Creates a DAG on components.
    n = SCC::number_of_components;
    MakeGraph(G::edges);
    TopologicalSort();

    std::vector<int> good_vertices = OneWayGoodVertices();

    std::reverse(topological_order + 1, topological_order + n + 1);
    for (int i = 1; i <= n; i++) {
      topological_order_t[i] = n - topological_order_t[i] + 1;
    }
    for (int i = 1; i <= n; i++) {
      std::swap(graph[i], graph_t[i]);
    }
    std::vector<int> good_vertices_t = OneWayGoodVertices();

    return B::Intersection(good_vertices, good_vertices_t, n);
  }

}  // namespace GV

std::vector<int> Algorithm() {
  SCC::StronglyConnectedComponents();
  std::vector<int> good_vertices = GV::FindGoodVertices();
  // Constructs the answer - all the vertices that are in a 'good' component.
  std::vector<int> answer;
  for (int i : good_vertices) {
    assert(1 <= i and i <= SCC::number_of_components);
    for (int j : SCC::vertices_in_component[i]) {
      answer.push_back(j);
    }
  }
  return B::BucketSort(answer, G::n);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  G::ReadGraph();

  std::vector<int> result = Algorithm();

  // Printing the result.
  std::cout << result.size() << "\n";
  for (int i = 0; i < static_cast<int>(result.size()); i++) {
    if (i != 0) {
      std::cout << " ";
    }
    std::cout << result[i];
  }
  std::cout << "\n";
  return EXIT_SUCCESS;
}
