/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Skalniak (SKA)                                             *}
{*   Plik:    skas3.cpp                                                  *}
{*   Autor:   Marek Cygan                                                *}
{*   Opis:    Rozwiazanie wolniejsze od wzorcowego, o zlozonosci         *}
{*            obliczeniowej O(n * 2^n)                                   *}
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

void wczytaj(){
  scanf("%d",&n);
  for (int i=0; i<n; ++i)
    scanf("%d %d %d",x+i,y+i,waga+i);
}

void licz(int pos,int koszt,int x1,int x2,int y1,int y2){
  if ((x2-x1+y2-y1)>obwod) 
    return;
  if (x2-x1+y2-y1==obwod && koszt>koszt_przestawiania) 
    return;
  if (pos==n){
    obwod=x2-x1+y2-y1;
    koszt_przestawiania=koszt;
    for (int i=0; i<n; ++i)
      przestaw[i]=stan[i];  
  } else{
    stan[pos]=0;
    licz(pos+1,koszt,min(x1,x[pos]),max(x2,x[pos]),min(y1,y[pos]),max(y2,y[pos]));
    stan[pos]=1;
    licz(pos+1,koszt+waga[pos],min(x1,y[pos]),max(x2,y[pos]),min(y1,x[pos]),max(y2,x[pos]));
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
  obwod=2*(MAX_ZAKRES+1);
  licz(0,0,MAX_ZAKRES,MIN_ZAKRES,MAX_ZAKRES,MIN_ZAKRES);
  wypisz();
  return 0;
}
