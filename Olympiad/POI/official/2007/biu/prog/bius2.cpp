/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Biura (BIU)                                                *}
{*   Plik:    bius2.cpp                                                  *}
{*   Autor:   Adam Iwanicki                                              *}
{*   Opis:    Rozwiazanie wolne, polegajace znajdowaniu spojnych         *}
{*            skladowych w grafie dopelnionym, korzystajace ze struktury *}
{*            Find & Union                                               *}
{*                                                                       *}
{*************************************************************************/
#include <vector>
#include <utility>
#include <algorithm>
#include <set>

using namespace std;

vector<vector<int> > krawedzie;
vector<int> spojne, przetwarzane, liczniki;

vector<int> kolejka;

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
  liczniki.resize(n);
  przetwarzane.resize(n);
  ile = n;
  for(int i=0; i<n; ++i) {
    spojne[i] = -1;
    przetwarzane[i] = i;
    kolejka.push_back(i);
  }

  while (kolejka.size()){
    int akt = kolejka.back(); kolejka.pop_back();
    if (spojne[akt] >=0) continue;
    vector<int> polaczone;
    multiset<int> edges;
    
    for(int j=0; j<ile; liczniki[przetwarzane[j++]]=0);

    for(__typeof(krawedzie[akt].begin()) it = krawedzie[akt].begin(); it != krawedzie[akt].end(); ++it)
      ++liczniki[find(*it)];
    
    for(int j=0; j< ile; ++j)
      if (!liczniki[przetwarzane[j]]) {
        join(akt,przetwarzane[j]);
        if (przetwarzane[j]!=akt) polaczone.push_back(przetwarzane[j]);
      }

    if (polaczone.size()) {
      polaczone.push_back(akt);
      for(__typeof(polaczone.begin()) it=polaczone.begin(); it != polaczone.end(); ++it) {
        set<int> own;
        int w = *it;
        for(__typeof(krawedzie[w].begin()) kr = krawedzie[w].begin(); kr != krawedzie[w].end(); ++kr) 
          own.insert(find(*kr));
        edges.insert(own.begin(), own.end());
      }
      akt = find(akt);
      krawedzie[akt].clear();
      int size = polaczone.size();
      for(__typeof(edges.begin()) it=edges.begin(); it!=edges.end(); ++it)
        if ((int)edges.count(*it) == size)
          krawedzie[akt].push_back(*it);
    }

    for(int j=0; j<ile;) {
      if (spojne[przetwarzane[j]] < 0)
        ++j;
      else
        przetwarzane[j] = przetwarzane[--ile];
    }

    if (polaczone.size())
      kolejka.push_back(akt);
  }

  for(int i=0; i< ile; ++i) 
    liczniki[i]=-spojne[przetwarzane[i]];

  sort(liczniki.begin(), liczniki.begin()+ile);

  printf("%d\n",ile);
  for(int i=0;i<ile;++i)
    printf("%d ",liczniki[i]);
  printf("\n");
}
