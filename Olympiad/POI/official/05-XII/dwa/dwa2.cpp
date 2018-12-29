/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: DWA (Dwa przyjêcia)                            *
 *   Plik:                dwa2.pas                                       *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Rozwiazanie alternatywne                       *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<vector>

using namespace std;

bool tab[210][210];
bool inFirst[210];
bool isEven[210];
int n;
bool used[210];

void divide()
{
  int chosen = -1;
  for (int i = 0; i < n; i++) {
    if ((!used[i]) && (!isEven[i])) {
      chosen = i;
      break;
    }
  }
  if (chosen == -1) {
    for (int i = 0; i < n; i++) {
      if (!used[i]) {
        inFirst[i] = true;
        used[i] = true;
      }
    }
    return;
  }
  // Get all neighbours
  vector < int >heap;
  for (int i = 0; i < n; i++) {
    if (tab[chosen][i]) {
      heap.push_back(i);
    }
  }

  for (unsigned int i = 0; i < heap.size(); i++) {
    for (unsigned int j = i + 1; j < heap.size(); j++) {
      tab[heap[i]][heap[j]] = !tab[heap[i]][heap[j]];
      tab[heap[j]][heap[i]] = !tab[heap[j]][heap[i]];
      isEven[heap[i]] = !isEven[heap[i]];
      isEven[heap[j]] = !isEven[heap[j]];
    }
  }

  for (unsigned int i = 0; i < heap.size(); i++) {
    tab[chosen][heap[i]] = false;
    tab[heap[i]][chosen] = false;
    isEven[chosen] = !isEven[chosen];
    isEven[heap[i]] = !isEven[heap[i]];
  }
  used[chosen] = true;

  divide();
  bool even = true;
  for (unsigned int i = 0; i < heap.size(); i++)
    if (inFirst[heap[i]])
      even = !even;

  if (even) {
    inFirst[chosen] = true;
  }

  for (unsigned int i = 0; i < heap.size(); i++) {
    for (unsigned int j = i + 1; j < heap.size(); j++) {
      tab[heap[i]][heap[j]] = !tab[heap[i]][heap[j]];
      tab[heap[j]][heap[i]] = !tab[heap[j]][heap[i]];
      isEven[heap[i]] = !isEven[heap[i]];
      isEven[heap[j]] = !isEven[heap[j]];
    }
  }
  for (unsigned int i = 0; i < heap.size(); i++) {
    tab[chosen][heap[i]] = true;
    tab[heap[i]][chosen] = true;
    isEven[chosen] = !isEven[chosen];
    isEven[heap[i]] = !isEven[heap[i]];
  }
  return;
}

int main()
{
  cin >> n;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      tab[i][j] = false;
  for (int i = 0; i < n; i++)
    isEven[i] = true;
  for (int i = 0; i < n; i++)
    used[i] = false;

  int ile;
  int a;
  for (int i = 0; i < n; i++) {
    cin >> ile;
    for (int j = 0; j < ile; j++) {
      cin >> a;
      a--;
      tab[i][a] = true;
      isEven[i] = !isEven[i];
    }
  }
  for (int i = 0; i < n; i++)
    inFirst[i] = false;

  divide();

  // Output
  int result = 0;
  for (int i = 0; i < n; i++)
    if (inFirst[i])
      result++;
  cout << result << endl;
  for (int i = 0; i < n; i++)
    if (inFirst[i])
      cout << i + 1 << " ";
  cout << endl;

  return 0;
}
