#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <stack>

#define FORC(it, C) for(__typeof((C).begin()) it = (C).begin(); it != (C).end(); ++it)

int main(void) {
  std::string dani_izraz;
  std::cin >> dani_izraz;
  int n = dani_izraz.size();
  std::vector< int > boja(n, -1);
  std::stack< int > trenutne;
  int broj_zagrada = 0;

  for (int i = 0; i < n; ++i) {
    if (dani_izraz[i] == '(') {
      boja[i] = broj_zagrada++;
      trenutne.push(boja[i]);
    }
    if (dani_izraz[i] == ')') {
      boja[i] = trenutne.top();
      trenutne.pop();
    }
  }

  std::set< std::string > rjesenja;

  for (int i = 1; i < (1<<broj_zagrada); ++i) {
    std::string trenutna;
    for (int j = 0; j < n; ++j) {
      if ((dani_izraz[j] != '(' && dani_izraz[j] != ')') || !(i & (1 << boja[j]))) {
        trenutna += dani_izraz[j];
      }
    }
    rjesenja.insert(trenutna);
  }

  for (auto &rjesenje: rjesenja) {
    std::cout << rjesenje << std::endl;
  }

  return 0;
}
