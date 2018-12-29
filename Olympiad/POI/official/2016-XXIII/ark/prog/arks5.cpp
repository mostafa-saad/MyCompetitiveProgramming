/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Arkanoid                                           *
 *   Autor programu:       Jakub Radoszewski                                  *
 *   Zlozonosc czasowa:    O((m+n+k) log (m+n+k))                             *
 *   Opis:                 sortuje i wstawia mapy, gdzie sie da               *
 *****************************************************************************/

#include<cstdio>
#include<cctype>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<string>
#include<list>
#include<deque>
#include<map>
#include<set>
#include<queue>
#include<stack>
#include<utility>
#include<sstream>
#include<cstring>
#include<numeric>
#include<cassert>
using namespace std;

#define FOR(I,A,B) for(int I=(A);I<=(B);I++)
#define FORD(I,A,B) for(int I=(A);I>=(B);I--)
#define REP(I,N) for(int I=0;I<(N);I++)
#define ALL(X) (X).begin(),(X).end()
#define PB push_back
#define MP make_pair
#define FI first
#define SE second
#define X first
#define Y second
#define INFTY 100000000
#define VAR(V,init) __typeof(init) V=(init)
#define FORE(I,C) for(VAR(I,(C).begin());I!=(C).end();I++)
#define SIZE(x) ((int)(x).size())

typedef vector<int> VI;
typedef pair<int,int> PII;
typedef long long ll;
typedef vector<string> VS;
typedef vector<PII> VPII;

const int MAX_K=1000000;

const int LEWO_DOL = 0;
const int PRAWO_GORA = 3;
const int PRAWO_DOL = 1;
const int LEWO_GORA = 2;

int n,m,k;

VPII pola_klocka[MAX_K+1];
map<PII,VI> numer_klocka; // moga byc dwa numery
set<PII> sciana;

VPII cztery_pola(PII klocek)
{
  vector<PII> t;
  int x=klocek.FI,y=klocek.SE;
  t.PB(MP(2*x+1,2*y));
  t.PB(MP(2*x+1,2*y+2));
  t.PB(MP(2*x,2*y+1));
  t.PB(MP(2*x+2,2*y+1));
  return t;
}

VPII wierzcholki;

void tworz_wierzcholki()
{
  scanf("%d%d%d",&m,&n,&k);
  FOR(i,1,2*n) if (i%2) { wierzcholki.PB(MP(0,i)); wierzcholki.PB(MP(2*m,i)); }
  FOR(i,1,2*m) if (i%2) { wierzcholki.PB(MP(i,0)); wierzcholki.PB(MP(i,2*n)); }
  REP(i,SIZE(wierzcholki)) sciana.insert(wierzcholki[i]);
  REP(i,k)
  {
    int x,y;
    scanf("%d%d",&x,&y);
    --x; --y;
    VPII pola=cztery_pola(MP(x,y));
    pola_klocka[i+1]=pola;
    REP(j,4) { wierzcholki.PB(pola[j]); numer_klocka[pola[j]].PB(i+1); }
  }
  sort(ALL(wierzcholki));
  wierzcholki.erase(unique(ALL(wierzcholki)),wierzcholki.end());
}

struct t_krawedz
{
  PII p;
  ll waga;
  int kier;
};

t_krawedz MK(PII p,ll waga,int kier)
{
  t_krawedz k;
  k.p=p; k.waga=waga; k.kier=kier;
  return k;
}

typedef vector<t_krawedz> VKraw;

map<PII,VKraw> krawedzie; // max 4 krawedzie na wierzcholek

int twardy_kierunek;
int id_prostej(PII a)
{
  return a.Y+twardy_kierunek*a.X;
}

bool por(PII a,PII b)
{
  return MP(id_prostej(a),a.Y) < MP(id_prostej(b),b.Y);
}

void tworz_krawedzie(int kierunek,int numer_kierunku1,int numer_kierunku2)
{
  twardy_kierunek=kierunek;
  sort(ALL(wierzcholki),por);
  FOR(i,1,SIZE(wierzcholki)-1)
  {
    const PII &p=wierzcholki[i], &pop=wierzcholki[i-1];
    if (id_prostej(p) == id_prostej(pop))
    {
      krawedzie[p][numer_kierunku1]=MK(pop,abs(p.X-pop.X),numer_kierunku2);
      krawedzie[pop][numer_kierunku2]=MK(p,abs(p.X-pop.X),numer_kierunku1);
    }
  }
}

void kompresuj_sciana_if(PII p)
{
  // wyznaczam konce i dlugosc krawedzi
  PII pop,nast;
  ll waga=0;
  int kier1,kier2;
  int i=0;
  while (krawedzie[p][i].p==MP(0,0)) ++i;
  pop=krawedzie[p][i].p;
  waga+=krawedzie[p][i].waga;
  kier1=krawedzie[p][i].kier;
  ++i;
  while (krawedzie[p][i].p==MP(0,0)) ++i;
  nast=krawedzie[p][i].p;
  waga+=krawedzie[p][i].waga;
  kier2=krawedzie[p][i].kier;

  if (numer_klocka.find(pop)!=numer_klocka.end() && numer_klocka.find(nast)!=numer_klocka.end())
    return; // unika nadgorliwej kompresji

  //printf("kompresuje: (%d %d) -- (%d %d) -- (%d %d)\n",pop.X,pop.Y,p.X,p.Y,nast.X,nast.Y);
  
  // tworze krawedz
  krawedzie[pop][kier1]=MK(nast,waga,kier2);
  krawedzie[nast][kier2]=MK(pop,waga,kier1);
  sciana.erase(p);
}

void kompresuj_co_sie_da(VPII t,PII pileczka)
{
  //return; // NIE KOMPRESUJ
  REP(i,SIZE(t))
  {
    PII p=t[i];
    if (sciana.find(p)!=sciana.end() && numer_klocka.find(p)==numer_klocka.end() && p!=pileczka)
    {
      // jest na scianie, nie jest w klocku i nie ma tam pileczki
      kompresuj_sciana_if(p);
    }
  }
}

void tworz_krawedzie()
{
  REP(i,SIZE(wierzcholki)) krawedzie[wierzcholki[i]].resize(4);
  tworz_krawedzie(-1,LEWO_DOL,PRAWO_GORA);
  tworz_krawedzie(1,PRAWO_DOL,LEWO_GORA);
  kompresuj_co_sie_da(wierzcholki, MP(m,0));
}

const int POLE1[4]={0,0,3,2};
const int POLE2[4]={3,2,1,1};
const int KIER1[4]={LEWO_DOL,PRAWO_DOL,PRAWO_DOL,LEWO_DOL};
const int KIER2[4]={PRAWO_GORA,LEWO_GORA,LEWO_GORA,PRAWO_GORA};

void rozklockuj(int numer,PII pileczka)
{
  // usuwamy numery klocka z pol
  REP(i,4)
  {
    PII p=pola_klocka[numer][i];
    int j=0;
    while (numer_klocka[p][j]!=numer) ++j;
    assert(j<SIZE(numer_klocka[p]));
    numer_klocka[p].erase(numer_klocka[p].begin()+j);
    if (numer_klocka[p].empty()) numer_klocka.erase(p);
  }

  // poprawiamy krawedzie w grafie
  VPII potencjalne_sciany;
  REP(z,4)
  {
    PII pole1=pola_klocka[numer][POLE1[z]], pole2=pola_klocka[numer][POLE2[z]];
    bool czy_nieruchomy1=false, czy_nieruchomy2=false;
    if (sciana.find(pole1)!=sciana.end() || numer_klocka.find(pole1)!=numer_klocka.end()) czy_nieruchomy1=true;
    if (sciana.find(pole2)!=sciana.end() || numer_klocka.find(pole2)!=numer_klocka.end()) czy_nieruchomy2=true;
    PII p1,p2;
    ll waga=1;
    int kier1,kier2;
    if (czy_nieruchomy1)
    {
      p1=pole1;
      kier1=KIER2[z];
    }
    else
    {
      p1=krawedzie[pole1][KIER1[z]].p;
      waga+=krawedzie[pole1][KIER1[z]].waga;
      kier1=krawedzie[pole1][KIER1[z]].kier;
    }
    if (czy_nieruchomy2)
    {
      p2=pole2;
      kier2=KIER1[z];
    }
    else
    {
      p2=krawedzie[pole2][KIER2[z]].p;
      waga+=krawedzie[pole2][KIER2[z]].waga;
      kier2=krawedzie[pole2][KIER2[z]].kier;
    }
    //printf("rozklockuj (%d %d) -- (%d %d)\n",p1.X,p1.Y,p2.X,p2.Y);
    krawedzie[p1][kier1]=MK(p2,waga,kier2);
    krawedzie[p2][kier2]=MK(p1,waga,kier1);
    potencjalne_sciany.PB(pole1); potencjalne_sciany.PB(pole2); // mozna efektywniej
    potencjalne_sciany.PB(p1); potencjalne_sciany.PB(p2); 
  }

  // proba kompresji scian
  sort(ALL(potencjalne_sciany));
  potencjalne_sciany.erase(unique(ALL(potencjalne_sciany)),potencjalne_sciany.end());
  kompresuj_co_sie_da(potencjalne_sciany,pileczka);
}

bool jest_elem(int elem,VI lista)
{
  REP(i,SIZE(lista)) if (lista[i]==elem) return true;
  return false;
}

ll symulacja()
{
  ll wynik=0;
  PII p=MP(m,0);
  int kier=LEWO_GORA;

  while (1)
  {
    //printf("%d %d\n",p.X,p.Y);
    if (numer_klocka.find(p)!=numer_klocka.end() && k==1) break;
    wynik+=krawedzie[p][kier].waga;

    // wyznaczanie nowego klocka
    PII nast=krawedzie[p][kier].p;
    int moj_kier=krawedzie[p][kier].kier;
    int nowy_kier=0;
    if (numer_klocka.find(nast)!=numer_klocka.end())
    {
      int nr=numer_klocka[nast][0];
      while (nowy_kier==moj_kier ||
          (numer_klocka.find(krawedzie[nast][nowy_kier].p)!=numer_klocka.end() &&
          jest_elem(nr,numer_klocka[krawedzie[nast][nowy_kier].p])))
        ++nowy_kier;
    } else
    {
      while (nowy_kier==moj_kier || krawedzie[nast][nowy_kier].p==MP(0,0)) ++nowy_kier;
    }

    // rozklockowanie
    if (numer_klocka.find(p)!=numer_klocka.end())
    {
      --k;
      assert(SIZE(numer_klocka[p])==1);
      rozklockuj(numer_klocka[p][0], nast);
    }

    p=nast;
    kier=nowy_kier;
  }
  return wynik;
}

int main()
{
  tworz_wierzcholki();
  tworz_krawedzie();
  printf("%lld\n",symulacja());
  return 0;
}
