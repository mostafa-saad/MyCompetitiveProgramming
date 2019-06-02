/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Drogi zmiennokierunkowe                            *
 *   Autor programu:       Marek Sommer                                       *
 *   Zlozonosc czasowa:    O(n + m)                                           *
 *   Zlozonosc pamieciowa: O(n + m)                                           *
 *   Opis:                 Rozwiazanie czesciowe                              *
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

  void TransposeGraph() {
    for (std::pair<int, int>& edge : edges) {
      std::swap(edge.first, edge.second);
    }
    for (int i = 1; i <= n; i++) {
      std::swap(graph[i], graph_t[i]);
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

  std::vector<int> Sum(std::vector<int> a, std::vector<int> b, int n) {
    for (int i = 1; i <= n; i++) {
      bucket[i] = 0;
    }
    for (int i : a) {
      bucket[i] = 1;
    }
    for (int i : b) {
      bucket[i] = 1;
    }
    return MakeResult(n);
  }

}  // namespace B

// Good Vertices
namespace GV {
  int n;  // Size of the DAG.
  std::vector<int> graph[MaxN + 5];  // Edges in DAG.
  int degree[MaxN + 5];
  bool visited[MaxN + 5];

  void MakeGraph(const std::vector< std::pair<int, int> > edges) {
    for (int i = 1; i <= n; i++) {
      graph[i].clear();
    }
    for (std::pair<int, int> edge : edges) {
      const int a = SCC::component_of[edge.first];
      const int b = SCC::component_of[edge.second];
      if (a != b) {
        graph[a].push_back(b);
      }
    }
  }

  // Find any vertex that has in-degree equal to 0.
  int FindFirstVertex() {
    for (int i = 1; i <= n; i++) {
      degree[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
      for (int j : graph[i]) {
        degree[j]++;
      }
    }
    for (int i = 1; i <= n; i++) {
      if (degree[i] == 0) {
        return i;
      }
    }
    assert(false);
  }

  void Dfs(int w) {
    if (!visited[w]) {
      visited[w] = true;
      for (int i : graph[w]) {
        Dfs(i);
      }
    }
  }

  bool IsGood(int w) {
    for (int i = 1; i <= n; i++) {
      visited[i] = false;
    }
    Dfs(w);
    for (int i = 1; i <= n; i++) {
      if (!visited[i]) {
        return false;
      }
    }
    return true;
  }

  std::vector<int> FindGoodVertices() {
    // Creates a DAG on components.
    n = SCC::number_of_components;
    MakeGraph(G::edges);

    const int w = FindFirstVertex();
    if (IsGood(w)) {
      return {w};
    }
    return {};
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
  std::vector<int> result1 = Algorithm();
  G::TransposeGraph();
  std::vector<int> result2 = Algorithm();

  std::vector<int> result = B::Sum(result1, result2, G::n);

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
