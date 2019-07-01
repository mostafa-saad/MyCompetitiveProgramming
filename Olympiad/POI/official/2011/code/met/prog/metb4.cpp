/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Meteory                                          *
 *   Autor:             Blazej Osinski                                   *
 *   Zlozonosc czasowa: O(k*lg(m) + n*OT*lg(m) + SPR*k*lg(m))            *
 *                      (OT - wielkość sprawdzanego otoczenia)           *
 *   Opis:              Rozwiazanie bledne: dla czesci panstw            *
 *                      (losowo wybranych) dokladne obliczenie           *
 *                      wynikow, a dla pozostalych statyczne odgadniecie *
 *                      odpowiedzi, nastepnie silowe sprawdzenie         *
 *                      bliskich momentow                                *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<vector>
#include<algorithm>
#include<list>
#include<cmath>
#include<cassert>
using namespace std;

int __abc;
#define scanf __abc=scanf

const int N = 300007;

// Promień otocznia momentów, które będą sprawdzane.
const int OT = 500;

// Liczba państwa sprawdzanych dokładnie.
const int SPR = 100; 

struct Zapytanie
{
  int l, r, a;
} zap[N];

int wielkosc_przeciecia(const Zapytanie & zap, const vector<int>& stacje);

static const int INF = 1000000000;

//*****  Statyczne drzewo przedziałowe  ***** {{{

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
// Para (a,b) oznacza, że b-te państwo potrzebuje opadu 
// o średniej wartości a na swoich stacjach
pair<int, int> srednie[N], wielkosci[N]; 
// Stacje posiadane przez konkretne panstwa.
vector<int> stacje[N]; 
int odp[N];
// Przewidywany moment, w którym państwa powinny się nasycić.
int moment[N];
int sumy[N];
bool dokl[N];
// Państwa, które kónczą swój limit w odpowiednim przedziale.
vector<int> panstwa[N]; 

// Średnio opad część całkowita i reszta.
long long soc, sor;

int main()
{
  // Wczytywanie danych. 
  scanf("%d %d", &n, &m);
  for(int i = 0; i < m; i++){
    scanf("%d", &z);
    z--;
    stacje[z].push_back(i);
  }
  int pocz = 0;
  for(int i = 0; i < n; i++){
    scanf("%d", &pot[i]);
    int ss = stacje[i].size();

    if (ss > 0)
      srednie[i] = make_pair((pot[i] + ss) / ss, i); 
    else{
      srednie[i] = make_pair(-1, i); 
      pocz++;
    }

    wielkosci[i] = make_pair(ss, i);
  }

 
  sort(srednie, srednie + n);
  int wsk = pocz; 

  // Wczytywanie zapytań i obliczenie przewidywanych czasów nasycenia państw.
  scanf("%d", &z);
  for(int i = 0; i < z; i++){
    int l, r, dl;
    scanf("%d %d %d", &l, &r, &zap[i].a);
    if (l <= r)
      dl = r-l+1;
    else
      dl = r + m-l+1; 
    zap[i].l = l-1;
    zap[i].r = r-1;
    sor += (long long) zap[i].a  * (long long) dl;
    soc += sor / m;
    sor %= m;
    while (wsk < n && srednie[wsk].first <= soc){
      moment[srednie[wsk].second] = i;
      wsk ++;
    }
  }

  while (wsk < n){
    moment[srednie[wsk].second] = z-1;
    wsk ++;
  }

  for(int i = 0; i < n; i++){
    odp[i] = -1;
  }

  // Obliczenie dokladnych odpowiedzi dla części państw.
  random_shuffle(wielkosci, wielkosci + n);
  for (int j = 0; j < n && j < SPR; j++) {
    int nr = wielkosci[j].second, psuma = pot[nr];
    dokl[nr] = true;
    for(int i = 0; i < z; i++){
       int wp = wielkosc_przeciecia(zap[i], stacje[nr]);
       if (wp >= (psuma + zap[i].a-1) / zap[i].a){
         odp[nr] = i;
         // Skończyliśmy z aktualnym państwem.
         break;
       }
       else {
         psuma -= wp * zap[i].a;
       }
    }   
  }

  wsk = pocz;

  // Symulacja - wyznaczanie dokładnych odpowiedzi,
  // o ile są oddalone od przewidzianych o mniej niż OT.
  Drzewo dpm(m);
  dpm.czysc();
  list<int> sprawdzane;
  for(int i = 0; i < z; i++){
    while (wsk < n && i >= moment[srednie[wsk].second] - OT){
      int suma = 0, a = srednie[wsk].second;
      if(!dokl[a]){
        sprawdzane.push_back(a);
        for(vector<int>::iterator it = stacje[a].begin(); it != stacje[a].end(); ++it){
          suma += dpm.znajdz_wartosc(*it);
          if (suma >= INF)
            break;
        }
        sumy[a] = suma;
      }
      wsk ++;
    }
    while (!sprawdzane.empty() && i >= moment[sprawdzane.front()] + OT){
      odp[sprawdzane.front()] = i; // Strzał - pewnie zła odpowiedź.
      sprawdzane.pop_front();
    }
    if (zap[i].l <= zap[i].r){
      dpm.dodaj_przedzial(zap[i].l, zap[i].r, zap[i].a); 
    }
    else{
      dpm.dodaj_przedzial(zap[i].l, m-1, zap[i].a); 
      dpm.dodaj_przedzial(0, zap[i].r, zap[i].a); 
    }
    for (list<int>::iterator it = sprawdzane.begin(); it != sprawdzane.end();){
      int wp = wielkosc_przeciecia(zap[i], stacje[*it]);
      if (wp >= (pot[*it] - sumy[*it] + zap[i].a-1) / zap[i].a){
        odp[*it] = i;
        // Więcej nie trzeba przetwarzać aktualnego państwa.
        it = sprawdzane.erase(it);
      }
      else {
        sumy[*it] += wp * zap[i].a;
        ++it;
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
