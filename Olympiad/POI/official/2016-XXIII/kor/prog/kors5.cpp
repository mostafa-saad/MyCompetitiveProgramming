/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Korale                                             *
 *   Autor programu:       Karol Pokorski                                     *
 *   Zlozonosc czasowa:    O(n * log n + k log ^2 k)                          *
 *   Opis:                 Rozwiazanie prawie wzorcowe                        *
 *****************************************************************************/


#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 1000005;

typedef long long int LL;

struct Neclace {
  LL gemValueSum;
  int minGemUsed;
  int minGemUsedWithoutMaxOrderGem;
  int maxOrderGemUsed;
  Neclace* parentNeclace;
  set<int> gems;
  
  Neclace();
  Neclace(LL gemValueSum, int minGemUsed, int minGemUsedWithoutMaxOrderGem,
          int lastAddedGem, Neclace* parentNeclace, int parentRemovedGem);
  bool operator<(const Neclace& other);
  Neclace* productionA();
  Neclace* productionB();
};

struct CmpNeclaces {
  bool operator()(Neclace* a, Neclace* b) {
    return (*b) < (*a);
  }
};

int n, k;
int gemOrdering[MAXN];
int sortedGemPos[MAXN];
LL gemValue[MAXN];
Neclace producedNeclaces[2*MAXN];
int countProducedNeclaces = 0;
priority_queue<Neclace*, vector<Neclace*>, CmpNeclaces> M;

Neclace::Neclace() {}

Neclace::Neclace(LL gemValueSum, int minGemUsed,
                 int minGemUsedWithoutMaxOrderGem, int maxOrderGemUsed,
                 Neclace* parentNeclace, int parentRemovedGem) {
  this->gemValueSum = gemValueSum;
  this->minGemUsed = minGemUsed;
  this->minGemUsedWithoutMaxOrderGem = minGemUsedWithoutMaxOrderGem;
  this->maxOrderGemUsed = maxOrderGemUsed;
  this->parentNeclace = parentNeclace;
  if (parentNeclace != nullptr) {
    gems = parentNeclace->gems;
    if (parentRemovedGem != -1)
      gems.erase(parentRemovedGem);
  }
  gems.insert(maxOrderGemUsed);
}

bool Neclace::operator<(const Neclace& other) {
  if (gemValueSum != other.gemValueSum)
    return gemValueSum < other.gemValueSum;
  return gems < other.gems;
}

Neclace* Neclace::productionA() {
  int posMaxOrderGemUsed = sortedGemPos[maxOrderGemUsed];
  if (posMaxOrderGemUsed == n) return nullptr;
  int nextGem = gemOrdering[posMaxOrderGemUsed+1];
  Neclace produced(
      gemValueSum - gemValue[maxOrderGemUsed] + gemValue[nextGem],
      min(minGemUsedWithoutMaxOrderGem, nextGem),
      minGemUsedWithoutMaxOrderGem,
      nextGem,
      this,
      maxOrderGemUsed);
  producedNeclaces[countProducedNeclaces++] = produced;
  return &(producedNeclaces[countProducedNeclaces-1]);
}

Neclace* Neclace::productionB() {
  int posMaxOrderGemUsed = sortedGemPos[maxOrderGemUsed];
  if (posMaxOrderGemUsed == n) return nullptr;
  int nextGem = gemOrdering[posMaxOrderGemUsed+1];
  Neclace produced(
      gemValueSum + gemValue[nextGem],
      min(minGemUsed, nextGem),
      minGemUsed,
      nextGem,
      this,
      -1);
  producedNeclaces[countProducedNeclaces++] = produced;
  return &(producedNeclaces[countProducedNeclaces-1]);
}

int main() {
  scanf("%d%d", &n, &k);
  k -= 2;
  for (int i = 1; i <= n; i++) {
    scanf("%Ld", &gemValue[i]);
    gemOrdering[i] = i;
  }
  
  if (k < 0) {
    printf("0\n\n");
    return 0;
  }

  sort(gemOrdering+1, gemOrdering+n+1,
       [](int a, int b) {
         if (gemValue[a] != gemValue[b]) return gemValue[a] < gemValue[b];
         return a < b;
       });
  for (int i = 1; i <= n; i++)
    sortedGemPos[gemOrdering[i]] = i;

  producedNeclaces[countProducedNeclaces++] =
      Neclace(gemValue[gemOrdering[1]], gemOrdering[1], n+1, gemOrdering[1],
              nullptr, -1);
  M.push(&(producedNeclaces[countProducedNeclaces-1]));

  while (k > 0) {
    Neclace* currentNeclace = M.top();
    M.pop();
    Neclace* neclaceA = currentNeclace->productionA();
    Neclace* neclaceB = currentNeclace->productionB();

    if (neclaceA != nullptr) M.push(neclaceA);
    if (neclaceB != nullptr) M.push(neclaceB);
    
    k--;
  }

  Neclace* last = M.top();
  const set<int>& solution = last->gems;
  printf("%Ld\n", last->gemValueSum);

  for (set<int>::iterator it = solution.begin(); it != solution.end(); it++) {
    if (it != solution.begin()) printf(" ");
    printf("%d", *it);
  }
  printf("\n");
  
  return 0;
}
