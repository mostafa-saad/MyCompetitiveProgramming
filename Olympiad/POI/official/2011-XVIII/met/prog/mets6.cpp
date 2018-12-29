/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Meteory                                          *
 *   Autor:             Blazej Osinski                                   *
 *   Zlozonosc czasowa: O((m*sqrt(k)+k)*lg(m))                           *
 *   Opis:              Rozwiazanie powolne, sztuczka z pierwiastkiem    *
 *                      z optymalizacja w drugim przebiegu symulacji     *
 *                      oraz optymalizacja na duza liczbe odp. "NIE"     *
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

int wielkosc_przeciecia(const Zapytanie & zap, const vector<int>& stacje);

static const int INF = 1000000000;

//***** Statyczne drzewo przedziałowe  **** {{{

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
int sumy[N];
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
    sumy[i] = 0;
  }

  // Zerowa symulacja - wyznaczenie zbioru tak. 
  Drzewo dpm(m);
  vector<int> tak;
  // Licznik wskazujący co sqrt(z) zapytanie
  int sqrtz = (int)sqrt(z);

  for(int i = 0; i < z; i++){
    if (zap[i].l <= zap[i].r){
      dpm.dodaj_przedzial(zap[i].l, zap[i].r, zap[i].a); 
    }
    else{
      dpm.dodaj_przedzial(zap[i].l, m-1, zap[i].a); 
      dpm.dodaj_przedzial(0, zap[i].r, zap[i].a); 
    }
  }
  for (int j = 0; j < n; j++) 
  {
    int suma = 0;
    for(vector<int>::iterator it = stacje[j].begin(); it != stacje[j].end(); ++it){
      suma += dpm.znajdz_wartosc(*it);
      if (suma >= INF)
        break;
    }
    if (suma >= pot[j]){
      tak.push_back(j);
    }
  }

  // Pierwsza symulacja - wyznaczenie tablicy przed. 
  dpm.czysc();
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
      for (int l = 0; l < (int) tak.size(); l++){
        int suma = 0;
        int j = tak[l];
        for(vector<int>::iterator it = stacje[j].begin(); it != stacje[j].end(); ++it){
          suma += dpm.znajdz_wartosc(*it);
          if (suma >= INF)
            break;
        }
        if (suma >= pot[j]){
          przed[j] = nrp;
          panstwa[nrp].push_back(j);
          // można usunąć państwo z listy tak, nie będzie więcej sprawdzane
          tak[l] = tak.back();
          tak.pop_back();
          l--;
        }
        else
          sumy[j] = suma;
      }
    }
  }

  for (int l = 0, nrp = (z-1)/sqrtz; l < (int) tak.size(); l++) 
  {
    int suma = 0;
    int j = tak[l];
    for(vector<int>::iterator it = stacje[j].begin(); it != stacje[j].end(); ++it){
      suma += dpm.znajdz_wartosc(*it);
      if (suma >= INF)
        break;
    }
    if (suma >= pot[j]){
      przed[j] = nrp; 
      panstwa[nrp].push_back(j);
      // można by usunąć, ale i tak już o liście tak zapominamy.
    }
  }

  // Druga symulacja - wyznaczanie dokładnych odpowiedzi
  vector<int>* zestaw = &panstwa[0];
  for(int i = 0; i < z; i++){
    if (i%sqrtz == 0){
      zestaw = &panstwa[i/sqrtz]; 
    }
    for (int j = 0; j < (int)zestaw->size(); j++){
      int a = (*zestaw)[j], wp = wielkosc_przeciecia(zap[i], stacje[a]);
      if (wp >= (pot[a]-sumy[a]+zap[i].a-1) / zap[i].a){
        odp[a] = i;
        // Więcej nie trzeba przetwarzać a-tego państwa.
        (*zestaw)[j] = zestaw->back();
        zestaw->pop_back();
        j--;
      }
      else
        sumy[a] += wp * zap[i].a; 
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

// Definicje funkcji pomocniczych {{{

int wielkosc_przeciecia2(int l, int r, const vector<int> & stacje){
  if (stacje.empty() || r < stacje.front() || stacje.back() < l)
    return 0;
  vector<int>::const_iterator p, k;
  if (l < stacje.front())
    p = stacje.begin();
  else
    p = lower_bound(stacje.begin(), stacje.end(), l);
  if (r > stacje.back()){
    k = stacje.end();
  }
  else{
    k = lower_bound(stacje.begin(), stacje.end(), r+1);
  }
  return k-p;
}

int wielkosc_przeciecia(const Zapytanie & zap, const vector<int>& stacje){
  if (zap.l <= zap.r)
    return wielkosc_przeciecia2(zap.l, zap.r, stacje);
  else
    return wielkosc_przeciecia2(0, zap.r, stacje) + wielkosc_przeciecia2(zap.l, m-1, stacje);
  return 0;
}

/// }}}
