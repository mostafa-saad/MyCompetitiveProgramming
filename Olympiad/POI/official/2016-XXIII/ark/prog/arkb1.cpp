/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Arkanoid                                           *
 *   Autor programu:       Jakub Radoszewski                                  *
 *   Opis:                 Rozwiazanie bledne                                 *
 *                         wzorcowka bez long longow                          *
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
typedef int ll; // lol
typedef vector<string> VS;
typedef vector<PII> VPII;
typedef vector<pair<PII,int> > VPPIII;

const int LEWO_DOL = 0;
const int PRAWO_GORA = 3;
const int PRAWO_DOL = 1;
const int LEWO_GORA = 2;

int n,m,k;

struct t_wierzcholek
{
  PII p;
  int nr;
  bool sciana;
  int nr_klocka[2];
};

inline t_wierzcholek MW(int x,int y)
{
  t_wierzcholek w;
  w.p=MP(x,y);
  w.nr=-1;
  w.sciana=false;
  w.nr_klocka[0]=w.nr_klocka[1]=-1;
  return w;
}

vector<t_wierzcholek> wierzcholki;
int start;
vector<VI> pola_klocka;

VPII cztery_pola(PII klocek)
{
  vector<PII> t;
  int x=klocek.X,y=klocek.Y;
  t.PB(MP(2*x+1,2*y));
  t.PB(MP(2*x+1,2*y+2));
  t.PB(MP(2*x,2*y+1));
  t.PB(MP(2*x+2,2*y+1));
  return t;
}

int twardy_kierunek=-1;
inline int id_prostej(PII a)
{
  return a.Y+twardy_kierunek*a.X;
}

bool por(t_wierzcholek a,t_wierzcholek b)
{
  return MP(id_prostej(a.p),a.p.Y) < MP(id_prostej(b.p),b.p.Y);
}

bool por_lex(t_wierzcholek a,t_wierzcholek b)
{
  return a.p<b.p;
}

bool por_nr(t_wierzcholek a,t_wierzcholek b)
{
  return a.nr<b.nr;
}

bool por_xy(int p1,int p2)
{
  return wierzcholki[p1].p < wierzcholki[p2].p;
}

void tworz_wierzcholki()
{
  scanf("%d%d%d",&m,&n,&k);
  FOR(i,1,2*n) if (i%2) { wierzcholki.PB(MW(0,i)); wierzcholki.PB(MW(2*m,i)); }
  FOR(i,1,2*m) if (i%2) { wierzcholki.PB(MW(i,0)); wierzcholki.PB(MW(i,2*n)); }
  REP(i,SIZE(wierzcholki)) wierzcholki[i].sciana=true;
  REP(i,k)
  {
    int x,y;
    scanf("%d%d",&x,&y);
    --x; --y;
    VPII pola=cztery_pola(MP(x,y));
    REP(j,4)
    {
      wierzcholki.PB(MW(pola[j].X,pola[j].Y));
      int *tab=wierzcholki.back().nr_klocka;
      if (tab[0]==-1) tab[0]=i+1; else tab[1]=i+1;
    }
  }
  sort(ALL(wierzcholki),por_lex);
  int i=0;
  int nr=0;
  while (i<SIZE(wierzcholki))
  {
    int i0=i+1;
    while (i0<SIZE(wierzcholki) && wierzcholki[i0].p==wierzcholki[i].p)
    {
      if (wierzcholki[i0].sciana) wierzcholki[i].sciana=true;
      int a=0,b=0;
      if (wierzcholki[i].nr_klocka[0]==-1) a=0; else a=1;
      while (b<2 && wierzcholki[i0].nr_klocka[b]!=-1) wierzcholki[i].nr_klocka[a++]=wierzcholki[i0].nr_klocka[b++];
      ++i0;
    }
    wierzcholki[i].nr=nr++;
    i=i0;
  }
  sort(ALL(wierzcholki),por_nr);
  reverse(ALL(wierzcholki));
  while (wierzcholki.back().nr==-1) wierzcholki.pop_back();
  reverse(ALL(wierzcholki));
  pola_klocka.resize(k+1);
  FOR(i,1,k) pola_klocka.reserve(4);
  REP(i,SIZE(wierzcholki))
  {
    const int *t=wierzcholki[i].nr_klocka;
    REP(j,2) if (t[j]!=-1) pola_klocka[t[j]].PB(i);
  }
  FOR(i,1,k) sort(ALL(pola_klocka[i]),por_xy);
  REP(i,SIZE(wierzcholki))
    if (wierzcholki[i].p==MP(m,0))
      start=wierzcholki[i].nr;
}

struct t_krawedz
{
  int p;
  ll waga;
  int kier;
};

t_krawedz MK(int p,ll waga,int kier)
{
  t_krawedz k;
  k.p=p; k.waga=waga; k.kier=kier;
  return k;
}

typedef vector<t_krawedz> VKraw;

vector<VKraw> krawedzie; // max 4 krawedzie na wierzcholek

void tworz_krawedzie(int kierunek,int nr_kierunku1,int nr_kierunku2)
{
  twardy_kierunek=kierunek;
  sort(ALL(wierzcholki),por);
  FOR(i,1,SIZE(wierzcholki)-1)
  {
    const PII &p=wierzcholki[i].p, &pop=wierzcholki[i-1].p;
    if (id_prostej(p) == id_prostej(pop))
    {
      krawedzie[wierzcholki[i].nr][nr_kierunku1]=MK(wierzcholki[i-1].nr,abs(p.X-pop.X),nr_kierunku2);
      krawedzie[wierzcholki[i-1].nr][nr_kierunku2]=MK(wierzcholki[i].nr,abs(p.X-pop.X),nr_kierunku1);
    }
  }
}

void kompresuj_sciana_if(int p)
{
  // wyznaczam konce i dlugosc krawedzi
  int p1,p2;
  ll waga=0;
  int kier1,kier2;
  int i=0;
  while (krawedzie[p][i].p==-1) ++i;
  p1=krawedzie[p][i].p;
  waga+=krawedzie[p][i].waga;
  kier1=krawedzie[p][i].kier;
  ++i;
  while (krawedzie[p][i].p==-1) ++i;
  p2=krawedzie[p][i].p;
  waga+=krawedzie[p][i].waga;
  kier2=krawedzie[p][i].kier;

  if (wierzcholki[p1].nr_klocka[0]!=-1 && wierzcholki[p2].nr_klocka[0]!=-1)
    return; // unika nadgorliwej kompresji

  // tworze krawedz
  krawedzie[p1][kier1]=MK(p2,waga,kier2);
  krawedzie[p2][kier2]=MK(p1,waga,kier1);

  // usuwam wierzcholek ze sciany
  wierzcholki[p].sciana=false;
}

void kompresuj_co_sie_da(const VI &t,int pileczka)
{
  //return; // NIE KOMPRESUJ
  REP(i,SIZE(t))
    if (wierzcholki[t[i]].sciana && wierzcholki[t[i]].nr_klocka[0]==-1 && t[i]!=pileczka)
    {
      // jest na scianie, nie jest w klocku i nie ma tam pileczki
      kompresuj_sciana_if(t[i]);
    }
}

void tworz_krawedzie()
{
  krawedzie.resize(SIZE(wierzcholki));
  REP(i,SIZE(krawedzie)) krawedzie[i].resize(4,MK(-1,-1LL,-1));
  tworz_krawedzie(-1,LEWO_DOL,PRAWO_GORA);
  tworz_krawedzie(1,PRAWO_DOL,LEWO_GORA);
  sort(ALL(wierzcholki),por_nr);
  VI t;
  REP(i,SIZE(wierzcholki)) t.PB(i);
  kompresuj_co_sie_da(t,start);
}

void wypisz()
{
  REP(i,SIZE(wierzcholki))
  {
    printf("%d: (%d %d) %d [ ",wierzcholki[i].nr,wierzcholki[i].p.X,wierzcholki[i].p.Y,wierzcholki[i].sciana);
    REP(j,2) printf("%d ",wierzcholki[i].nr_klocka[j]);
    printf("]  kr: ");
    REP(j,SIZE(krawedzie[i])) printf("%d ",krawedzie[i][j].p);
    puts("");
  }
  printf("start: %d\n",start);
  FOR(i,1,k)
  {
    printf("pola klocka %d: ",i);
    REP(j,SIZE(pola_klocka[i])) printf("%d ",pola_klocka[i][j]);
    puts("");
  }
}


const int POLE1[4]={1,1,3,0};
const int POLE2[4]={3,0,2,2};
const int KIER1[4]={LEWO_DOL,PRAWO_DOL,PRAWO_DOL,LEWO_DOL};
const int KIER2[4]={PRAWO_GORA,LEWO_GORA,LEWO_GORA,PRAWO_GORA};

void rozklockuj(int kl,int pileczka)
{
  // usuwamy numery klocka z pol
  REP(i,4)
  {
    int p=pola_klocka[kl][i];
    int *t=wierzcholki[p].nr_klocka;
    if (t[0]==kl) { t[0]=t[1]; t[1]=-1; } else t[1]=-1;
  }

  // poprawiamy krawedzie w grafie
  VI potencjalne_sciany;
  REP(z,4)
  {
    int pole1=pola_klocka[kl][POLE1[z]], pole2=pola_klocka[kl][POLE2[z]];
    bool czy_nieruchomy1=false, czy_nieruchomy2=false;
    if (wierzcholki[pole1].sciana || wierzcholki[pole1].nr_klocka[0]!=-1) czy_nieruchomy1=true;
    if (wierzcholki[pole2].sciana || wierzcholki[pole2].nr_klocka[0]!=-1) czy_nieruchomy2=true;
    int p1,p2;
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
    krawedzie[p1][kier1]=MK(p2,waga,kier2);
    krawedzie[p2][kier2]=MK(p1,waga,kier1);
    potencjalne_sciany.PB(p1); potencjalne_sciany.PB(p2); 
  }

  // proba kompresji scian
  kompresuj_co_sie_da(potencjalne_sciany,pileczka);
}

inline bool jest_elem(int elem,const int *lista2)
{
  return lista2[0]==elem || lista2[1]==elem;
}

ll symulacja()
{
  ll wynik=0;
  int p=start;
  int kier=LEWO_GORA;

  ll kroki=0;
  while (1)
  {
    //printf("%d %d\n",wierzcholki[p].p.X,wierzcholki[p].p.Y);
    if (wierzcholki[p].nr_klocka[0]!=-1 && k==1) break;
    wynik+=krawedzie[p][kier].waga;

    // wyznaczanie nowego klocka
    int nast=krawedzie[p][kier].p;
    int moj_kier=krawedzie[p][kier].kier;
    int nowy_kier=0;
    int nr=wierzcholki[nast].nr_klocka[0];
    if (nr!=-1)
    {
      while (nowy_kier==moj_kier || jest_elem(nr,wierzcholki[krawedzie[nast][nowy_kier].p].nr_klocka))
        ++nowy_kier;
    } else
    {
      while (nowy_kier==moj_kier || krawedzie[nast][nowy_kier].p==-1) ++nowy_kier;
    }

    // rozklockowanie
    if (wierzcholki[p].nr_klocka[0]!=-1)
    {
      --k;
      assert(wierzcholki[p].nr_klocka[1]==-1);
      rozklockuj(wierzcholki[p].nr_klocka[0], nast);
    }

    p=nast;
    kier=nowy_kier;
    ++kroki;
  }
  //fprintf(stderr,"Liczba krokow symulacji: %lld  liczba wierzcholkow: %d\n",kroki,SIZE(wierzcholki));
  return wynik;
}

int main()
{
  tworz_wierzcholki();
  tworz_krawedzie();
  //wypisz();
  printf("%d\n",symulacja());
  return 0;
}
