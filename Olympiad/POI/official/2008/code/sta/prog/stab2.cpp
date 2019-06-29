/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Stacja (STA)                                              *
 *   Plik:     stab2.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie bledne, po prostu strzelamy sobie jakis lisc. *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
using namespace std;

#define MAX_N 1000000

int n;
int deg[MAX_N + 1];
vector<int> liscie;

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    scanf("%d%d", &a, &b);
    deg[a]++;
    deg[b]++;
  }
  
  for (int i = 1; i <= n; i++)
    if (deg[i] == 1)
      liscie.push_back(i);
  srand(12345);
  /* Po prostu losowy lisc. */
  printf("%d\n", liscie[rand() % (int)liscie.size()]);
  return 0;
}
