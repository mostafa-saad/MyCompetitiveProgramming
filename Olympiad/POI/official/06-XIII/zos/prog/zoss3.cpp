/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ZOS (Zosia)                                    *
 *   Plik:                zoss3.cpp                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                                                                       *
 *                        Program rozrzedza graf, po czym uruchamia na   *
 *                        nim przeszukiwanie wszystkich podzbiorów       *
 *                        zbioru wierzcho³ków.                           *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;


#define MAX_N 1000000

int n, m, k, n0;
vector<int> t[MAX_N];
bool pokryte[MAX_N];
int numer[110];
int antynumer[MAX_N];
vector<int> pokrycie;


void odczyt()
{
  scanf("%d%d%d", &n, &k, &m);
  k = n - k; /* ¿eby szukaæ pokrycia wielko¶ci k */
  for (int i = 0; i < m; i++)
  {
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    t[a].push_back(b);
    t[b].push_back(a);
  }
  n0 = n;
}

/* Przerzedzamy graf */
bool przerzedzenie()
{
  /* Do pokrycia bierzemy wierzcho³ki o stopniach > 10 */
  for (int i = 0; i < n; i++)
    pokryte[i] = false;
  int ile = 0;
  for (int i = 0; i < n; i++)
    if ((int)t[i].size() > k)
    {
      pokryte[i] = true;
      pokrycie.push_back(i);
      ile++;
    }
  if (ile > k)
    return false;
  /* Usuwamy tak wybrane krawêdzie */
  ile = 0;
  for (int i = 0; i < n; i++)
  {
    if (pokryte[i])
      t[i].clear();
    int j = 0;
    while (j < (int)t[i].size())
    {
      if (pokryte[t[i][j]])
      {
        swap(t[i][j], t[i].back());
        t[i].pop_back();
        j--;
      }
      j++;
    }
    ile += t[i].size();
  }
  if (ile > 2 * k * k)
    return false;
  /* I robimy nowy graf */
  ile = 0;
  for (int i = 0; i < n; i++)
    if (t[i].size())
    {
      numer[ile] = i;
      antynumer[i] = ile;
      if (ile != i)
        t[ile] = t[i];
      ile++;
    }
  for (int i = 0; i < ile; i++)
    for (int j = 0; j < (int)t[i].size(); j++)
      t[i][j] = antynumer[t[i][j]];
  n = ile; /* nowy graf ma mniej wierzcho³ków */
  return true;
}

int wyn; /* najlepsze uzyskane pokrycie */
int ile_max; /* jakie max pokrycie mo¿emy wzi±æ */
vector<int> akt, w;

void brucik(int v, int ile)
{
  bool czy = true;
  for (int i = 0; i < n; i++)
  {
    if (pokryte[i])
      continue;
    for (int j = 0; j < (int)t[i].size(); j++)
      if (!pokryte[t[i][j]])
      {
        czy = false;
        break;
      }
    if (!czy)
      break;
  }
  if (czy) /* mamy pokrycie */
  {
    if (ile < wyn)
    {
      wyn = ile;
      w = akt;
    }
    return;
  }
  if (v >= n || ile > wyn)
    return;

  for (int i = v; i < n; i++)
  {
    pokryte[i] = true;
    akt.push_back(numer[i]);
    brucik(i + 1, ile + 1);
    akt.pop_back();
    pokryte[i] = false;
  }
}

int main()
{
  odczyt();
  /* Usuwamy powtórzenia krawêdzi */
  for (int i = 0; i < n; i++)
  {
    sort(t[i].begin(), t[i].end());
    t[i].erase(unique(t[i].begin(), t[i].end()), t[i].end());
  }
  if (!przerzedzenie())
    printf("NIE\n");
  else
  {
    for (int i = 0; i < n; i++)
      pokryte[i] = false;
    ile_max = k - pokrycie.size();
    wyn = ile_max + 1;
    brucik(0, 0);
    if (wyn > ile_max)
      printf("NIE\n");
    else
    {
      /* Uda³o siê - wypisujemy zbiór niezale¿ny. */
      for (int i = 0; i < (int)w.size(); i++)
        pokrycie.push_back(w[i]);
      sort(pokrycie.begin(), pokrycie.end());
      printf("%d\n", n0 - pokrycie.size());
      int j = 0;
      for (int i = 0; i < n0; i++)
        if (j < (int)pokrycie.size() && pokrycie[j] == i)
          j++;
        else
          printf("%d ", i + 1);
      printf("\n");
    }
  }
  return 0;
}
