/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Klocki (KLO)                                               *}
{*   Plik:    klochk.cpp                                                 *}
{*   Autor:   Pawel Parys                                                *}
{*   Opis:    Program weryfikujacy poprawnosc wyjscia wygenerowanego     *}
{*            przez program zawodnika, format:                           *}
{*            ./skachk.e in out_zawodnika out_wzorcowy                   *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define REP(a,n) for (int a=0; a<(n); ++a)
#define FOR(a,b,c) for (int a=(b); a<=(c); ++a)

using namespace std;

FILE *foutgr;
char buf[2000000];
int line = 0;

void error(const char *str, int line2 = line)
{
  printf("WRONG\nLinia %d: %s\n", line2, str);
  exit(0);
}

void read_ints(int n)
{
  if (!n) // ma byc pusta linia - tak jakby jej mialo nie byc
    return;
  int len = 0;
  for (;;) // wczytuj a¿ dostaniesz niepust± liniê (pomijaj±c puste)
  {
    for (;;) // wczytuj a¿ wczytasz ca³± liniê
    {
      if (len>=(int)sizeof(buf)-1) // koniec bufora
        error("Za d³uga linia.", line+1);
      char *ok = fgets(buf+len, sizeof(buf)-len, foutgr);
      if (!ok && !len)
        error("Za ma³o linii.", line+1);
      if (!ok) // koniec pliku = koniec linii
        break;
      for (int a = len; buf[a]; ++a) // pomin zbedne spacje
        if (buf[a]!=' ' || (buf[a]==' ' && len && buf[len-1]!=' '))
          buf[len++] = buf[a];
      if (len && buf[len-1]=='\n')
      { // koniec linii - usun znak konca i przerwij czytanie
        buf[--len] = 0;
        break;
      }
    }
    ++line;
    if (len)
      break;
  }
  while (len && buf[len-1]==' ')
    --len; // usun spacje z konca linii
  int dl = 0;
  REP(a, len)
  {
    if (!isdigit(buf[a]) && buf[a]!=' ')
      error("Nieprawid³owy znak.");
    if (isdigit(buf[a]))
    {
      if (!dl)
        --n;
      ++dl;
      if (dl>9 && (dl>10 || buf[a-9]!='1'))
        error("Liczba za du¿a.");
    }
    else
    {
      if (!n)
        error("¦mieci na koñcu linii.");
      dl = 0;
    }
  }
  if (n)
    error("Za ma³o liczb w linii.");
}

void end_of_file()
{
  ++line;
  for (;;) // wczytuj i pomijaj puste linie
  {
    char *ok = fgets(buf, sizeof(buf), foutgr);
    if (!ok) 
      break;
    int len = strlen(buf);
    REP(a, len)
      if (buf[a]!=' ' && buf[a]!='\n')
        error("¦mieci na koñcu pliku.");
    if (len && buf[len-1]=='\n')
    {
      ++line;
      buf[--len] = 0;
    }
  }
}

int N;
int tab[100000];   // oryginalna wieza
int usun[100000];  // czy usuwamy ten klocek

int licz() // ile klockow bedzie na swoich pozycjach
{
  int wynik = 0;
  int p = 1;
  REP(a, N)
    if (!usun[a] && tab[a]==p++)
      ++wynik;
  return wynik;
}

int main(int argc, char **argv)
{
  if (argc!=4)
  {
    fprintf(stderr, "Potrzebujê trzech argumentów!!!\n");
    return -1;
  }
  FILE *fin = fopen(argv[1], "r");
  foutgr = fopen(argv[2], "r");
  FILE *foutok = fopen(argv[3], "r");
  if (fin==NULL || foutgr==NULL || foutok==NULL)
  {
    fprintf(stderr, "Nie umiem otworzyæ plików!!!\n");
    return -2;
  }
  fscanf(fin, "%d", &N);
  REP(a, N)
  {
    fscanf(fin, "%d", &tab[a]);
    usun[a] = 0;
  }
  int ile_ok;
  fscanf(foutok, "%d", &ile_ok);
  REP(a, ile_ok)
  {
    int x;
    fscanf(foutok, "%d", &x);
    usun[x-1] = 1;
  }
  int opt = licz();
  REP(a, N)
    usun[a] = 0;
  int ile;
  read_ints(1); 
  sscanf(buf, "%d", &ile);
  read_ints(ile);
  int p = 0; // aktualna pozycja w buforze
  REP(a, ile)
  {
    int x, c;
    char b = 0;
    swap(buf[p+20], b); // super trick przyspieszajacy, inaczej sscanf wolno dziala
    sscanf(buf+p, "%d%n", &x, &c);
    swap(buf[p+20], b); 
    p += c;
    if (x<1 || x>N)
    {
      sprintf(buf, "Numer klocka %d spoza zakresu.", x);
      error(buf);
    }
    if (usun[x-1])
    {
      sprintf(buf, "Dwukrotna próba usuniêcia klocka numer %d.", x);
      error(buf);
    }
    usun[x-1] = 1;
  }
  int wyn = licz();
  if (wyn!=opt)
  {
    sprintf(buf, "Wynik %d nieoptymalny (mo¿e byæ %d).", wyn, opt);
    error(buf);
  }
  end_of_file();
  printf("OK\n");
}
