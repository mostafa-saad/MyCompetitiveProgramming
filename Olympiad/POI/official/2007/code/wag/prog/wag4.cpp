/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Waga Czworkowa (WAG)                                       *}
{*   Plik:    wag4.cpp                                                   *}
{*   Autor:   Adam Iwanicki                                              *}
{*   Opis:    Rozwiazanie optymalne, ale przegladajace liczbe od cyfr    *}
{*            najmniej znaczacych                                        *}
{*                                                                       *}
{*************************************************************************/
#include<cstdio>
#include<cstdlib>
#include<cstring>

int bignum[1000], bignumsize;
int czworkowe[8000], czworkowesize;
int tab[4], tmp[4]; // Nmozliwosci, Nliczba, Dmozliwosci, Dliczba
char liczba[1100];

int reszta4()
{
  int reszta = 0, pom;
  for(int i=bignumsize-1; i>=0; --i) {
    pom = reszta*100000+bignum[i];
    bignum[i] = pom >> 2;
    reszta = pom & 3;
  }
  while( bignumsize >0 && 0 == bignum[bignumsize-1] ) --bignumsize;
  return reszta;
}

int main()
{
  fgets(liczba, sizeof(liczba), stdin);
  int rozm = strlen(liczba)-1;

  char* pom = liczba + rozm;
  while( true ) {
    pom[0] = '\0';
    pom -= 5;
    if( pom < liczba ) pom = liczba;
    bignum[bignumsize++] = atoi(pom);
    if( pom == liczba ) break;
  }

  while( bignumsize > 1 || bignum[0] ) {
    czworkowe[czworkowesize++] = reszta4();
  }

  tab[0]=tab[2]=1;
  tab[3]=5;
  for(int i=0; i<czworkowesize; ++i) {
    tmp[0] = tab[0];
    tmp[2] = tab[0];
    tmp[1] = tab[1] + czworkowe[i];
    tmp[3] = tab[1] + 4 - czworkowe[i] + 1;

    if( tab[3] + czworkowe[i] < tmp[1] ) {
      tmp[1] = tab[3] + czworkowe[i];
      tmp[0] = tab[2];
    } else if ( tab[3] + czworkowe[i] == tmp[1] ){
      tmp[0] += tab[2];
    }

    if( tab[3] + 4-czworkowe[i]-1 < tmp[3] ) {
      tmp[3] = tab[3]+4-czworkowe[i]-1;
      tmp[2] = tab[2];
    } else if ( tab[3] + 4 - czworkowe[i]-1 == tmp[3] ) {
      tmp[2] += tab[2];
    }

    for(int j=0; j<4; ++j) {
      tab[j] = tmp[j] % 1000000000;
    }
  }

  int res=0;
  if( tab[1] == tab[3] ) {
    res = (tab[0]+tab[2])%1000000000;
  } else if (tab[1] < tab[3] ) {
    res = tab[0];
  } else {
    res = tab[2];
  }
  printf("%d\n", res);

  return 0;
}

