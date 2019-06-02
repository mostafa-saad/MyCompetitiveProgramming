/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PAL (Palindromy)                               *
 *   Plik:                pal.cpp                                        *
 *   Autor:               Adam Iwanicki                                  *
 *   Opis:                Rozwiazanie wzorcowe polegajace na obliczaniu  *
 *                        pierwiastkow pierwotnych slow, zgodnie z       *
 *                        obserwacja ze konkatenacja bedzie palindromem  *
 *                        o ile slowa sa potegami tego samo slowa.       *
 *                        Rozwiazanie korzysta z STLowych struktur       *
 *                        danych oraz STLowej funkcji sort               *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <string>
using namespace std;

const int MAX=2000001;
vector<string> slowa;
char slowo[MAX];

/*
 * funckja obliczajaca pierwiastek pierwotny danego slowa
 * wylicza tablice prefiksow, a nastepnie zgodnie z obserwacja
 * ze pierwiastek to n-p[n] jesli to dzieli n lub cale slowo
 */
int p[MAX];
char* pierwiastek(char* slowo,int dl) {
  int i=1, q=0;
  p[0]=0;
  while (i<dl) {
    while (q && slowo[i] != slowo[q]) q=p[q-1];
    if (slowo[i] == slowo[q]) q++;
    p[i++]=q;
  }
  if (!(dl%(dl-p[dl-1])))
    slowo[dl-p[dl-1]] = 0;
  return slowo;
}

int main() {
  int n, dl, last=0, wynik=0;
  scanf("%d",&n);
  for(int i=0; i<n; ++i) {
    scanf("%d %s",&dl,slowo);
    slowa.push_back(pierwiastek(slowo,dl));
  }
  sort(slowa.begin(),slowa.end());

  wynik=n;
  for(int i=1; i<n ; ++i)
    if (slowa[i-1]==slowa[i]) wynik+= ++last<<1;
    else last=0;

  printf("%d\n", wynik);
}
