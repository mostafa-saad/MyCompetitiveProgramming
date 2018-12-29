/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: BAN (Banknoty)                                 *
 *   Plik:                ban0.cpp                                       *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwi±zanie wzorcowe do zadania BAN (Banknoty) *
 *                        Jêzyk: C++ bez u¿ycia STL                      *
 *                                                                       *
 *************************************************************************/
#include<cstdio>
using namespace std;

const int MAX_N = 200;
const int MAX_K = 20000;
const int NIESKONCZONOSC = 1000000000;

//Element listy wska¼nikowej
struct Element
{
  int w; //warto¶æ
  Element *nast,*pop; //wska¼niki do poprzedniego i kolejnego elementu listy
};

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
  for(int r = 0;r < b[nr];r++) //r-kolejna reszta modulo nomina³ b[nr]
  {
    Element *head = NULL, *tail = NULL;
    int i = 0;
    while (r + i*b[nr] <= k)
    {
      M[i] = (R[r + i*b[nr]] == NIESKONCZONOSC) ? 
        NIESKONCZONOSC : R[r + i*b[nr]] - i;
      while (tail != NULL && M[tail->w] >= M[i])
      {
        //usuniêcie ostatniego elementu z kolejki
        Element *tmp = tail->pop;
        delete(tail);
        tail = tmp;
        if (tail == NULL)
          head = NULL;
        else
          tail->nast = NULL;
      } //while
      
      //w³o¿enie liczby i na koniec kolejki
      Element *tmp = new(Element);
      tmp->w = i;
      tmp->nast  = NULL;
      tmp->pop   = tail;
      if (tail != NULL)
        tail->nast = tmp;
      tail = tmp;
      if (head == NULL)
        head = tail;
      
      R[r + i*b[nr]] = M[head->w] + i;
      wyn[r + i*b[nr]][nr] = i - head->w;
      if (head->w == i - c[nr])
      {
        //usuniêcie pierwszego elementu z kolejki
        Element *tmp = head->nast;
        delete(head);
        head = tmp;
        if (head == NULL)
          tail = NULL;
        else
          head->pop = NULL;
      } //if
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
