/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Meteory                                          *
 *   Autor:             Blazej Osinski                                   *
 *   Zlozonosc czasowa: O((n*lg(n)+(m+k)*lg(m))*lg(k))                   *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************/

#include<cstdio>
#include<vector>
#include<algorithm>
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
// Stacje posiadane przez konkretne panstwa.
vector<int> stacje[N]; 
pair<int, int> przed[N], srodki[N];

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
  
  // Wspólne wyszukiwanie binarne
  Drzewo dpm(m);
  for(int i = 0; i < n; i++)
    przed[i] = make_pair(0, z);
  
  for(;;){
    int l = 0;
    for (int i = 0; i < n; i++)
      if (przed[i].first != przed[i].second){
        srodki[l] = make_pair((przed[i].first + przed[i].second)/2, i);
        l++;
      }
    if (l == 0)
      break;
    sort(srodki, srodki + l);
    int wsk = 0;
    // Symulacja
    dpm.czysc();
    // to czyszczenie by można było pominąć, sprawdzić ile przyśpieszy
    // (chyba nie w żaden łatwy sposób, coś mi się wcześniej musiało pomieszać)
    for(int i = 0; i < z && wsk < l; i++){
      if (zap[i].l <= zap[i].r){
        dpm.dodaj_przedzial(zap[i].l, zap[i].r, zap[i].a); 
      }
      else{
        dpm.dodaj_przedzial(zap[i].l, m-1, zap[i].a); 
        dpm.dodaj_przedzial(0, zap[i].r, zap[i].a); 
      }
      while(wsk < l && srodki[wsk].first == i){ // jak ktos tu napisze if to trzeba go wyciac
        int suma = 0, nr = srodki[wsk].second;
        for(vector<int>::iterator it = stacje[nr].begin(); it != stacje[nr].end(); ++it){
          suma += dpm.znajdz_wartosc(*it);
          if (suma >= INF)
            break;
        }
        if (pot[nr] <= suma) // Liczba meteorytów jest nie mniejsza niż potrzebna państwu nr.
          przed[nr].second = i;
        else
          przed[nr].first = i+1;
        wsk++;
      }
    }
  }
  for(int i = 0; i < n; i++){
    if(przed[i].first < z)
      printf("%d\n", przed[i].first+1);
    else
      printf("NIE\n");
  }
  return 0;
}
