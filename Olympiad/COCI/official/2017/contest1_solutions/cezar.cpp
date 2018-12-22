#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 110;
const int SLOVA = 26;

int mat[SLOVA][SLOVA];

vector<int> graf[MAXN];

int n;

string unos[MAXN], glavni[MAXN];

int in[SLOVA];

int bio[SLOVA];

vector<int> ispis;

int lcp(int a, int b)
{
  int kraj = min((int)glavni[a].size(), (int)glavni[b].size());
  int i = 0;
  for(; i < kraj; i++)
    if(glavni[a][i] != glavni[b][i]) 
      break;
  return i;
}

int pref(int a, int b)
{
  int x = lcp(a, b);
  if(x == (int)glavni[a].size()) return 1;
  return 0;
}

void dodaj(int x, int y)
{
  if(mat[x][y]) return;
  mat[x][y] = 1;
  graf[x].push_back(y);
  in[y]++;
}

int da;

void rek(int cvor)
{
  if(bio[cvor])
  {
    da = 1;
    return;
  }
  bio[cvor] = 1;
  for(int i = 0; i < (int) graf[cvor].size(); i++)
    rek(graf[cvor][i]);
  bio[cvor] = 0;
}

void topoloski(int cvor)
{
  if(bio[cvor]) return;
  bio[cvor] = 1;
  for(int i = 0; i < (int)graf[cvor].size(); i++)
    topoloski(graf[cvor][i]);
  ispis.push_back(cvor);
}

int main()
{
  cin >> n;
  for(int i = 0; i < n; i++)
    cin >> unos[i];
  for(int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    x--;
    glavni[i] = unos[x];
  }
  for(int i = 0; i < n; i++)
    for(int j = 0; j < i; j++)
      if(pref(i, j))
      {
        cout << "NE" << endl;
        return 0;
      }
  for(int i = 0; i < n - 1; i++)
  {
    if(pref(i, i + 1)) continue;
    for(int j = 0; ; j++)
    {
      if(glavni[i][j] != glavni[i + 1][j])
      {
        dodaj(glavni[i + 1][j] - 'a', glavni[i][j] - 'a');
        break;
      }
    }
  }
  for(int i = 0; i < SLOVA; i++)
  {
    memset(bio, 0, sizeof(bio));
    da = 0;
    rek(i);
    if(da)
    {
      cout << "NE" << endl;
      return 0;
    }
  }
  memset(bio, 0, sizeof(bio));
  for(int i = 0; i < SLOVA; i++)
    if(!in[i])
      topoloski(i);
  cout << "DA" << endl;
  int rj[MAXN];
  for(int i = 0; i < (int)ispis.size(); i++)
    rj[ispis[i]] = i;
  for(int i = 0; i < SLOVA; i++)
    cout << (char)(rj[i] + 'a');
  cout << endl;
  return 0;
}
