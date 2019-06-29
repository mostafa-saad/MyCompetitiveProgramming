/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Skalniak (SKA)                                             *}
{*   Plik:    skas1.cpp                                                  *}
{*   Autor:   Marek Cygan                                                *}
{*   Opis:    Rozwiazanie wolniejsze od wzorcowego, o zlozonosci         *}
{*            obliczeniowej O(n^2)                                       *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAX_N=1000000, MAX_WAGA=2000, MAX_ZAKRES=1000000000, MIN_ZAKRES=0;
int n; //liczba kamieni
int x[MAX_N],y[MAX_N],waga[MAX_N]; //wspolrzedne oraz wagi kamieni
int przestaw[MAX_N]; //wektor przestawien dla najlepszego dotychczas
                     //znalezionego wyniku
int koszt_przestawiania, obwod; //najlepsze znalezione rozwiazanie
int stan[MAX_N]; //aktualny wektor przestawien
int prog[2*MAX_N]; //tablica pomocnicza ze wszystkimi wspolrzednymi

void wczytaj(){
  scanf("%d",&n);
  for (int i=0; i<n; ++i)
    scanf("%d %d %d",x+i,y+i,waga+i);
}

//jesli liczba b jest ujemna, zamieniamy liczbe b na -b+1
inline bool pomiedzy(int x,int a,int b){
  if (b<0) b=-b-1;
  return x>=a && x<=b;
}

//w procedurze probujemy przestawiac kamienie (bez wzgledu na koszt) tak,
//aby miescily sie w prostokacie (x1,y1) (x2,y2), ale jedna z liczb x2,y2
//(ktora jako podawana jako argument jest ujemna) ma nieustalona wartosc,
//ktora chcemy zminimalizowac
void probuj(int x1,int x2,int y1,int y2){
  for (int i=0; i<n; ++i)
    if (!(pomiedzy(x[i],x1,x2) && pomiedzy(y[i],y1,y2))
        && !(pomiedzy(y[i],x1,x2) && pomiedzy(x[i],y1,y2))){
      int a=x[i];
      int b=y[i];
      if (a>b) swap(a,b);
      if (x2<0){
        if (a>=x1 && pomiedzy(b,y1,y2)) x2=-a-1;
        else if (b>=x1 && pomiedzy(a,y1,y2)) x2=-b-1;
        else return;
      } else{
        /*y2<0*/
        if (a>=y1 && pomiedzy(b,x1,x2)) y2=-a-1;
        else if (b>=y1 && pomiedzy(a,x1,x2)) y2=-b-1;
        else return;
      }
    }
  if (x2<0) x2=-x2-1;
  if (y2<0) y2=-y2-1;
  obwod=min(obwod,x2-x1+y2-y1);
}

//w procedurze probujemy minimalnym kosztem przestawiac kamienie, aby miescily sie
//w prostokacie o rogach (x1,y1) (x2,y2)
void ustaw(int x1,int x2,int y1,int y2){
  int koszt=0;
  for (int i=0; i<n; ++i)
    if (pomiedzy(x[i],x1,x2) && pomiedzy(y[i],y1,y2))
      stan[i]=0;
    else if (pomiedzy(y[i],x1,x2) && pomiedzy(x[i],y1,y2)){
      stan[i]=1;
      koszt+=waga[i];
      if (koszt>=koszt_przestawiania) return;
    } else return;
  koszt_przestawiania=koszt;
  for (int i=0; i<n; ++i) 
    przestaw[i]=stan[i];
}

void licz(){
  int minimum=x[0],maksimum=x[0];
  for (int i=0; i<n; ++i){
    prog[2*i]=x[i];
    prog[2*i+1]=y[i];
  }
  for (int i=0; i<2*n; ++i){
    minimum=min(minimum,prog[i]);
    maksimum=max(maksimum,prog[i]);
  }

  //najpierw obliczamy obwod optymalnego ustawienia
  obwod=2*(MAX_ZAKRES+1);
  for (int i=0; i<2*n; ++i){
    probuj(minimum,maksimum,prog[i],-prog[i]-1);
    probuj(prog[i],-prog[i]-1,minimum,maksimum);
    probuj(minimum,-minimum-1,prog[i],maksimum);
    probuj(prog[i],maksimum,minimum,-minimum-1);
  }

  //teraz obliczamy minimalny koszt przestawienia,
  //przy zachowaniu minimalnego obwodu
  koszt_przestawiania=MAX_N*(MAX_WAGA+1);
  for (int i=0; i<2*n; ++i){
    ustaw(minimum,maksimum,prog[i],prog[i]+obwod-(maksimum-minimum));
    ustaw(prog[i],prog[i]+obwod-(maksimum-minimum),minimum,maksimum);
    ustaw(minimum,minimum+obwod-(maksimum-prog[i]),prog[i],maksimum);
    ustaw(prog[i],maksimum,minimum,minimum+obwod-(maksimum-prog[i]));
  }
}

void wypisz(){
  printf("%u %u\n",2*obwod,koszt_przestawiania);
  for (int i=0; i<n; ++i)
    printf("%d",przestaw[i]);
  printf("\n");
}

int main(){
  wczytaj();
  licz();
  wypisz();
  return 0;
}
