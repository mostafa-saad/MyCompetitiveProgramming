/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Biura (BIU)                                                *}
{*   Plik:    bius1.cpp                                                  *}
{*   Autor:   Adam Iwanicki                                              *}
{*   Opis:    Rozwiazanie silowe, polegajace znajdowaniu spojnych        *}
{*            skladowych w grafie dopelnionym o pesymistycznej           *}
{*            zlozonosci O(n^2)                                          *}
{*                                                                       *}
{*************************************************************************/
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > krawedzie;
vector<int> spojne,licznosci;
int n,m;

void dfs(int num, int k, int &count)
{
  vector<int>::const_iterator pocz = krawedzie[num].begin(), kon=krawedzie[num].end();
  spojne[num] = k;
  ++count;

  int last=0;
  do {
    int ogr = (pocz == kon) ? n : *pocz++;
    for(int i=last; i<ogr; ++i)
      if (!spojne[i])
        dfs(i,k,count);

    last = ogr+1;
  } while (last<n);
}

int main()
{
  scanf("%d %d",&n,&m);
  krawedzie.resize(n);
  for(int i=0; i<m; ++i) {
    int a,b;
    scanf("%d %d",&a, &b);
    --a; --b;
    krawedzie[a].push_back(b);
    krawedzie[b].push_back(a);
  }

  spojne.resize(n);
  for(int i=0; i<n; ++i) {
    sort(krawedzie[i].begin(),krawedzie[i].end());
    spojne[i] = 0;
  }

  int k = 0;
  for (int i=0; i<n; ++i)
    if (!spojne[i]) {
      int ile=0;
      dfs(i,++k, ile);
      licznosci.push_back(ile);
    }

  sort(licznosci.begin(), licznosci.end());

  printf("%d\n",k);
  for(unsigned int i=0;i<licznosci.size();++i)
    printf("%d ",licznosci[i]);
  printf("\n");
}
