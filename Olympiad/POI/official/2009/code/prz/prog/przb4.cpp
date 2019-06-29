/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Przyspieszanie algorytmu (PRZ)                            *
 *   Plik:     przb4.cpp                                                 *
 *   Autor:    Adam Gawarkiewicz                                         *
 *   Opis:     Rozwiazanie bledne. Przeszukuje wszerz drzewo wywolan     *
 *             rekurencyjnych, odwiedzajac tylko okreslona ilosc wierz.  *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <utility>
#include <set>

using namespace std;

#define MAX_NUM 100
#define MAX_N 100000
#define LIMIT 700000

typedef pair<long long, int> wierzcholek;

#define PX(wierzch) (wierzch.first / MAX_N)
#define PY(wierzch) (wierzch.first % MAX_N)
#define ILE_ZNAKOW(wierzch) (wierzch.second)
#define WIERZCHOLEK(px, py, ile_znakow) make_pair(((long long)px)*((long long)MAX_N) + ((long long)py), ile_znakow)

wierzcholek Q[LIMIT];
set<wierzcholek> wygenerowane;
int x[MAX_N], y[MAX_N];
int ile_x[MAX_NUM], ile_y[MAX_NUM];
int n, m, ile_wierzch;

bool generuj(int ind) {
    int px = PX(Q[ind]), py = PY(Q[ind]), ile_znakow = ILE_ZNAKOW(Q[ind]);
    
    if (ile_znakow == 1) return x[px]==y[py];
    
    int rozne_x = 0;
    memset(ile_x, 0, sizeof(ile_x));
    for (int i = px; i < n && (rozne_x < ile_znakow || ile_x[x[i]]); i++) {
        if (!ile_x[x[i]]) 
            rozne_x++;
        ile_x[x[i]]++;
    }
    
    int rozne_y = 0;
    memset(ile_y, 0, sizeof(ile_y));
    for (int i = py; i < m && (rozne_y < ile_znakow || ile_y[y[i]]); i++) {
        if (!ile_y[y[i]]) 
            rozne_y++;
        ile_y[y[i]]++;
    }
    if (rozne_x != ile_znakow || rozne_y != ile_znakow) return false;
    
    for (int i = 0; i < MAX_NUM; i++)
        if (!!ile_x[i] != !!ile_y[i])
            return false;
    
    int pierwszy_x = px;
    while (--ile_x[x[pierwszy_x]]) pierwszy_x++;
    pierwszy_x++;
    int pierwszy_y = py;
    while (--ile_y[y[pierwszy_y]]) pierwszy_y++;
    pierwszy_y++;
    
    if (ile_wierzch < LIMIT) {
        wierzcholek wierzch = WIERZCHOLEK(px, py, ile_znakow-1);
        if (wygenerowane.find(wierzch)==wygenerowane.end()) {
            Q[ile_wierzch++] = wierzch;
            wygenerowane.insert(wierzch);
        }
    }
    if (ile_wierzch < LIMIT) {
        wierzcholek wierzch = WIERZCHOLEK(pierwszy_x, pierwszy_y, ile_znakow-1);
        if (wygenerowane.find(wierzch)==wygenerowane.end()) {
            Q[ile_wierzch++] = wierzch;
            wygenerowane.insert(wierzch);
        }
    }
    
    return true;
}

int main() {
    int k;
    scanf("%d", &k);
    while (k--) {
        scanf("%d%d", &n, &m);
        int rozne_x = 0, rozne_y = 0;
        memset(ile_x, 0, sizeof(ile_x));
        memset(ile_y, 0, sizeof(ile_y));
        
        for (int i = 0; i < n; i++) {
            scanf("%d", &x[i]);
            x[i]--;
            if (!ile_x[x[i]]) rozne_x++;
            ile_x[x[i]]++;
        }
        for (int i = 0; i < m; i++) {
            scanf("%d", &y[i]);
            y[i]--;
            if (!ile_y[y[i]]) rozne_y++;
            ile_y[y[i]]++;
        }
        bool czyRozne = (rozne_y != rozne_x);
        for (int i = 0; i < MAX_NUM; i++)
            if (!!ile_x[i] != !!ile_y[i])
                czyRozne = true;
        
        if (czyRozne) { // W(x) != W(y)
            printf("0\n");
            continue;
        } else if (rozne_x==1) { // |W(x)| = |W(y)| = 1
            printf("1\n");
            continue;
        }
        
        wygenerowane.clear();
        Q[0] = WIERZCHOLEK(0, 0, rozne_x);
        ile_wierzch = 1;
        bool wynik = true;
        for (int akt = 0; wynik && akt<ile_wierzch; akt++)
            wynik = generuj(akt);
        
        printf("%d\n", wynik);
    }
    return 0;
}
