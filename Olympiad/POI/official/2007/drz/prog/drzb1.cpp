/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Drzewa (DRZ)                                               *}
{*   Plik:    drzb1.cpp                                                  *}
{*   Autor:   Anna Niewiarowska                                          *}
{*   Opis:    Rozwiazanie bledne: zle obliczany wspolczynnik             *}
{*            estetycznosci w przypadku zamiany sasiadujacych drzew      *}
{*                                                                       *}
{*************************************************************************/
#include<stdio.h>
#include<stdlib.h>

#define N 50002 

#define bez(x,y) (x>y?(x-y):(y-x))
#define minimum(x,y) (x>y?(y):(x))
#define maximum(x,y) (x>y?(x):(y))

int n; //liczba drzew
int wys[N]; //wysokosci kolejnych drzew
int mozl_zysk[N]; //ile mozemy zarobic wstawiajac na danej pozycji inne drzewo
long long koszt; //koszt pierwotnego rzedu drzew

struct potencjalny_zysk{
  int nr_drzewa;
  int kwota;
};
potencjalny_zysk sort[N];


int policz_koszt(int drzewo, int gdzie) {
  if (gdzie==1) return bez(wys[drzewo],wys[2]);
  if (gdzie==n) return bez(wys[drzewo],wys[n-1]);
  return bez(wys[drzewo],wys[gdzie-1])+bez(wys[drzewo],wys[gdzie+1]);
}

int zysk(int d1, int d2) {
  int n_koszt = policz_koszt(d1,d2)+policz_koszt(d2,d1);
  int s_koszt = policz_koszt(d1,d1)+policz_koszt(d2,d2);
  return s_koszt-n_koszt;
}


void oblicz(int drzewo) {
  long long akt_zysk = 0;
  int tmp;
  
  for (int i=0; i<n; i++) {
    if (mozl_zysk[drzewo]+sort[i].kwota<=akt_zysk) break;
    tmp=zysk(sort[i].nr_drzewa,drzewo);
    if (tmp>akt_zysk) akt_zysk=tmp;
  }
  printf("%lld\n",koszt-akt_zysk);
};

int f_por(const void *v1, const void *v2) {
  potencjalny_zysk* w1 = (potencjalny_zysk*) v1;
  potencjalny_zysk* w2 = (potencjalny_zysk*) v2;
  
  if (w1->kwota > w2->kwota) return -1;
  return 1;
}

void sortuj() {
  for (int i=0; i<n; i++) {sort[i].nr_drzewa=i+1; 
                           sort[i].kwota=mozl_zysk[i+1];}
  qsort(sort,n,sizeof(potencjalny_zysk),f_por);
}

int main() {
  scanf("%d ",&n);
  for (int i=1; i<=n; i++) scanf("%d ", &wys[i]);
  
  koszt=0;
  for (int i=2; i<=n; i++) koszt+=bez(wys[i],wys[i-1]);

  mozl_zysk[1]=bez(wys[2],wys[1]);
  mozl_zysk[n]=bez(wys[n-1],wys[n]);
  for (int i=2; i<n; i++) { 
    mozl_zysk[i]=2*(wys[i]-maximum(wys[i-1],wys[i+1]));
    if (mozl_zysk[i]<0) mozl_zysk[i]=2*(minimum(wys[i-1],wys[i+1])-wys[i]);
    if (mozl_zysk[i]<0) mozl_zysk[i]=0;
  } 
  sortuj(); //sortuje drzewa po tym, o ile mozna zmniejszyc koszty
  
  for (int i=1; i<=n; i++) oblicz(i);
  return 0;
}
