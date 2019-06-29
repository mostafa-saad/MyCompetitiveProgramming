/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Skalniak (SKA)                                             *}
{*   Plik:    skas2.cpp                                                  *}
{*   Autor:   Marek Cygan                                                *}
{*   Opis:    Rozwiazanie wolniejsze od wzorcowego, o zlozonosci         *}
{*            obliczeniowej O(n^3)                                       *}
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

inline bool pomiedzy(int x,int a,int b){
  return x>=a && x<=b;
}

//w procedurze probujemy minimalnym kosztem przestawiac kamienie, aby miescily sie
//w prostokacie o rogach (x1,y1) (x2,y2)
void probuj(int x1,int x2,int y1,int y2){
  int nowy_obwod=x2-x1+y2-y1;
  if (nowy_obwod>obwod) 
    return;
  int koszt=0;
  for (int i=0; i<n; ++i)
    if (pomiedzy(x[i],x1,x2) && pomiedzy(y[i],y1,y2))
      stan[i]=0;
    else if (pomiedzy(y[i],x1,x2) && pomiedzy(x[i],y1,y2)){
      stan[i]=1;
      koszt+=waga[i];
      if (nowy_obwod==obwod && koszt>=koszt_przestawiania) return;
    } else return;
  obwod=nowy_obwod;
  koszt_przestawiania=koszt;
  for (int i=0; i<n; ++i) 
    przestaw[i]=stan[i];
}

void licz(){
  int minimum=x[0],maksimum=x[0];
  obwod=2*(MAX_ZAKRES+1);
  for (int i=0; i<n; ++i){
    prog[2*i]=x[i];
    prog[2*i+1]=y[i];
  }
  for (int i=0; i<2*n; ++i){
    minimum=min(minimum,prog[i]);
    maksimum=max(maksimum,prog[i]);
  }
  for (int i=0; i<2*n; ++i)
    for (int j=0; j<2*n; ++j){
      probuj(minimum,maksimum,prog[i],prog[j]);
      probuj(prog[i],prog[j],minimum,maksimum);
      probuj(minimum,prog[i],prog[j],maksimum);
      probuj(prog[i],maksimum,minimum,prog[j]);
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
