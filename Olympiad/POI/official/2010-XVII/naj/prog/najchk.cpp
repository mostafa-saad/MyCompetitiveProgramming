/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Najdzielniejszy dzielnik (NAJ)                            *
 *   Plik:     najchk.cpp                                                *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Weryfikator wyjsc.                                        *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;


inline void error(const char *st)
{
  puts("WRONG");
  puts(st);
  exit(1);
}

#define MX 10000

int main(int argc, char **argv)
{
  if (argc != 4)
    error("Wywolanie: ./program in out wzo");
  FILE *in = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "r");
  FILE *wzo = fopen(argv[3], "r");

  /* Odczyt */
  char k1[MX + 2], D1[MX + 2], k2[MX + 2], D2[MX + 2];
  fscanf(wzo, "%s%s", k1, D1);
  fgets(k2, MX, out);
  fgets(D2, MX, out);
  fclose(in); fclose(out); fclose(wzo);

  /* Koncowe obcinanie k2. */
  int l = strlen(k2);
  while (l > 0 && (k2[l - 1] == ' ' || k2[l - 1] == '\n'))
  {
    k2[l - 1] = '\0';
    l--;
  }

  /* Koncowe obcinanie D2. */
  l = strlen(D2);
  while (l > 0 && (D2[l - 1] == ' ' || D2[l - 1] == '\n'))
  {
    D2[l - 1] = '\0';
    l--;
  }

  /* Wyznaczanie punktacji. */
  int pkt = 0;
  if (!strcmp(k1, k2))
    pkt = 50;
  if (pkt == 50 && !strcmp(D1, D2))
    pkt = 100;

  /* Wypisywanie komunikatu. */
  if (pkt == 0)
  {
    puts("WRONG\nKrotnosc k niepoprawna");
  } else
  {
    puts("OK");
    if (pkt == 50)
      puts("Krotnosc k poprawna, liczba D niepoprawna");
    else
      puts("Krotnosc k poprawna, liczba D poprawna");
    printf("%d\n", pkt);
  }
  return 0;
}
