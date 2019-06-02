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

class wierzcholek {
  bool odwiedzony;
  public:
   static uint32_t odpowiedz;
   std::vector<wierzcholek*> sasiedzi;
 
   wierzcholek() : odwiedzony(false) {
    } // Brakuje mi in class inicjalizacji
  uint32_t solve();
 };

uint32_t wierzcholek::odpowiedz = 0;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  // Pobieranie danych
  uint32_t n;
  std::cin >> n;
  if(n <= 3) {
    std::cout << n - 2 << '\n';
    return 0;
   }
  wierzcholek* const graf = new wierzcholek[n];
  for(uint32_t a, b, i = 0; i < n - 1; ++i) {
    std::cin >> a >> b;
    graf[a-1].sasiedzi.push_back(&graf[b-1]);
    graf[b-1].sasiedzi.push_back(&graf[a-1]);
   }
  // Rozwiazywanie
  const uint32_t odpowiedz = graf[0].solve();
  std::cout << std::max(odpowiedz, wierzcholek::odpowiedz) << '\n';
 }

uint32_t wierzcholek::solve() {
  // Lisc
  if(sasiedzi.size() == 1 && sasiedzi.back()->odwiedzony == true) {
    return 0;
   }
  if(sasiedzi.size() == 1) {
    return sasiedzi.front()->solve();
   }
  // Inaczej
  std::array<uint32_t, 3> wynik{{0, 0, 0}};
  odwiedzony = true;
  for(const auto& ptr : sasiedzi) {
    if(ptr->odwiedzony == false) {
      wynik.front() = ptr->solve();
      std::sort(std::begin(wynik), std::end(wynik));
     }
   }
  odpowiedz = std::max({odpowiedz, static_cast<uint32_t>(wynik[1] + wynik[2] + sasiedzi.size() - 2U),
     static_cast<uint32_t>(wynik[2] + sasiedzi.size() - 1U)});
  odwiedzony = false;
  return std::max(wynik[2] + sasiedzi.size() - 2, sasiedzi.size() - 1);
 }
