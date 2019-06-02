/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Tetris attack (TET)                                        *}
{*   Plik:    tetchk.cpp                                                 *}
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
char buf[1024];
int line = 0;

void error(const char *str, int line2 = line)
{
  printf("WRONG\nLinia %d: %s\n", line2, str);
  exit(0);
}

void read_ints(int n)
{
  int len = 0;
  for (;;) // wczytuj a¿ dostaniesz niepust± liniê
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
int tab[2*50000];

void znikaj(int skad)
{
  --N;
  FOR(a, skad, 2*N-1)
    tab[a] = tab[a+2];
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
  REP(a, 2*N)
  {
    fscanf(fin, "%d", &tab[a]);
    --tab[a];
  }
  int opt;
  fscanf(foutok, "%d", &opt);
  int ile;
  read_ints(1); 
  sscanf(buf, "%d", &ile);
  if (ile!=opt)
  {
    if (ile<opt)
      sprintf(buf, "Nie da siê wygraæ w %d ruchach, potrzeba %d.", ile, opt);
    else
      sprintf(buf, "Rozwi±zanie nieoptymalne: wystarczy %d ruchów zamiast %d.", opt, ile);
    error(buf);
  }
  REP(a, ile)
  {
    read_ints(1);
    int zam;
    sscanf(buf, "%d", &zam);
    if (zam<1 || zam>=2*N)
    {
      sprintf(buf, "Na stosie nie ma ju¿ elementu %d.\n", zam==2*N ? zam+1 : zam);
      error(buf);
    }
    --zam;
    swap(tab[zam], tab[zam+1]);
    if (zam+2<2*N && tab[zam+1]==tab[zam+2])
      znikaj(zam+1);
    if (zam+1<2*N && tab[zam]==tab[zam+1])
      znikaj(zam);
    while (zam>0 && zam<2*N && tab[zam-1]==tab[zam])
      znikaj(--zam);
  }
  if (N)
    error("Strategia nie usuwa wszystkich elementów.\n");
  end_of_file();
  printf("OK\n");
}
