/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: BAN (Banknoty)                                 *
 *   Plik:                banb0.cpp                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwi±zanie b³êdne do zadania BAN (Banknoty)   *
 *                        Jêzyk: C++ z u¿yciem STL                       *
 *                                                                       *
 *************************************************************************/
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAX_N = 100000;
const int MAX_K = 100000;
const int NIESKONCZONOSC = 1000000000;

int n,k,wyn;
int b[MAX_N + 1],c[MAX_N + 1];
int w[MAX_N + 1];

//Odczyt danych
void odczyt()
{
  int i;
  scanf("%d",&n);
  for(i = 0;i < n;i++)
    scanf("%d",&b[i]);
  for(i = 0;i < n;i++)
    scanf("%d",&c[i]);
  scanf("%d",&k);
} //odczyt

int main()
{
  odczyt();
  wyn = 0;
  for(int i = n-1;i >= 0;i--)
  {
    int ile_razy = min(c[i],k/b[i]);
    k -= ile_razy*b[i];
    wyn += ile_razy;
    w[i] = ile_razy;
  } //for
  printf("%d\n",wyn);
  for(int i = 0;i < n - 1;i++)
    printf("%d ",w[i]);
  printf("%d\n",w[n-1]);
  return 0;
} //main
