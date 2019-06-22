/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MET (Metro)                                    *
 *   Plik:                metb2.cpp                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie niepoprawne.                       *
 *                        Prosta heurystyka - bierze pod uwage           *
 *                        wierzcholki wewnetrzne: min(2*l,#lisci)        *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
using namespace std;

int n,k,a,b;
int deg[1000000];

int main()
{
  scanf("%d%d",&n,&k);
  for(int i=1;i<n;i++) { scanf("%d%d",&a,&b); a--; b--; deg[a]++; deg[b]++; }
  int wyn=0;
  k*=2;
  for(int i=0;i<n;i++) if (deg[i]>1) wyn++; else if (k && deg[i]==1) { wyn++; k--; }
  printf("%d\n",wyn);
  return 0;
}
