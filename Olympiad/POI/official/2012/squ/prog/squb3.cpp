/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Squarki                                          *
 *   Autor:             Alan Kutniewski                                  *
 *   Opis:              Rozwiazanie bledne: zaklada, ze a_2+a_3 jest     *
 *                      najwieksza z mozliwych                           *
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

map<int, int> oczekiwane; //mapa oczekiwanych mas

int main(){
  ios_base::sync_with_stdio(0);
  cin >> n; //wczytujemy dane
  ilepar = (n * (n - 1)) / 2;
  for(int i = 0; i < ilepar; ++i){
    cin >> pary[i]; //wczytywanie par
  }
  sort(pary, pary+ilepar);
    a[0] = pary[0] + pary[1] - pary[n - 1]; //obliczanie a1
    a[0] /= 2;
    a[1] = pary[0] - a[0]; //a2
    a[2] = pary[1] - a[0]; //i a3
    //inicjalizacja oczekiwanych, dodawanie do nich a1+a2, a1+a3 i a2+a3
    oczekiwane.clear();
    for(int j = 0; j < ilepar; ++j){
        oczekiwane[pary[j]] = 0;
    }
    ++oczekiwane[a[0] + a[1]];
    ++oczekiwane[a[0] + a[2]];
    ++oczekiwane[a[1] + a[2]];
    int znalezione = 3;
    bool ok = true;
    for(int j = 0; j < ilepar; ++j){ //przegladanie par
        if(oczekiwane[pary[j]] > 0)--oczekiwane[pary[j]]; //oczekiwana
        else{ //nieoczekiwana, czyli masa nowego kwarka
            if(znalezione >= n){ //za duzo kwarkow
                j = ilepar;
                ok = false;
            }
            else{ //dodanie nowego kwarka
                a[znalezione] = pary[j] - a[0];
                for(int l = 1; l < znalezione; ++l)++oczekiwane[a[l] + a[znalezione]];
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
  cout << ilewynik << endl; //wypisanie wyniku
  for(int i = 0; i < ilewynik; ++i){
    for(int j = 0; j < n; ++j){
      cout << wynik[i][j] << " ";
    }
    cout << "\n";
  }
  return 0;
}
