/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Biura (BIU)                                                *}
{*   Plik:    biu3.cpp                                                   *}
{*   Autor:   Adam Iwanicki                                              *}
{*   Opis:    Rozwiazanie silowe, polegajace znajdowaniu spojnych        *}
{*            skladowych w grafie dopelnionym, korzystajace z obserwacji,*}
{*            ze jestli w grafie oryginalnym jest malo krawedzi, to w    *}
{*            grafie dopelnionym jest spojna skladowa o duzej licznosci  *}
{*                                                                       *}
{*************************************************************************/
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > krawedzie;
vector<int> spojne,licznosci;
int n,m;

bool dfs(int num, int k, int &count, bool force)
{
  vector<int>::const_iterator pocz = krawedzie[num].begin(), kon=krawedzie[num].end();
  spojne[num] = k;
  ++count;

  int last=0;
  bool res = false;
  do {
    int ogr = (pocz == kon) ? n : *pocz++;
    for(int i=last; i<ogr; ++i)
      if (!spojne[i])
        res |= dfs(i,k,count,force);
      else if (spojne[i] != k) {
        if (force)
          res |= dfs(i,k,count,force);
        else 
          res = true;
      }

    last = ogr+1;
  } while (last<n);
  return res;
}

int findk()
{
  long long int k = n>>1;
  while (k*(n-k)>m) --k;
  return k;
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

  int k = n - findk();
  int ile = 0;
  if (k > n>>1) 
    for(int i=0; i<n; ++i)
      if ((int) krawedzie[i].size() < k) {
        spojne[i]=1;
        ++ile;
      } else 
        spojne[i] = 0;


  for(int i=0; i<n; ++i)
    if (!spojne[i])
      sort(krawedzie[i].begin(),krawedzie[i].end());

  if (ile) {
    licznosci.push_back(ile);
    k=1;
  } else
    k=0;

  for (int i=0; i<n; ++i)
    if (!spojne[i]) {
      int ile=0;
      if (dfs(i,k+1, ile,false)) {
        dfs(i,1,licznosci[0],true);
      } else {
        ++k;
        licznosci.push_back(ile);
      }
    }

  sort(licznosci.begin(), licznosci.end());

  printf("%d\n",k);
  for(unsigned int i=0;i<licznosci.size();++i)
    printf("%d ",licznosci[i]);
  printf("\n");
}

