/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Squarki                                          *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n^5)                                           *
 *   Opis:              Rozwiazanie powolne: nieefektywna struktura      *
 *                      danych                                           *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <algorithm>
#include <map>
#define MAXN 300
#define MAXV 100000001

using namespace std;

int pary[MAXN*MAXN]; //masy par kwarkow
int a[MAXN]; //masy pojedynczych kwarkow
int wynik[MAXN][MAXN]; //tablica wynikow
int ilewynik; //ilosc wynikow

int n, ilepar; //ilosc kwarkow i par

struct para{
    int wartosc;
    int klucz;
}_p;

para oczekiwane_wartosci[MAXN*MAXN];

int ile(int klucz){
    for(int i = 0; i < ilepar; ++i){
        if(oczekiwane_wartosci[i].klucz == klucz)return oczekiwane_wartosci[i].wartosc;
    }
    return -1;
}

void zmniejsz(int klucz){
    for(int i = 0; i < ilepar; ++i){
        if(oczekiwane_wartosci[i].klucz == klucz)--oczekiwane_wartosci[i].wartosc;
    }
}

void zwieksz(int klucz){
    for(int i = 0; i < ilepar; ++i){
        if(oczekiwane_wartosci[i].klucz == klucz)++oczekiwane_wartosci[i].wartosc;
    }
}

void inicjalizuj(){
    for(int i = 0; i < ilepar; ++i){
        oczekiwane_wartosci[i].klucz = pary[i];
        oczekiwane_wartosci[i].wartosc = 0;
    }
}

int main(){
  ios_base::sync_with_stdio(0);
  cin >> n; //wczytujemy dane
  ilepar = (n * (n - 1)) / 2;
  for(int i = 0; i < ilepar; ++i){
    cin >> pary[i]; //wczytywanie par
  }
  sort(pary, pary+ilepar);
  for(int i = 2; i < n; ++i){ //iteracja po mozliwych masach a2+a3
    a[0] = pary[0] + pary[1] - pary[i]; //obliczanie a1
    if(a[0] % 2 || a[0] < 0)continue; //niecalkowita masa
    if(i > 2 && pary[i] == pary[i - 1])continue;
    a[0] /= 2;
    a[1] = pary[0] - a[0]; //a2
    a[2] = pary[1] - a[0]; //i a3
    //inicjalizacja oczekiwanych, dodawanie do nich a1+a2, a1+a3 i a2+a3
        inicjalizuj();
    zwieksz(a[0] + a[1]);
    zwieksz(a[0] + a[2]);
    zwieksz(a[1] + a[2]);
    int znalezione = 3;
    bool ok = true;
    for(int j = 0; j < ilepar; ++j){ //przegladanie par
            int ilosc = ile(pary[j]);
      if(ilosc > 0)zmniejsz(pary[j]); //oczekiwana
      else{ //nieoczekiwana, czyli masa nowego kwarka
        if(ilosc == -1 || znalezione >= n){ //za duzo kwarkow
          j = ilepar;
          ok = false;
        }
        else{ //dodanie nowego kwarka
          a[znalezione] = pary[j] - a[0];
          for(int l = 1; l < znalezione; ++l)zwieksz(a[l] + a[znalezione]);
          ++znalezione;
        }
      }
    }
    if(znalezione == n && ok){ //jesli poszlo ok
            for(int j = 1; j < n; ++j){
                if(a[j] == a[j - 1])ok = false;
            }
      if(ok){
                for(int j = 0; j < n; ++j){ //dodajemy wynik do tablicy wynikow
            wynik[ilewynik][j] = a[j];
          }
          ++ilewynik;
            }
    }
  }
  cout << ilewynik << endl; //wypisanie wyniku
  for(int i = 0; i < ilewynik; ++i){
    for(int j = 0; j < n; ++j){
      cout << wynik[i][j] << " ";
    }
    cout << "\n";
  }
  return 0;
}
