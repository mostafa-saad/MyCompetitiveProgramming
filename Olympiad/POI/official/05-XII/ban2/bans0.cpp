/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: BAN (Banknoty)                                 *
 *   Plik:                ban.cpp                                        *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwi±zanie nieoptymalne do zadania BAN        *
 *                        Jêzyk: C++                                     *
 *                        (backtracking)                                 *
 *                                                                       *
 *************************************************************************/
#include<cstdio>
#include<algorithm>
using namespace std;

const int MAX_N = 200;
const int MAX_K = 20000;
const int NIESKONCZONOSC = 1000000000;

int n,k,wyn;
int b[MAX_N + 1],c[MAX_N + 1];
int tab[MAX_N + 1];
int t[MAX_N + 1];

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

/* Rekurencyjny backtracking; analizuje banknoty w kolejno¶ci malej±cych
 * nomina³ów, ka¿dego banknotu bierze dowoln± dozwolon± liczbê sztuk
 * i kontynuuje wyszukiwanie.*/
void oblicz(int nr,int kw,int akt) //parametry: numer banknotu, kwota do
                                   //wyp³acenia i liczba ju¿ zu¿ytych banknotów
{
  if (akt >= wyn) //nie osi±gniemy w ten sposób mniejszej liczby banknotów
    return;
  if (!kw) //uzyskali¶my kwotê, sprawdzamy, czy zu¿yli¶my ma³o banknotów
  {
    if (akt < wyn)
    {
      for(int i=0;i<n;i++)
        tab[i]=t[i];
      wyn=akt;
    }
  }
  else
  if (nr >= 0)
  {
    int s = min(c[nr],kw/b[nr]);
    for(int i = s;i >= 0;i--)
    {
      t[nr] = i;
      oblicz(nr - 1,kw - i*b[nr],akt + i);
    }
    t[nr] = 0;
  } //if
} //oblicz

int main()
{
  odczyt();
  wyn = NIESKONCZONOSC;
  for(int i = 0;i <= n;i++)
    t[i] = 0;
  oblicz(n - 1,k,0);
  printf("%d\n",wyn);
  for(int i = 0;i < n - 1;i++)
    printf("%d ",tab[i]);
  printf("%d\n",tab[n - 1]);
  return 0;
} //main
