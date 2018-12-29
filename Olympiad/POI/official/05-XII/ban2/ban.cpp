/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: BAN (Banknoty)                                 *
 *   Plik:                ban.cpp                                        *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwi±zanie wzorcowe do zadania BAN (Banknoty) *
 *                        Jêzyk: C++ z u¿yciem STL                       *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<list>
using namespace std;

const int MAX_N = 200;
const int MAX_K = 20000;
const int NIESKONCZONOSC = 1000000000;

int n,k;
int b[MAX_N + 1],c[MAX_N + 1];
int R[MAX_K + 1]; /*R[x] to minimalna liczba banknotów, w jakiej mo¿na
                  wyp³aciæ kwotê x przy pomocy dotychczas rozwa¿onych
                  nomina³ów*/
int M[MAX_K + 1]; /*Tablica pomocniczna zdefiniowana poprzez
                   M[i]=R[r + i*b[nr]] - i dla tablicy R przed uaktualnieniem*/
int wyn[MAX_K + 1][MAX_N + 1]; /*Tablica wskazuj±ca dla ka¿dej kwoty i dla
                                 ka¿dego banknotu, ile sztuk tego banknotu
                                 zosta³o u¿yte w optymalnym otrzymaniu kwoty*/

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

//Inicjalizacja tablic R i wyn
void inicjuj()
{
  R[0] = 0;
  for(int i = 1;i <= k;i++)
    R[i] = NIESKONCZONOSC;
  for(int i = 0;i <= k;i++)
    for(int j = 1;j <= n;j++)
      wyn[i][j]=0;
} //inicjuj

//Aktualizuje tablicê R, analizuj±c kolejny nomina³ banknotów (o numerze nr)
void aktualizuj(int nr)
{
  list<int> kolejka;
  for(int r = 0;r < b[nr];r++) //r-kolejna reszta modulo nomina³ b[nr]
  {
    kolejka.clear();
    int i = 0;
    while (r + i*b[nr] <= k)
    {
      M[i] = R[r + i*b[nr]] - i;
      while (!kolejka.empty() && M[kolejka.back()] >= M[i])
        kolejka.pop_back();
      kolejka.push_back(i);
      R[r + i*b[nr]] = M[kolejka.front()] + i;
      wyn[r + i*b[nr]][nr] = i - kolejka.front();
      if (kolejka.front() == i - c[nr])
        kolejka.pop_front();
      i++;
    } //while
  } //for
} //aktualizuj

void pisz(int n,int k)
{
  if (n > 0)
    pisz(n - 1,k - wyn[k][n]*b[n]);
  if (!n)
    printf("%d",wyn[k][n]);
  else
    printf(" %d",wyn[k][n]);
} //pisz

int main()
{
  odczyt();
  inicjuj();
  for(int i = 0;i < n;i++)
    aktualizuj(i);
  printf("%d\n",R[k]);
  pisz(n - 1,k);
  printf("\n");
  return 0;
} //main
