/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Meteory                                          *
 *   Autor:             Blazej Osinski                                   *
 *   Zlozonosc czasowa: O((m+k)*lg(m)*lg(k))                             *
 *   Opis:              Rozwiazanie alternatywne                         *
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

static const int INF = 1000000000;

//*****  Drzewo potęgowe  ***** {{{

struct DrzewoPotegowe {
    static const int WD = 524377;
    long long s[WD];
    int wd;
    DrzewoPotegowe(int n);
    void czysc();
    void dodaj_wartosc(int a, int wart);
    long long suma(int w);
};

DrzewoPotegowe::DrzewoPotegowe(int n){
  wd = 1;
  while ((1<<wd) < n)
    wd++;
  czysc();
}

void DrzewoPotegowe::czysc(){
  for(int i = 1; i <= (1<<wd); i++)
    s[i] = 0;
}

long long DrzewoPotegowe::suma(int w)
{
  w++;
  if (w == 0)
    return 0LL;
  long long suma = 0LL;
  int p = 1;
  while (w > 0) {
    if (p & w){
      suma += s[w];
      w ^= p;
    }
    p <<= 1;
  }
  return suma;
}

void DrzewoPotegowe::dodaj_wartosc(int a, int wart){
  a++;
  for (int i = 0, p = 1; i <= wd; i++, p <<= 1){
    if (a & p){
      s[a] += wart;
      a += p;
    }
  }
}

//******************************************** }}}

int n, m, pot[N], wl[N], z, srodki[N];
pair<int, int> przed[N];
vector<pair<int, int> > grupy[N];
long long suma[N];

int main()
{
  // Wczytywanie danych. 
  scanf("%d %d", &n, &m);
  for(int i = 0; i < m; i++){
    scanf("%d", &z);
    z--;
    wl[i] = z;
  }
  for(int i = 0; i < n; i++)
    scanf("%d", &pot[i]);
  
  // Wczytywanie zapytań.
  scanf("%d", &z);
  for(int i = 0; i < z; i++){
    int l, r, a;
    scanf("%d %d %d", &l, &r, &a);
    l--;
    r--;
    if (l <= r){
      grupy[l].push_back(make_pair(i, a));
      grupy[r+1].push_back(make_pair(i, -a));
    }
    else {
      grupy[0].push_back(make_pair(i, a));
      grupy[r+1].push_back(make_pair(i, -a));
      grupy[l].push_back(make_pair(i, a));
      grupy[m].push_back(make_pair(i, -a));
    }
  }

  // Wspólne wyszukiwanie binarne
  DrzewoPotegowe dpot(z);
  for(int i = 0; i < n; i++)
    przed[i] = make_pair(0, z);
  
  for(;;){
    int l = 0;
    for (int i = 0; i < n; i++){
      suma[i] = 0LL;
      if (przed[i].first != przed[i].second){
        srodki[i] = (przed[i].first + przed[i].second)/2;
        l++;
      }
      else
        srodki[i] = -1;
    } 
    if (l == 0)
      break;

    // Zamiast symulacji przegladamy wydarzenia dla kolejnych stacji.
    dpot.czysc(); 
    for (int i = 0; i < m; i++){
      for (vector<pair<int, int> >::iterator it = grupy[i].begin(); it != grupy[i].end(); ++it){
        dpot.dodaj_wartosc(it->first, it->second);
      }
      if (srodki[wl[i]] != -1)
      {
        // Właściciel tej stacji nie jest jeszcze rozpatrzony.
        suma[wl[i]] += dpot.suma(srodki[wl[i]]);
        if(suma[wl[i]] > INF)
          suma[wl[i]] = INF;
      }
    }
    for (int i = 0; i < n; i++){
      if (przed[i].first != przed[i].second){
        if ((long long)pot[i] <= suma[i]) // i-te państwo dostało co najmniej tyle co potrzebowało. 
          przed[i].second = srodki[i];
        else
          przed[i].first = srodki[i]+1;
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
