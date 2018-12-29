/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Squarki                                          *
 *   Autor:             Karol Pokorski                                   *
 *   Zlozonosc czasowa: O(n^3) - oczekiwana                              *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

typedef long long int LL;

const int MAXN = 305;
const int MAXK = (MAXN*(MAXN-1))/2;
const int MAXHASH = 1000003;

int t[MAXK], seq[MAXN], x[3], p[MAXN], result[MAXN][MAXN], numSol = 0;
vector<int> hashTable[MAXHASH];
queue<int> toClear;

int HashFunc(int value) {
  return (int)(((LL)value*value+7)%MAXHASH);
}

int CheckExist(int value) {
  int hashKey = HashFunc(value);

  for (int i = 0; i < (int)hashTable[hashKey].size(); i++)
    if (value == hashTable[hashKey][i])
      return i;
  return -1;
}

void Insert(int value) {
  hashTable[HashFunc(value)].push_back(value);
  toClear.push(HashFunc(value));
}

void Erase(int value) {
  hashTable[HashFunc(value)].erase(find(hashTable[HashFunc(value)].begin(), hashTable[HashFunc(value)].end(), value));
}

void ClearHashTable() {
  while (!toClear.empty()) {
    hashTable[toClear.front()].clear();
    toClear.pop();
  }
}

int main() {
  int n, N, ret;

  ret = scanf("%d", &n);

  N = (n*(n-1))/2;

  for (int i = 0; i < N; i++)
    ret = scanf("%d", &t[i]);

  if (ret < 0)
    return 0;

  sort(t, t+N);

  for (int i = 2; i < n; i++) {
    int numFound = 3;
    bool corr = true;

    p[0] = t[0]+t[1]-t[i];
    
    if ((p[0] < 0) || (p[0] % 2 == 1))
      continue;
    if ((i > 2) && (t[i] == t[i-1]))
      continue;

    p[0] /= 2;
      
    p[1] = t[0]-p[0];
    p[2] = t[1]-p[0];

    ClearHashTable();
    
    Insert(p[0]+p[1]);
    Insert(p[0]+p[2]);
    Insert(p[1]+p[2]);
      
    for (int j = 0; j < N; j++) {
      if (CheckExist(t[j]) != -1)
        Erase(t[j]);
      else {
        if (numFound >= n) {
          j = N;
          corr = false;
        }
        else {
          p[numFound] = t[j]-p[0];
          for (int l = 1; l < numFound; l++)
            Insert(p[l]+p[numFound]);
          numFound++;
        }
      }
    }
    
    if ((numFound == n) && (corr)) {
      for (int j = 1; j < n; j++)
        if (p[j] == p[j-1])
          corr = false;
      
      if (corr) {
        for (int j = 0; j < n; j++)
          result[numSol][j] = p[j];
        numSol++;
      }
    }
  }
  
  printf("%d\n", numSol);
  
  for (int i = 0; i < numSol; i++) {
    for (int j = 0; j < n; j++)
      printf("%d ", result[i][j]);
    printf("\n");
  }

  return 0;
}
