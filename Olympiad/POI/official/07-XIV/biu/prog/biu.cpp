/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Biura (BIU)                                                *}
{*   Plik:    biu.cpp                                                    *}
{*   Autor:   Adam Iwanicki                                              *}
{*   Opis:    Rozwiazanie wzorcowe, polegajace znajdowaniu spojnych      *}
{*            skladowych w grafie dopelnionym przy pomocy struktury      *}
{*            Finf & Union o zlozonosci O((n+m)log^* n)                  *}
{*                                                                       *}
{*************************************************************************/
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

vector<vector<int> > krawedzie;
vector<int> spojne, przetwarzane, liczniki;

int n,m,ile;

int find(int a)
{
  if (spojne[a] < 0) 
    return a;
  else
    return spojne[a] = find(spojne[a]);
}

void join(int a, int b)
{
  a = find(a);
  b = find(b);
  if (a!=b) {
    if (spojne[a] > spojne[b])
      swap(a,b);
    spojne[a]+=spojne[b];
    spojne[b] = a;
  }
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
  przetwarzane.resize(n);
  liczniki.resize(n);
  ile = n;
  for(int i=0; i<n; ++i) {
    spojne[i] = -1;
    przetwarzane[i] = i;
  }

  for (int i=0; i<n; ++i) {
    for(int j=0; j<ile; liczniki[przetwarzane[j++]]=0);

    for(__typeof(krawedzie[i].begin()) it = krawedzie[i].begin(); it != krawedzie[i].end(); ++it) {
      ++liczniki[find(*it)];
    }

    for(int j=0; j< ile; ++j)
      if (liczniki[przetwarzane[j]] != -spojne[przetwarzane[j]])
        join(i,przetwarzane[j]);

    for(int j=0; j<ile;) {
      if (spojne[przetwarzane[j]] < 0)
        ++j;
      else
        przetwarzane[j] = przetwarzane[--ile];
    }
  }

  for(int i=0; i< ile; ++i) 
    liczniki[i]=-spojne[przetwarzane[i]];

  sort(liczniki.begin(), liczniki.begin()+ile);

  printf("%d\n",ile);
  for(int i=0;i<ile;++i)
    printf("%d ",liczniki[i]);
  printf("\n");
}
