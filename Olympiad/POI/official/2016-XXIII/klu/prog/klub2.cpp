/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Klubowicze                                         *
 *   Autor:                Marek Sommer                                       *
 *   Zlozonosc czasowa:    O(2^n)                                             *
 *   Zlozonosc pamieciowa: O(2^n)                                             *
 *   Opis:                 Rozwiazanie bledne - losuje wymiar po ktorym dzieli*
 *****************************************************************************/

#include <cassert>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

int RandomInt(int a, int b) {
  return rand() % (b - a + 1) + a;
}

int GetIthBit(int mask, int i) {
  return (mask >> i) & 1;
}

int RemoveIthBit(int mask, int i) {
  return (mask & ((1 << i) - 1)) ^ ((mask >> (i + 1)) << i);
}

int InsertIthBit(int mask, int i, int bit) {
  return (mask & ((1 << i) - 1)) ^ ((((mask >> i) << 1) ^ bit) << i);
}

int NegateIthBit(int mask, int i) {
  return mask ^ (1 << i);
}

std::vector<int> FindCycle(int n,
    const std::vector< std::pair<int, int> >& partners) {
  // Validates input.
  assert(n >= 1);
  assert((int) partners.size() == (1 << (n - 1)));
  std::vector<bool> already_used(1 << n, false);
  for (const std::pair<int, int>& par : partners) {
    assert(0 <= par.first and par.first < (1 << n));
    assert(0 <= par.second and par.second < (1 << n));
    assert(par.first != par.second);
    assert(!already_used[par.first]);
    assert(!already_used[par.second]);
    already_used[par.first] = true;
    already_used[par.second] = true;
  }

  // A problem that cannot be split.
  if (n == 1) {
    assert(partners[0] == std::make_pair(0, 1)
             or partners[0] == std::make_pair(1, 0));
    return {{0, 1}};
  }

  // Bit that will separate all vertices into to sets.
  const int separating_bit = RandomInt(0, n - 1);

  // Preprocessing.
  std::vector<int> partner(1 << n);
  for (const std::pair<int, int>& par : partners) {
    partner[par.first] = par.second;
    partner[par.second] = par.first;
  }

  // Making a smaller subproblem.
  std::vector< std::pair<int, int> > smaller_problem;
  std::vector<int> leftovers;
  for (const std::pair<int, int>& par : partners) {
    const int first_side = GetIthBit(par.first, separating_bit);
    const int second_side = GetIthBit(par.second, separating_bit);
    if (first_side == 0 and second_side == 0) {
      smaller_problem.emplace_back(par.first, par.second);
    } else if (first_side == 0) {
      leftovers.push_back(par.first);
    } else if (second_side == 0) {
      leftovers.push_back(par.second);
    }
  }
  // Pairing arbitrarily the leftovers.
  assert((int) leftovers.size() % 2 == 0);
  for (int i = 0; i < (int) leftovers.size(); i += 2) {
    smaller_problem.emplace_back(leftovers[i], leftovers[i + 1]);
  }

  // Renaming vertices in the smaller problem.
  for (std::pair<int, int>& par : smaller_problem) {
    assert(GetIthBit(par.first, separating_bit) == 0);
    assert(GetIthBit(par.second, separating_bit) == 0);
    par.first = RemoveIthBit(par.first, separating_bit);
    par.second = RemoveIthBit(par.second, separating_bit);
  }

  // Solving the subproblem.
  std::vector<int> subcycle = FindCycle(n - 1, smaller_problem);
  assert((int) subcycle.size() == (1 << (n - 1)));

  // Renaming back vertices in the subcycle.
  for (int& v : subcycle) {
    v = InsertIthBit(v, separating_bit, 0);
  }

  // Thin edges from left side to right side in final solution.
  std::vector<int> jump(1 << n, -1);

  // Finding connected components.
  std::vector<int> ids(1 << n, -1);
  std::function<void(int, int)> dfs
      = [&dfs, n, separating_bit, &ids, &partner, &jump](
            int w, int id) -> void {
          if (ids[w] != -1) {
            assert(ids[w] == id);
            return;
          }
          const int v = partner[w];
          const int v_counterpart = NegateIthBit(v, separating_bit);
          jump[v] = v_counterpart;
          jump[v_counterpart] = v;
          ids[w] = id;
          ids[v] = id;
          dfs(v_counterpart, id);
        };
  for (int i = 0; i < (1 << (n - 1)); i++) {
    const int id = InsertIthBit(i, separating_bit, 0);
    if (ids[id] == -1) {
      dfs(id, id);
    }
  }

  std::vector<bool> ids_taken(1 << n, false);
  ids_taken[ids[subcycle[0]]] = true;
  // Merging separate components.
  for (int i = 1; i < (int) subcycle.size(); i++) {
    const int u = subcycle[i - 1];
    const int v = subcycle[i];
    assert(ids_taken[ids[u]]);
    if (!ids_taken[ids[v]] and ids[u] != ids[v]) {
      ids_taken[ids[v]] = true;
      // u and v are in separate components.
      const int u_jump = jump[u];
      const int v_jump = jump[v];
      jump[u] = v;
      jump[v] = u;
      jump[u_jump] = v_jump;
      jump[v_jump] = u_jump;
    }
  }

  // Creating the resulting cycle.
  std::vector<int> cycle;
  int w = 0;  // Starts from 0.
  do {
    cycle.push_back(w);
    cycle.push_back(partner[w]);
    w = jump[partner[w]];
  } while (w != 0);

  assert((int) cycle.size() == (1 << n));

  return cycle;
}

int main() {
  int n;
  std::cin >> n;
  std::vector< std::pair<int, int> > edges;
  for (int i = 0; i < (1 << (n - 1)); i++) {
    int a, b;
    std::cin >> a >> b;
    edges.emplace_back(a, b);
  }
  std::vector<int> cycle = FindCycle(n, edges);
  for (int i = 0; i < (int) cycle.size(); i++) {
    if (i) {
      std::cout << " ";
    }
    std::cout << cycle[i];
  }
  std::cout << std::endl;
  return 0;
}
