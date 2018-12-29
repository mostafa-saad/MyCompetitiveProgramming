/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PAL (Palindromy)                               *
 *   Plik:                pal1.c                                         *
 *   Autor:               Adam Iwanicki                                  *
 *   Opis:                Rozwiazanie wzorcowe polegajace na obliczaniu  *
 *                        pierwiastkow pierwotnych slow, zgodnie z       *
 *                        obserwacja ze konkatenacja bedzie palindromem  *
 *                        o ile slowa sa potegami tego samo slowa.       *
 *                        Nastepnie mozna posortowac te pierwiastki      *
 *                        pierwotne leksykograficznie, a nastepnie zlicz *
 *                        ile jest tych samych slow sortujac je          *
 *                        leksykograficznie zlozonosc O(n), gdzie        *
 *                        n - suma dlugosci slow                         *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define MAX 2000001
#define ALPHA 26
#define WSK(X) (X-'a'+1)

char slowa[MAX];
int poczatki[MAX],dlugosci[MAX],kolejnosc[MAX],n;
long long int wynik=0;

/*
 * funkcja zwracajaca wartosc logiczna czy pierwiastek pierwotny
 * palindromu a jest mniejszy od pierwiastka pierwotnego palindromu b
 * w porzadku leksykograficznym
 */
int porownaj(int k, int l)
{
  int dl,i;
  char *a, *b;
  if (dlugosci[k] < dlugosci[l]) return -1;
  else if (dlugosci[k] > dlugosci[l]) return 1;
  dl = dlugosci[k]; a = slowa+poczatki[k]; b = slowa+poczatki[l];
  for (i=0; i<dl && *a==*b; ++i,++a,++b) ;
  if (i==dl) return 0;
  else if (*a<*b) return -1;
  else return 1;
}

void sort(int l, int p) 
{
    int pom,med=(l+p)>>1,x, i=l, j=p;
    if (l>=p) return;
    x = kolejnosc[med];
    do {
        while (porownaj(kolejnosc[i],x) == -1) ++i;
        while (porownaj(kolejnosc[j],x) == 1) --j;
        if (i<=j) {
            pom = kolejnosc[i];
            kolejnosc[i++] = kolejnosc[j];
            kolejnosc[j--] = pom;
        }
    } while (i<=j);
    sort(i,p);
    sort(l,j);
}

/*
 * sortuje pierwiastki slow leksykograficznie 
 */
inline void posortuj() {
  int i;
  for(i=0; i<n; ++i) kolejnosc[i]=i;
  sort(0,n-1);
}

/*
 * funckja obliczajaca pierwiastek pierwotny danego slowa
 * wylicza tablice prefiksow, a nastepnie zgodnie z obserwacja
 * ze pierwiastek to n-p[n] jesli to dzieli n lub cale slowo
 */
int p[MAX];
void pierwiastek(int k) {
  int i=1, q=0, dl=dlugosci[k];
  char *slowo = slowa+poczatki[k];
  p[0]=0;
  while (i<dl) {
    while (q && slowo[i] != slowo[q]) q=p[q-1];
    if (slowo[i] == slowo[q]) q++;
    p[i++]=q;
  }
  dlugosci[k] = (dl%(dl-p[dl-1]))==0 ? dl-p[dl-1] : dl;
}

int main() {
  int i,last=0;
  scanf("%d",&n);
  for(i=0; i<n; ++i) {
    poczatki[i]=last;
    scanf("%d ",dlugosci+i);
    scanf("%s",slowa+last);
    last+=dlugosci[i];
    pierwiastek(i);
  }
  posortuj();

  last=0;
  wynik=n;
  for(i=1; i<n ; ++i) 
    if (porownaj(kolejnosc[i-1],kolejnosc[i])==0) wynik+= ++last<<1;
    else last=0;
  
  printf("%lld\n", wynik);
  return 0;
}
