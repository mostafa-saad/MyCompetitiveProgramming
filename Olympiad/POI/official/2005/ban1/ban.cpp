/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: BAN (Bankomat)                                 *
 *   Plik:                ban.cpp                                        *
 *   Autor:               Rafa³ Rusin                                    *
 *   Opis:                Rozwiazanie wzorcowe                           *
 *                                                                       *
 *************************************************************************/

#include <iostream>
using namespace std;
#define FOR(i,n) for(int (i)=0;(i)<(n);(i)++)

typedef short int AutomatEl[10]; //Pojedynczy element automatu

const int MAXN=1000, //Maksymalna ilo¶æ scen
  MAXS=10000; //Maksymalna sekwencja ruchów

AutomatEl *automaty[MAXN];
int slowo[MAXS];

AutomatEl *utworzAutomat(int dlugosc) {
  AutomatEl *a=new AutomatEl[dlugosc];
  {
    int i=dlugosc-1;
    
    FOR(j,10) a[i][j]=-1;
    a[i][slowo[i]]=i;
  }
  
  for(int i=dlugosc-2;i>=0;i--) {
    FOR(j,10) a[i][j]=a[i+1][j];
    a[i][slowo[i]]=i;
  }
  return a;
}

//funkcja sprawdza pin "od konca"
//tzn. automat dla sceny 123 zaakceptuje pin 321
bool sprawdzPin(int pin,AutomatEl *a) {
  int stan=0;
  FOR(i,4) {
    int cyfra=pin%10;
    pin=pin/10;
    
    stan=a[stan][cyfra];
    if (stan==-1) return 0;
  }
  return 1;
}

int main() {
  int n;
  cin>>n;
  FOR(i,n) {
    int dl;
    cin>>dl;
    cin.get();
    FOR(j,dl) {
      slowo[j]=cin.get()-'0';
    }
    automaty[i]=utworzAutomat(dl);
  }
  
  int wynik=0;
  FOR(pin,10000) {
    int czyOk=1;
    FOR(k,n) {
      czyOk=czyOk && sprawdzPin(pin,automaty[k]);
    }
    wynik+=czyOk;
  }
  cout<<wynik<<"\n";
}
