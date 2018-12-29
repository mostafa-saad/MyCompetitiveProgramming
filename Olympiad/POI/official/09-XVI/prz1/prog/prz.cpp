/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     prz.cppas                                                 *
 *   Autor:    Adam Gawarkiewicz                                         *
 *   Opis:     Rozwiazanie wzorcowe O(n*K)                               *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>

#define MAX_NUM 100
#define MAX_N 100000
#define X 0
#define Y 1

/* tablice przechowujace wierzcholki */
int s[2*MAX_N]; // 0 lub 1 - ktorego slowa (x lub y) tyczy sie dany wierzcholek
int a[2*MAX_N], b[2*MAX_N]; // konce przedzialu
int pKraw[2*MAX_N], pWart[2*MAX_N]; // krawedz przy przejsciu do prefiksu, wartosc przy przejsciu do prefiksu
int sKraw[2*MAX_N], sWart[2*MAX_N]; // krawedz przy przejsciu do sufiksu, wartosc przy przejsciu do sufiksu

inline bool rowneWierzch(int w1, int w2) {
    return pKraw[w1] == pKraw[w2] && pWart[w1] == pWart[w2]
        && sKraw[w1] == sKraw[w2] && sWart[w1] == sWart[w2];
}

int dl[2]; // dlugosc ciagu (n, m)
int tab1[2*MAX_N], tab2[2*MAX_N]; // potrzebne do sortowania przez zliczanie
int ileWierzch;
int ile[2*MAX_N]; // potrzebne do sortowania przez zliczanie
int ileElem;
int maxWart; // maksymalna wartosc nadana przy numerowaniu wierzcholkow

int slowo[2][MAX_N];
int ilosc[2][MAX_NUM]; // ilosci danych liczb calkowitych w ciagu
int rozne[2]; // ilosc roznych znakow w ciagach
int najdluzszySufiks[2][2][MAX_N]; // [poziom][slowo][i]: wartosci dla najdluzszych sufiksow slow [0..i]
int najdluzszyPrefiks[2][2][MAX_N]; //[poziom][slowo][i]: wartosci dla najdluzszych prefiksow slow [i..n-1]
int poziom; // na ktorym poziomie akurat jestesmy - 0 lub 1

// operacje na zbiorze, wykorzystuja tablice ile
#define ROZMIAR ileElem
#define DODAJ(a) if (ile[a]++ == 0) ileElem++;
#define USUN(a) if (--ile[a] == 0) ileElem--;
#define ZAWIERA(a) (ile[a] != 0)

void tworzPoziom(int sl, int ileZnakow) {
    memset(ile, 0, sizeof(int)*MAX_NUM);
    ROZMIAR = 0;
    int poprzedniPoziom = (poziom^1);
    int i = 0, j = 0;
    int ostatnioDodany = 0;
    while (j < dl[sl]) {
        while (j < dl[sl] && (ROZMIAR < ileZnakow || ZAWIERA(slowo[sl][j]))) {
            if (!ZAWIERA(slowo[sl][j])) ostatnioDodany = slowo[sl][j];
            DODAJ(slowo[sl][j]);
            j++;
        }

        s[ileWierzch] = sl;
        a[ileWierzch] = i;
        b[ileWierzch] = j - 1;
        pWart[ileWierzch] = najdluzszyPrefiks[poprzedniPoziom][sl][i];
        sWart[ileWierzch] = najdluzszySufiks[poprzedniPoziom][sl][j - 1];
        pKraw[ileWierzch] = ostatnioDodany;
        while (ROZMIAR == ileZnakow) {
            sKraw[ileWierzch] = slowo[sl][i];
            USUN(slowo[sl][i]);
            i++;
        }
        ileWierzch++;
    }
}

int* sortujWierzcholki() {
    // sortuj wg pKraw, wynik zapisz w tab2
    memset(ile, 0, sizeof(int)*(maxWart+1));
    for (int i = 0; i < ileWierzch; i++)
        ile[pKraw[i]]++;
    for (int i = 1; i <= maxWart; i++)
        ile[i] += ile[i-1];
    for (int i = ileWierzch-1; i >= 0; i--)
        tab2[--ile[pKraw[i]]] = i;
    // sortuj tab2 wg pWart, wynik zapisz w tab1
    memset(ile, 0, sizeof(int)*(maxWart+1));
    for (int i = 0; i < ileWierzch; i++)
        ile[pWart[tab2[i]]]++;
    for (int i = 1; i <= maxWart; i++)
        ile[i] += ile[i-1];
    for (int i = ileWierzch-1; i >= 0; i--)
        tab1[--ile[pWart[tab2[i]]]] = tab2[i];
    // sortuj tab1 wg sKraw, wynik zapisz w tab2
    memset(ile, 0, sizeof(int)*(maxWart+1));
    for (int i = 0; i < ileWierzch; i++)
        ile[sKraw[tab1[i]]]++;
    for (int i = 1; i <= maxWart; i++)
        ile[i] += ile[i-1];
    for (int i = ileWierzch-1; i >= 0; i--)
        tab2[--ile[sKraw[tab1[i]]]] = tab1[i];
    // sortuj tab2 wg sWart, wynik zapisz w tab1
    memset(ile, 0, sizeof(int)*(maxWart+1));
    for (int i = 0; i < ileWierzch; i++)
        ile[sWart[tab2[i]]]++;
    for (int i = 1; i <= maxWart; i++)
        ile[i] += ile[i-1];
    for (int i = ileWierzch-1; i >= 0; i--)
        tab1[--ile[sWart[tab2[i]]]] = tab2[i];
        
    return tab1;
}

void numerujWierzcholki(int* tab) {
    int aktNumer = 0;
    najdluzszyPrefiks[poziom][s[tab[0]]][a[tab[0]]] = najdluzszySufiks[poziom][s[tab[0]]][b[tab[0]]] = aktNumer;
    for (int i = 1; i < ileWierzch; i++)
        najdluzszyPrefiks[poziom][s[tab[i]]][a[tab[i]]] = najdluzszySufiks[poziom][s[tab[i]]][b[tab[i]]] =
            (rowneWierzch(tab[i-1], tab[i]) ? aktNumer : ++aktNumer);
    maxWart = aktNumer > MAX_NUM ? aktNumer : MAX_NUM;
}

int main() {
    int k;
    scanf("%d", &k);
    while (k--) {
        memset(ilosc, 0, sizeof(ilosc));
        rozne[X] = rozne[Y] = 0;
        
        scanf("%d%d", &dl[0], &dl[1]);
        for (int s = X; s <= Y; s++)
            for (int i = 0; i < dl[s]; i++) {
                scanf("%d", &slowo[s][i]);
                slowo[s][i]--;
                if (!ilosc[s][slowo[s][i]]) rozne[s]++;
                ilosc[s][slowo[s][i]]++;
            }
        
        bool czyRozne = (rozne[X] != rozne[Y]);
        for (int i = 0; i < MAX_NUM; i++)
            if (!!ilosc[X][i] != !!ilosc[Y][i])
                czyRozne = true;
        
        if (czyRozne) { // W(x) != W(y)
            printf("0\n");
            continue;
        } else if (rozne[X]==1) { // |W(x)| = |W(y)| = 1
            printf("1\n");
            continue;
        }
        
        poziom = 0;
        for (int s = X; s <= Y; s++)
            for (int i = 0; i < dl[s]; i++)
                najdluzszyPrefiks[poziom][s][i] = najdluzszySufiks[poziom][s][i] = slowo[s][i];
        maxWart = MAX_NUM;
        for (int ileZnakow = 2; ileZnakow <= rozne[X]; ileZnakow++) {
            poziom ^= 1;
            ileWierzch = 0;
            tworzPoziom(X, ileZnakow);
            tworzPoziom(Y, ileZnakow);
            numerujWierzcholki(sortujWierzcholki());
        }
        
        printf("%d\n", (najdluzszyPrefiks[poziom][X][0]==najdluzszyPrefiks[poziom][Y][0]));
    }
    return 0;
}
