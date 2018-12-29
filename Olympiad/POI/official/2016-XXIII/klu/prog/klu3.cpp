/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Klubowicze                                         *
 *   Autor:                Dominik Klemba                                     *
 *   Zlozonosc czasowa:    O(n * 2^n)                                         *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <array>
#include <tuple>

typedef uint32_t vector_t;

// Equivalence class of x. (x + N)
// Element of quotient space V/N.
// V = (Z_2)^n
// Vectors only from standard base.
class equivalence {
  vector_t x;
  uint32_t in_base; // Sum of N base
  uint32_t dim;
  public:
   static size_t dim_V;
   equivalence();
   vector_t nth_element(const uint32_t) const;
   size_t size() const;
   bool is_included(const vector_t) const;
   vector_t representant() const;
   void set(const vector_t, const bool);
 };

size_t equivalence::dim_V;
void dfs(uint32_t = 0);
void connect(const size_t, const size_t);

class node {
  public:
   uint32_t auxiliary_value, auxiliary_state;
   uint32_t soft_link, hard_link;
   node() : auxiliary_state(0){
    }
 } *graph;

void solve(equivalence);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  uint32_t n;
  std::cin >> n;
  equivalence::dim_V = n;
  uint32_t number_of_nodes= 1U << n;

  graph = new node[number_of_nodes];
  for(size_t a,b, i = 0; i < number_of_nodes; i += 2) {
    std::cin >> a >> b;
    graph[a].hard_link = b;
    graph[b].hard_link = a;
   }

  solve(equivalence());

  dfs();
  std::vector<uint32_t> output(number_of_nodes);
  for(size_t i = 0; i < number_of_nodes; ++i) {
    output[graph[i].auxiliary_value] = i;
   }
  std::copy(std::begin(output), std::end(output),
   std::ostream_iterator<uint32_t>(std::cout, " "));
  std::cout << '\n';
 }

equivalence::equivalence(): x(0), in_base(0), dim(dim_V) {
  for(size_t i = 0; i < dim_V; ++i) {
    in_base |= 1U << i;
   }
 }

vector_t equivalence::nth_element(const uint32_t n) const {
  vector_t result = x;
  for(uint32_t i = 1, j = 1; j <= n; i <<= 1) {
    if((i & in_base) == 0) {
      continue;
     }
    if((n & j) != 0) {
      result |= i;
     }
    j <<= 1;
   }

  return result;
 }

inline size_t equivalence::size() const {
  return 1 << dim;
 }

inline bool equivalence::is_included(const vector_t v) const {
  return ((~in_base) & v) == x;
 }

inline vector_t equivalence::representant() const {
  return x;
 }

void equivalence::set(const vector_t v, const bool type) {
  if(type == true) {
    x |= v;
   }
  in_base ^= v;
  dim -= 1;
 }

inline void connect(const size_t a, const size_t b) {
  graph[a].hard_link = b;
  graph[b].hard_link = a;
 }

void bruteforce(const equivalence& state) { // state.size() == 4
  std::array<vector_t, 4> t;
  for(uint32_t i = 0; i < state.size(); ++i) {
    t[i] = state.nth_element(i);
   }

  if(t[1] == graph[t[0]].hard_link) {
    std::swap(t[1], t[2]);
   }

  graph[t[0]].soft_link = t[1];
  graph[t[1]].soft_link = t[0];
  graph[t[2]].soft_link = t[3];
  graph[t[3]].soft_link = t[2];
 }

inline uint32_t difference(const uint32_t a, const uint32_t b) {
  for(uint32_t i = 1; true; i <<= 1) {
    if((a&i) != (b&i)) {
      return i;
     }
   }
 }

void dfs(uint32_t ptr) {
   static uint32_t global_state = 0;
   global_state += 1;

   uint32_t in_cycle = 0;
   while(graph[ptr].auxiliary_state < global_state) {
    graph[ptr].auxiliary_state = global_state;
    graph[ptr].auxiliary_value = in_cycle++;
    if(graph[graph[ptr].hard_link].auxiliary_state < global_state) {
      ptr = graph[ptr].hard_link;
     }
    else {
      ptr = graph[ptr].soft_link;
     }
   }
 }

void solve(equivalence state) {
  if(state.size() == 4) {
   bruteforce(state);
   return;
  }

  uint32_t diff = difference(state.representant(),
   graph[state.representant()].hard_link);
  equivalence new_state(state);
  new_state.set(diff, true);

  typedef std::tuple<uint32_t, uint32_t> data_t;
  std::vector<data_t> cache;
  for(uint32_t temp, i = 0; i < new_state.size(); ++i) {
    temp = new_state.nth_element(i);
    if((temp & diff) != (graph[temp].hard_link & diff)) {
      cache.emplace_back(temp, graph[temp].hard_link);
     }
   }
  for(size_t i = 0; i < cache.size(); i += 2) {
    connect(std::get<0>(cache[i]), std::get<0>(cache[i+1]));
   }
  solve(new_state);

  dfs(std::get<0>(cache.front()));
  std::sort(std::begin(cache), std::end(cache), [](data_t a, data_t b){
   return graph[std::get<0>(a)].auxiliary_value < graph[std::get<0>(b)].auxiliary_value;});

  connect(std::get<1>(cache.front()), std::get<1>(cache.back()));
  for(size_t i = 1; i + 1 < cache.size(); i += 2) {
   connect(std::get<1>(cache[i]), std::get<1>(cache[i+1]));
  }

  equivalence new_state2(state);
  new_state2.set(diff, false);
  solve(new_state2);

  // Restore correct data
  for(const auto& x : cache) {
    graph[std::get<0>(x)].hard_link = std::get<1>(x);
    graph[std::get<1>(x)].hard_link = std::get<0>(x);
   }
 }

