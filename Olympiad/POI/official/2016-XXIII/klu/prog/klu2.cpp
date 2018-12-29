/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Klubowicze                                         *
 *   Autor:                Marek Sommer                                       *
 *   Zlozonosc czasowa:    O(n * 2^n)                                         *
 *   Zlozonosc pamieciowa: O(2^n)                                             *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/


#include <cassert>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

int GetIthBit(int mask, int i) {
  return (mask >> i) & 1;
}

int RemoveIthBit(int mask, int i) {
  return (mask & ((1 << i) - 1)) ^ ((mask >> (i + 1)) << i);
}

int InsertIthBit(int mask, int i, int bit) {
  return (mask & ((1 << i) - 1)) ^ ((((mask >> i) << 1) ^ bit) << i);
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
    return {0, 1};
  }

  // Preprocessing.
  std::vector<int> partner(1 << n);
  for (const std::pair<int, int>& par : partners) {
    partner[par.first] = par.second;
    partner[par.second] = par.first;
  }

  // Finding a bit which separates at least one pair of partners.
  const int separator_bit
      = __builtin_ctz(partners[0].first ^ partners[0].second);

  // Making smaller subproblems.
  // Left problem:  the set with 0 on separator bit.
  // Right problem: the set with 1 on separator bit.
  std::vector< std::pair<int, int> > smaller_problem[2];
  std::vector<int> leftovers;  // "left" leftovers :P
  std::vector<bool> is_in_leftovers(1 << n, false);
  for (const std::pair<int, int>& par : partners) {
    const int first_side = GetIthBit(par.first, separator_bit);
    const int second_side = GetIthBit(par.second, separator_bit);
    if (first_side == second_side) {
      smaller_problem[first_side].emplace_back(par.first, par.second);
    } else if (first_side == 0) {
      is_in_leftovers[par.first] = true;
      leftovers.push_back(par.first);
    } else if (second_side == 0) {
      is_in_leftovers[par.second] = true;
      leftovers.push_back(par.second);
    }
  }
  // Pairing arbitrarily the leftovers in the left problem.
  assert(smaller_problem[0].size() == smaller_problem[1].size());
  assert((int) leftovers.size() % 2 == 0);
  for (int i = 0; i < (int) leftovers.size(); i += 2) {
    smaller_problem[0].emplace_back(leftovers[i], leftovers[i + 1]);
  }

  // Solves the given subproblem recursively. Saves the resulting cycle
  // in the 'subcycle' array.
  std::vector<int> subcycle[2];
  auto SolveSubproblem = [n, separator_bit, &smaller_problem, &subcycle](
      int subproblem_id) -> void {
    // Renaming vertices in the subproblem so that they have indices
    // from 0 to 2^(n - 1) - 1 (in other words, removing the separator bit).
    for (std::pair<int, int>& par : smaller_problem[subproblem_id]) {
      assert(GetIthBit(par.first, separator_bit) == subproblem_id);
      assert(GetIthBit(par.second, separator_bit) == subproblem_id);
      par.first = RemoveIthBit(par.first, separator_bit);
      par.second = RemoveIthBit(par.second, separator_bit);
    }
    subcycle[subproblem_id] = FindCycle(n - 1, smaller_problem[subproblem_id]);
    // Renaming back the vertices on the subcycle.
    for (int& v : subcycle[subproblem_id]) {
      v = InsertIthBit(v, separator_bit, subproblem_id);
    }
  };

  // Solving the left subproblem.
  SolveSubproblem(0);

  // List of leftovers in an order from subcycle[0].
  std::vector<int> leftovers_on_subcycle0;
  for (int v : subcycle[0]) {
    if (is_in_leftovers[v]) {
      leftovers_on_subcycle0.push_back(v);
    }
  }
  assert(leftovers.size() == leftovers_on_subcycle0.size());

  // Pairing the "rightovers" in the right problem.
  for (int i = 1; i < (int) leftovers_on_subcycle0.size(); i += 2) {
    const int next_i = (i + 1) % leftovers_on_subcycle0.size();
    smaller_problem[1].emplace_back(partner[leftovers_on_subcycle0[i]],
                                    partner[leftovers_on_subcycle0[next_i]]);
  }

  // Solving the right subproblem.
  SolveSubproblem(1);

  // Edges between the partner-edges on both subcycles.
  std::vector<int> jump(1 << n, -1);
  for (int i = 0; i < 2; i++) {
    for (int j = 1; j < (int) subcycle[i].size(); j += 2) {
      const int next_j = (j + 1) % subcycle[i].size();
      jump[subcycle[i][j]] = subcycle[i][next_j];
      jump[subcycle[i][next_j]] = subcycle[i][j];
    }
  }

  // Creating the resulting cycle. The cycle alternates between the 'jump'
  // edges and the 'partner' edges.
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
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
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
