#include <cstdio>
using namespace std;

const int MAXN = 60;

int n, imam[MAXN], karta;
int suma, x;

int main() {
  scanf("%d",&n);
  
  for (int i = 2; i <= 11; i++) imam[i] = 4;
  imam[10] = 4 * 4;

  for (int i = 0; i < n; i++) {
    scanf("%d",&karta);
    imam[karta]--;
    suma += karta;
  }

  x = 21 - suma;

  int vecih = 0;
  for (int i = x + 1; i <= 11; i++)
    vecih += imam[i];

  if (52 - n - vecih > vecih) puts("VUCI");
  else puts("DOSTA");
  return 0;
}
