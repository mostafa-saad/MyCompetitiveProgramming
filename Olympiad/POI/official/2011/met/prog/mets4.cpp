/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Meteory                                          *
 *   Autor:             Blazej Osinski                                   *
 *   Zlozonosc czasowa: O((m*sqrt(k)+k)*lg(m))                           *
 *   Opis:              Rozwiazanie powolne, sztuczka z pierwiastkiem    *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;

int __abc;
#define scanf __abc=scanf

const int N = 300007;

struct Zapytanie
{
  int l, r, a;
} zap[N];

static const int INF = 1000000000;

//***** Statyczne drzewo przedziałowe  ***** {{{

struct Drzewo {
    static const int WD = 1048677;
    int w[WD], wd;
    Drzewo(int n);
    void czysc();
    int znajdz_wartosc(int a);
    void dodaj_przedzial(int l, int r, int wart);
  private:
    void dodaj_przedzial(int wierz, int l, int r, int wart, int bl, int br);
};

Drzewo::Drzewo(int n){
  wd = 1;
  while (wd < n)
    wd *= 2;
  czysc();
}

void Drzewo::czysc(){
  for(int i = 0; i < 2*wd; i++)
    w[i] = 0;
}


int Drzewo::znajdz_wartosc(int a){
  a += wd;
  int wyn = 0;
  while (a > 0){
    wyn += w[a];
    if(wyn > INF)
      return INF;
    a /= 2;
  }
  return wyn;
}

void Drzewo::dodaj_przedzial(int l, int r, int wart){
  dodaj_przedzial(1, l, r, wart, 0, wd-1);
}

void Drzewo::dodaj_przedzial(int wierz, int l, int r, int wart, int bl, int br){
  if (br < l || r < bl){
    // Przedziały się mijają.
    return; 
  }
  if (l <= bl && br <= r){
    // Przedział bazowy jest zawarty w dodawanym przedziale.
    w[wierz] += wart;
    if(w[wierz] > INF)
      w[wierz] = INF;
    return;
  }
  int sr = (bl+br)/2;
  dodaj_przedzial(2*wierz, l, r, wart, bl, sr);
  dodaj_przedzial(2*wierz+1, l, r, wart, sr+1, br);
}

//******************************************** }}}

int n, m, pot[N], z;
// Stacje posiadane przez konkretne panstwa.
vector<int> stacje[N]; 
// W którym przedziale opadów [1 , sqrt(k)], [sqrt(k)+1 , 2*sqrt(k)] ...
// państwo przekroczyło swój limit opadów.  
int przed[N];
int odp[N];
// Państwa, które kónczą swój limit w odpowiednim przedziale.
vector<int> panstwa[N]; 

int main()
{
  // Wczytywanie danych. 
  scanf("%d %d", &n, &m);
  for(int i = 0; i < m; i++){
    scanf("%d", &z);
    z--;
    stacje[z].push_back(i);
  }
  for(int i = 0; i < n; i++)
    scanf("%d", &pot[i]);
  
  // Wczytywanie zapytań.
  scanf("%d", &z);
  for(int i = 0; i < z; i++){
    scanf("%d %d %d", &zap[i].l, &zap[i].r, &zap[i].a);
    zap[i].l--;
    zap[i].r--;
  }

  for(int i = 0; i < n; i++){
    przed[i] = -1;
    odp[i] = -1;
  }

  // Pierwsza symulacja - wyznaczenie tablicy przed. 
  Drzewo dpm(m);
  // Licznik wskazujący co sqrt(z) zapytanie
  int sqrtz = (int) sqrt(z);
  for(int i = 0; i < z; i++){
    if (zap[i].l <= zap[i].r){
      dpm.dodaj_przedzial(zap[i].l, zap[i].r, zap[i].a); 
    }
    else{
      dpm.dodaj_przedzial(zap[i].l, m-1, zap[i].a); 
      dpm.dodaj_przedzial(0, zap[i].r, zap[i].a); 
    }
    if ((i+1)%sqrtz == 0){
      // W następnym obrocie pętli zmieni się przedział.
      int nrp = i/sqrtz;
      for (int j = 0; j < n; j++) 
        if (przed[j] == -1){
          int suma = 0;
          for(vector<int>::iterator it = stacje[j].begin(); it != stacje[j].end(); ++it){
            suma += dpm.znajdz_wartosc(*it);
            if (suma >= INF)
              break;
          }
          if (suma >= pot[j]){
            przed[j] = nrp;
            panstwa[nrp].push_back(j);
          }
        }
    }
  }

  for (int nrp = (z-1)/sqrtz, j = 0; j < n; j++) 
    if (przed[j] == -1){
      int suma = 0;
      for(vector<int>::iterator it = stacje[j].begin(); it != stacje[j].end(); ++it){
        suma += dpm.znajdz_wartosc(*it);
        if (suma >= INF)
          break;
      }
      if (suma >= pot[j]){
        przed[j] = nrp; 
        panstwa[nrp].push_back(j);
      }
    }

  // Druga symulacja - wyznaczanie dokładnych odpowiedzi
  dpm.czysc();
  vector<int>* zestaw = &panstwa[0];
  for(int i = 0; i < z; i++){
    if (i%sqrtz == 0){
      zestaw = &panstwa[i/sqrtz]; 
    }
    if (zap[i].l <= zap[i].r){
      dpm.dodaj_przedzial(zap[i].l, zap[i].r, zap[i].a); 
    }
    else{
      dpm.dodaj_przedzial(zap[i].l, m-1, zap[i].a); 
      dpm.dodaj_przedzial(0, zap[i].r, zap[i].a); 
    }
    for (int j = 0; j < (int)zestaw->size(); j++){
      //vector<int>::iterator j = zestaw->begin(); j != zestaw->end(); ++j){ 
      int suma = 0, a = (*zestaw)[j];
      for(vector<int>::iterator it = stacje[a].begin(); it != stacje[a].end(); ++it){
        suma += dpm.znajdz_wartosc(*it);
        if (suma >= INF)
          break;
      }
      if (suma >= pot[a]){
        odp[a] = i;
        // Więcej nie trzeba przetwarzać a-tego państwa.
        (*zestaw)[j] = zestaw->back();
        zestaw->pop_back();
        j--;
      }
    }
  }

  for(int i = 0; i < n; i++){
    if(odp[i] != -1)
      printf("%d\n", odp[i]+1);
    else
      printf("NIE\n");
  }
  return 0;
}
