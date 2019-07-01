/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Studnia                                          *
 *   Autor:             Igor Adamski                                     *
 *   Opis:              Program sprawdzajacy wyjscia                     *
 *                                                                       *
 *************************************************************************/

#include<cstdio>

#include "oi.h"
using namespace std;

const int MAXN = 1000000; // 10^6
const long long MAXM = 1000000000000000000LL; // 10^18
const int MAXX = 1000000000; // 10^9

void wrong(const char* msg, int line=0, int position=0) {
  printf("WRONG\n");
  printf("%s\n", msg);
  exit(1);
}

int main(int argc, char *argv[]) {
  oi::Scanner input(argv[1], wrong, oi::PL);
  oi::Scanner output(argv[2], wrong, oi::PL);
  oi::Scanner popr_output(argv[3], wrong, oi::PL);
  int x[MAXN+1];
  int n = input.readInt(1, MAXN);
  input.readSpace();
  long long m = input.readLL(1, MAXM);
  input.readEoln();
  for(int i=1;i<=n;++i)
  {
    if(i != 1)
      input.readSpace();
    x[i] = input.readInt(1, MAXX);
  }
  popr_output.skipWhitespaces();
  popr_output.readInt();
  popr_output.skipWhitespaces();
  int popr_z = popr_output.readInt(0, MAXX);

  output.skipWhitespaces();
  int miejsce = output.readInt(1, MAXN);
  output.skipWhitespaces();
  int z = output.readInt();
  output.skipWhitespaces();
  output.readEof();

  if(z != popr_z) {
    printf("WRONG\n");
    printf("Oczekiwano z=%d, a wczytano %d\n", popr_z, z);
    exit(1);
  }

  long long koszt = 0;
  for(int i=1;i<=n-1;++i)
  {
    koszt += max(0, x[i+1]-x[i]-z);
    x[i+1] = min(x[i+1], x[i]+z);
  }
  for(int i=n;i>=2;--i)
  {
    koszt += max(0, x[i-1]-x[i]-z);
    x[i-1] = min(x[i-1], x[i]+z);
  }
  for(int i=1;i<=n;++i)
    koszt += max(0LL, (long long)x[i]-(long long)z*abs(i-miejsce));
  if(koszt > m) {
    printf("WRONG\n");
    printf("Dokopanie do wody w miejscu %d wymaga zbyt wielu ruchow", miejsce);
    exit(1);
  }
  printf("OK\n");
  return 0;
}
