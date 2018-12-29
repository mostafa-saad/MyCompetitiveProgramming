/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Karty                                         *
 *   Autor:                Lech Duraj                                    *
 *   Zlozonosc czasowa:    O(n + m log n)                                *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

using namespace std;

typedef int PI[2];

const int infty = (int)1e9+1;
const int maxn = 200*1000;

typedef bool matrix[2][2];

PI cards[2*maxn+1];             // wartosci kart

/* Drzewo przedzialowe: */
matrix trans[4*maxn+3];         // macierz mozliwych przejsc z poczatku na koniec przedzialu
// trans[x][p][q] = 1 wtedy i tylko wtedy, kiedy mozna ustawic przedzial wezla x nierosnaco tak,
// aby skrajnie lewa karta byla w pozycji p, a prawa w pozycji q
PI borders[4*maxn+3];           // borders[x] = (poczatek,koniec) przedzialu x, pomocniczo



void fix(int x)         /* naprawia wezel drzewa */
{
    int bleft = borders[2*x][1];  // dwie karty w srodku przedzialu, na styku jego dzieci
    int bright = borders[2*x+1][0];
    for(int q=0; q<2; q++)
        for(int r=0; r<2; r++)
            trans[x][q][r] = false;
    for(int s=0; s<2; s++)        // dla wszystkich mozliwe kombinacji kart srodkowych...
        for(int t=0; t<2; t++)
        {
            if (cards[bleft][s]>cards[bright][t])     // ...ktore sa dozwolone...
                continue;
            for(int q=0; q<2; q++)                    // ...ustaw na 1 odpowiednie wartosci w macierzy przejsc
                for(int r=0; r<2; r++)
                    trans[x][q][r] |= trans[2*x][q][s] && trans[2*x+1][t][r];
        }
}

int main()
{
    int n,m;
    scanf("%d",&n);
    for(int i=0; i<n; i++)
        scanf("%d %d",&cards[i][0],&cards[i][1]);

    int K = 1;                            // uzupelnij liczbe kart do potegi dwojki
    while(K<n)
        K*=2;
    for(int i=n; i<K; i++)
        cards[i][0] = cards[i][1] = infty;

    for(int i=0; i<K; i++)                // wypelnij dolny poziom drzewa (wezly K..2K-1)
    {
        borders[K+i][0] = borders[K+i][1] = i;
        for(int q=0; q<=1; q++)
            for(int r=0; r<=1; r++)
                trans[K+i][q][r] = (q==r);
    }

    for(int i=K-1; i>=1; i--)             // wypelnij reszte drzewa od konca
    {
        borders[i][0] = borders[2*i][0];
        borders[i][1] = borders[2*i+1][1];
        fix(i);
    }

    scanf("%d",&m);                       // przerobienie zapytan
    for(int i=0; i<m; i++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        x--;
        y--;
        swap(cards[x][0],cards[y][0]);            // zamien karty (macierzy na dole drzewa nie trzeba, sa identyczne)
        swap(cards[x][1],cards[y][1]);
        int t;
        t = (K+x)/2;                        // napraw sciezki od zmienionych wezlow
        while(t>0)
        {
            fix(t);
            t = t/2;
        }
        t = (K+y)/2;
        while(t>0)
        {
            fix(t);
            t = t/2;
        }

        /* da sie ustawic cala tablice <=> ktores przejscie w wezle 1 jest mozliwe */
        printf((trans[1][0][0] || trans[1][0][1] || trans[1][1][0] || trans[1][1][1]) ? "TAK\n" : "NIE\n");
    }
    return 0;
}
