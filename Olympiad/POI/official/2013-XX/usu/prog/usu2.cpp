/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Usuwanka                                      *
 *   Autor:                Igor Adamski                                  *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe, wersja z tablica next   *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<cstdlib>
#include<queue>
using namespace std;

const int MAXN = 1000010;

int ciag[MAXN];
int next[MAXN]; /* ciag[i] + ciag[i+1] + ... + ciag[next[i]] = 0 */

int n, k;

void obliczNext() {
    /* pom[i] = ostatni indeks, taki ze suma sufiksu ciagu jest rowna i
       czyli pom[i] = j jesli
       ciag[j] + ciag[j+1] + ... ciag[n] = i */
    int *pom = (int*)malloc(2*n*sizeof(int));
    for(int i=0; i<2*n; ++i) pom[i] = n+2;
    /* Zmieniamy wskaznik na poczatek tablicy, dzieki temu bedzie mozna sie odwolywac do ujemnych indeksow */
    pom += n;
    pom[0] = n+1;
    int sum = 0; /* Suma wartosci sufiksu ciagu */
    for(int i=n; i>=1; --i)
    {
        sum += ciag[i];
        next[i] = pom[sum] - 1;
        pom[sum] = i;
    }
    pom -= n;
    free(pom);
}

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(0);
    cin >> n >> k;
    for(int i=1; i<=n; ++i)
    {
        char z;
        cin >> z;
        if(z == 'b') ciag[i] = 1;
        else ciag[i] = -k;
    }
    obliczNext();
    queue< pair<int,int> > Q;
    /* Zaczynamy z calym przedzialem */
    Q.push(make_pair(1, n));
    while(!Q.empty())
    {
        int i = Q.front().first;
        int j = Q.front().second;
        Q.pop();
        int t = next[i];
        /* Jezeli da sie ten przedzial rozdzielic na dwa niepuste
           przedzialy, ktorym sumy wynosza 0
           to tak robimy */
        if(t < j) {
            Q.push(make_pair(i, t));
            Q.push(make_pair(t+1, j));
        }
        else {
            /* W przeciwnym wypadku wykonujemy ruch */
            cout << i << ' ';
            ++i;
            while(i <= j)
            {
                if(next[i] <= j) {
                    /* Omijamy spojny zerowy podprzedzial i dodajemy go do zbioru */
                    Q.push(make_pair(i, next[i]));
                    i = next[i] + 1;
                }
                else {
                    cout << i << ' ';
                    ++i;
                }
            }
            cout << "\n";
        }
    }
    return 0;
}

