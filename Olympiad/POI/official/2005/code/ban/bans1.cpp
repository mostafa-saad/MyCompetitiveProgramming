/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: BAN (Banknoty)                                 *
 *   Plik:                bans1.cpp                                      *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwi±zanie nieoptymalne do zadania BAN        *
 *                        Jêzyk: C++                                     *
 *                        (analizuje ka¿dy banknot z osobna)             *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<algorithm>
using namespace std;

const int MAX_N = 200;
const int MAX_K = 20000;
const int NIESKONCZONOSC = 1000000000;

int n,k,liczba;
int b[MAX_N + 1],c[MAX_N + 1];
int R[MAX_K + 1]; /*R[x] to minimalna liczba banknotów, w jakiej mo¿na
                  wyp³aciæ kwotê x przy pomocy dotychczas rozwa¿onych
                  nomina³ów*/
bool W[MAX_K + 1][1601];
int jaki[1601],uzyte[MAX_N + 1];

//Odczyt danych
void odczyt()
{
  int i;
  liczba = 0;
  scanf("%d",&n);
  for(i = 0;i < n;i++)
    scanf("%d",&b[i]);
  for(i = 0;i < n;i++)
  {
    scanf("%d",&c[i]);
    liczba += c[i];
  }
  scanf("%d",&k);
} //odczyt

//Inicjalizacja tablic R i W
void inicjuj()
{
  R[0] = 0;
  for(int i = 1;i <= k;i++)
    R[i] = NIESKONCZONOSC;
  for(int i = 0;i <= k;i++)
    for(int j = 0;j <= liczba;j++)
      W[i][j] = false;
} //inicjuj

//Obliczenie wszystkich pól tablicy R dla kolejnych banknotów
void oblicz()
{
  int ktory = 0;
  for(int nr = 0;nr < n;nr++) //pêtla po wszystkich nomina³ach
    for(int j = 0;j < c[nr];j++) //pêtla po liczbie banknotów danego nomina³u
    {
      ktory++;
      jaki[ktory] = nr;
      for(int poz = k - b[nr];poz >= 0;poz--)
        if (R[poz] + 1 < R[poz + b[nr]])
        {
          W[poz + b[nr]][ktory] = true;
          R[poz + b[nr]] = R[poz] + 1;
        } //if
    } //for
} //oblicz

void pisz(int k,int n)
{
  if (n > 0)
    pisz(k - (!W[k][n] ? 0 : b[jaki[n]]),n - 1);
  if (W[k][n])
    uzyte[jaki[n]]++;
} //pisz

int main()
{
  odczyt();
  inicjuj();
  oblicz();
  for(int i = 0;i < n;i++)
    uzyte[i] = 0;
  pisz(k,liczba);
  printf("%d\n",R[k]);
  for(int i = 0;i < n-1;i++)
    printf("%d ",uzyte[i]);
  printf("%d\n",uzyte[n-1]);
  return 0;
} //main
