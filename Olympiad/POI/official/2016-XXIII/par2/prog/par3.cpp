/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Parada                                             *
 *   Autor programu:       Dominik Klemba                                     *
 *   Zlozonosc czasowa:    O(n)                                               *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include <algorithm>
#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <tuple>

// Types
typedef std::vector<std::vector<uint32_t>> graph_t;
typedef std::array<uint32_t, 3> answer_t;
typedef std::tuple<uint32_t, uint32_t> state;

enum : size_t {
  id = 0, position = 1
 };

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  // Input
  uint32_t n;
  std::cin >> n;
  if(n <= 4) {
    std::cout << n - 2 << '\n';
    return 0;
   }
  graph_t graph(n);
  for(uint32_t a, b, i = 1; i < n; ++i) {
    std::cin >> a >> b;
    graph[a-1].push_back(b-1);
    graph[b-1].push_back(a-1);
   }
  uint32_t answer = 2;
  std::stack<state> heap;
  std::vector<answer_t> results(n);
  std::vector<bool> visited(n, false);
  heap.emplace(0, 0);
  visited[0] = true;
  // Solve main problem
  while(heap.empty() == false) {
    size_t now = std::get<id>(heap.top()), now_pos = std::get<position>(heap.top());
    // heap ^
    std::get<position>(heap.top()) += 1;
    if(now_pos == graph[now].size()) {
      if(now == 0 && graph[now].size() == 1) {
        results[now][2] = results[graph[now][0]][2];
        heap.pop();
        continue;
       }
      if(graph[now].size() == 1) {
        heap.pop();
        continue;
       }
      for(const auto& x : graph[now]) {
        results[now][0] = results[x][2];
        std::sort(std::begin(results[now]), std::end(results[now]));
       }
      answer = std::max({answer,
       static_cast<uint32_t>(results[now][1] + results[now][2] + graph[now].size() - 2U),
       static_cast<uint32_t>(results[now][2] + graph[now].size() - 1U)});
      results[now][2] = std::max(static_cast<uint32_t>(results[now][2] + graph[now].size() - 2U),
       static_cast<uint32_t>(graph[now].size() - 1U));
      heap.pop();
      continue;
     }
    size_t next = graph[now][now_pos];
    // heap ^
    if(visited[next] == true) {
      continue;
     }
    visited[next] = true;
    heap.emplace(next, 0);
   }
  std::cout << std::max(answer, results[0][2]) << '\n';
 }
